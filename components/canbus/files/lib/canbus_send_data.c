
#include <private/canbus_p.h>

#ifndef __USE_CANUDP
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int canbus_send_regular(const int fd, const canbus_frame_t* msg) {
    int _ret=-1;

    
_exit:
    return _ret;
}
#else
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define BUF_SIZE    (1+sizeof(canbus_addr_t)+CANBUS_DATA_SIZE_MAX+1)

static int canbus_send_udp(const int fd, const canbus_frame_t* msg) {
    int _ret=-1;
    uint8_t buf[BUF_SIZE];
    uint8_t *p=buf;
    canbus_addr_t *i=(canbus_addr_t*)&buf[1];
    
    memset(buf, 0, BUF_SIZE);
    p[0]=msg->dlc; 
    (*i)=msg->id;
    if(msg->dlc)
        memcpy(&p[1+sizeof(canbus_addr_t)], msg->data, msg->dlc);    

    _ret=socket_send4 (fd, (char*)buf, BUF_SIZE, canbus_mcast_addr, canbus_udp_port);
    return _ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canbus_send_data(const int fd, const canbus_frame_t* msg) {
    int _ret=-1;
    
    if(fd<0) goto _exit;
    if(!msg) goto _exit;
    
#ifndef __USE_CANUDP
    _ret=canbus_send_regular(fd, msg);
#else
    _ret=canbus_send_udp(fd, msg);
#endif

_exit:
    return _ret;
}