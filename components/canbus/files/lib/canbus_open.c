
#include <private/canbus_p.h>

#ifndef __USE_CANUDP
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int canbus_open_regular(const char* const device, const int use_stamp) {
    int _ret=-1;
    struct ifreq ifr;
    struct sockaddr_can caddr;
    int fd=-1;
   
    fd=socket(PF_CAN, SOCK_RAW, CAN_RAW);    
    if(fd<0) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while opening BCM socket: ", strerror(errno));
        goto _exit;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strcpy(ifr.ifr_name, device);
    
    if(ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while searching for bus: ", strerror(errno));
        goto _exit;
    }

    {
        int stamp=!!use_stamp;
        if(setsockopt(fd, SOL_SOCKET, SO_TIMESTAMP, &stamp, sizeof(stamp)) < 0) {
            strerr_warn2x(__PRETTY_FUNCTION__, ": could not enable CAN timestamps");
            goto _exit;
        }
    }

    memset(&caddr, 0, sizeof(struct sockaddr_can));
    caddr.can_family = AF_CAN;
    caddr.can_ifindex = ifr.ifr_ifindex;
    
    /* bind socket */
    if(bind(fd, (struct sockaddr *) &caddr, sizeof(caddr)) < 0) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while binding RAW socket: ", strerror(errno));
        goto _exit;
    }

    _ret=0;
    
_exit:
    if(_ret<0) {
        fd_close(fd);
        fd=-1;
    }
    return fd;
}
#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>    

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int canbus_open_udp(const int server) {
    int _ret=-1;
    int fd=-1;
   
    fd=socket_udp();  
    if(fd<0) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while opening UDP socket: ", strerror(errno));
        goto _exit;
    }
    
    if(server && socket_bind4_reuse (fd, canbus_udp_addr, canbus_udp_port)) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while binding UDP socket: ", strerror(errno));
        goto _exit;
    }
    
    if(server) {
        struct ip_mreq mreq;
        
        memset(&mreq, 0, sizeof(struct ip_mreq));
        memcpy(&mreq.imr_multiaddr.s_addr, canbus_mcast_addr, 4) ;
        memcpy(&mreq.imr_interface.s_addr, canbus_udp_addr, 4) ;
        if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq)) < 0) {
            strerr_warn3x(__PRETTY_FUNCTION__, ": error while joining mcast group: ", strerror(errno));
            goto _exit;
        }        
    }
    
    // if(server) {
        // char loopch = 1;
        // if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0) {
            // strerr_warn3x(__PRETTY_FUNCTION__, ": error while loop mcast interface: ", strerror(errno));
            // goto _exit;
        // }        
    // }        
    
    _ret=0;
    
_exit:
    if(_ret<0) {
        fd_close(fd);
        fd=-1;
    }
    return fd;
}
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canbus_open(const char* const device, const int use_stamp) {
    int fd=-1;
    
    if(!device) goto _exit;
    
#ifndef __USE_CANUDP
    fd=canbus_open_regular(const char* const device, const int use_stamp);
#else
    fd=canbus_open_udp(use_stamp);
#endif

_exit:
    return fd;
}