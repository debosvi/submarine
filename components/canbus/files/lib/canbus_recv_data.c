
#include <private/canbus_p.h>

#ifndef __USE_CANUDP
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int canbus_recv_regular(const int fd, canbus_addr_t* id, char* data, size_t* dlc) {
    int _ret=-1;

    
_exit:
    return _ret;
}
#else
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define DATA_SIZE    (8)
#define BUF_SIZE    (1+sizeof(canbus_addr_t)+DATA_SIZE+1)

static int canbus_recv_udp(const int fd, canbus_addr_t* id, char* data, size_t* dlc) {
    int _ret=-1;
    char buf[BUF_SIZE];
    char *p=buf;
    canbus_addr_t *i=(canbus_addr_t*)&buf[1];
    char addr[4];
    uint16_t port;
    
    memset(buf, 0, BUF_SIZE);
    if(socket_recv4(fd, buf, BUF_SIZE, addr, &port)>=(int)BUF_SIZE) {
        (*dlc)=p[0];
        (*id)=(*i);
        memcpy(data, &p[1+sizeof(canbus_addr_t)], DATA_SIZE);    
        _ret=0;
    }

    return _ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canbus_recv_data(const int fd, canbus_addr_t* id, char* data, size_t* dlc) {
    int _ret=-1;
    
    if(fd<0) goto _exit;
    if(!id || !data || !dlc) goto _exit;
    
#ifndef __USE_CANUDP
    _ret=canbus_recv_regular(fd, id, data, dlc);
#else
    _ret=canbus_recv_udp(fd, id, data, dlc);
#endif

_exit:
    return _ret;
}