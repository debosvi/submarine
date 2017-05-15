
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
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static int canbus_open_udp(void) {
    int _ret=-1;
    int fd=-1;
   
    fd=socket_udp();  
    if(fd<0) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while opening UDP socket: ", strerror(errno));
        goto _exit;
    }
    
    if(socket_bind4_reuse (fd, canbus_udp_addr, canbus_udp_port)) {
        strerr_warn3x(__PRETTY_FUNCTION__, ": error while binding UDP socket: ", strerror(errno));
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
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canbus_open(const char* const device, const int use_stamp) {
    int fd=-1;
    
    if(!device) goto _exit;
    
#ifndef __USE_CANUDP
    fd=canbus_open_regular(const char* const device, const int use_stamp);
#else
    (void)use_stamp;
    fd=canbus_open_udp();
#endif

_exit:
    return fd;
}