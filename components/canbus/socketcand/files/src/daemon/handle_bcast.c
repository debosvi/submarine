
#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <skalibs/socket.h>
#include <skalibs/fmtscan.h>

#include <binn/json.h>

#include "private/daemon_p.h"

#define BEACON_TYPE "SocketCAN"
#define BEACON_DESCRIPTION PROG

static const char *kname = "name";
static const char *ktype = "type";
static const char *kdesc = "description";
static const char *kaddr = "address";
static const char *kport = "port";
static const char *kbeacon = "beacon";
static const char *kurl = "url";
static const char *kifaces = "ifaces";

stralloc beacon_sa_g = STRALLOC_ZERO;

static char hostname_g[32];
static struct in_addr bcast_addr;

///////////////////////////////////////////////////////////////////////////////
static void build_bcast_buffer(void) {
    if(beacon_sa_g.s) return;

    {
        struct in_addr i_addr;
        int iface_port=SERVER_PORT;    
        binn_t head=binn_object();
        binn_t beacon=binn_object();
        binn_t url=binn_object();
        binn_t ifaces=binn_list();
            
        gethostname((char *) &hostname_g, (size_t)  32);
        binn_object_add_item(beacon, kname, binn_string(hostname_g));
        binn_object_add_item(beacon, ktype, binn_string(BEACON_TYPE));
        binn_object_add_item(beacon, kdesc, binn_string(BEACON_DESCRIPTION));
        
        determine_address(&i_addr);
        binn_object_add_item(url, kaddr, binn_string(inet_ntoa( i_addr )));
        binn_object_add_item(url, kport, binn_int16(iface_port));
        
        for(int i=0; i<(int)candev_count_g; i++) {
            binn_list_add_item(ifaces, binn_string(candev_g[i].dname));
        }

        binn_object_add_item(head, kbeacon, beacon);
        binn_object_add_item(head, kurl, url);
        binn_object_add_item(head, kifaces, ifaces);
        
        char *json=binn_to_json_str(head);
        if(json) {
            stralloc_catb(&beacon_sa_g, json, strlen(json));
            stralloc_append(&beacon_sa_g, 0);
            free(json);
        }        
        
        binn_free(head);
    }

    stralloc_shrink(&beacon_sa_g);
    determine_address_bcast(&bcast_addr);
}

///////////////////////////////////////////////////////////////////////////////
int handle_bcast_send(int fd) {    
    build_bcast_buffer();
    
    if(socket_send4 (fd, beacon_sa_g.s, beacon_sa_g.len, (char*)&bcast_addr, BCAST_PORT)<0)
        strerr_diefu1sys(111, "unable to broadcast data") ;

    return 0;
}

static char bcast_buffer_g[1024] = {0};

///////////////////////////////////////////////////////////////////////////////
int handle_bcast_recv(char *buf, unsigned int len) {
    char *sname=0;
    binn_t beacon=BINN_INVALID;
    binn_t name=BINN_INVALID;
    binn_t url=BINN_INVALID; 
    binn_t head=BINN_INVALID;
    int _ret=-1;
    
    (void)len;
    
    strcat(bcast_buffer_g, buf);
    
    _ret=json_to_binn(bcast_buffer_g, &head);
    if(_ret>0) {
        // strerr_warn2x(__PRETTY_FUNCTION__, ": JSON successfully parsed");
        memmove(bcast_buffer_g, bcast_buffer_g+_ret, 1024-_ret);
        bcast_buffer_g[_ret]=0;
    }
    else if(head==BINN_INVALID) {
        strerr_warn2x(__PRETTY_FUNCTION__, ": JSON not parsed");
        return 0;
    }
    
    binn_object_get_item(head, kbeacon, &beacon);
    binn_object_get_item(head, kurl, &url);
    
    if((url==BINN_INVALID) || (beacon==BINN_INVALID)) {
        strerr_warn2x(__PRETTY_FUNCTION__, ": JSON not containing either 'beacon' or 'url' elements");
        binn_free(head);
        return 0;
    }
    
    binn_object_get_item(beacon, kname, &name);
    if(!binn_to_string(name, &sname) && strcmp(hostname_g, sname)) {
        char *saddr=0;
        int64_t uport=0;
        binn_t addr=BINN_INVALID;
        binn_t port=BINN_INVALID;
        binn_t ifaces=BINN_INVALID;
                                
        // find url to connect to
        binn_object_get_item(url, kaddr, &addr);
        binn_object_get_item(url, kport, &port);
        if( !binn_to_string(addr, &saddr) && !binn_to_int64(port, &uport)) {
            char i0[16];
            memset(i0, 0, 16);
            int_fmt(i0, uport);
            strerr_warn6x(__PRETTY_FUNCTION__, ": address (", saddr, "), port(", i0 ,")");
        }
        else {
            strerr_warn2x(__PRETTY_FUNCTION__, ": 'address' or 'port' not found!");
            goto exit;
        }
        
        // find ifaces        
        if(!binn_object_get_item(head, "ifaces", &ifaces)) {
            int i=0;
            while(1) {
                binn_t elem=BINN_INVALID;
                if(!binn_list_get_item(ifaces, i, &elem)) {
                    char *dname=0;
                    if(!binn_to_string(elem, &dname)) {
                        strerr_warn3x(__PRETTY_FUNCTION__, ": subscribe to interface: ", dname);
                        uint32_t ip=0;
                        
                        if(ip4_scan (saddr, (char*)&ip)>7)
                            add_canio_ip(ip, uport, dname);
                    }
                }
                else {
                    break;
                }
                i++;
            }
        }
        else {
            strerr_warn2x(__PRETTY_FUNCTION__, ": no interfaces to subscribe to!");
            goto exit;
        }

    }
    else {
        // strerr_warn2x(__PRETTY_FUNCTION__, ": not relevant message!");
    }

exit:        
    binn_free(head);

    return _ret;
}
