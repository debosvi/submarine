
#include <private/canbus_p.h>

#ifndef __USE_CANUDP
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int canbus_recv_regular(const int fd, canbus_frame_t* msg) {
    int _ret=-1;

    
_exit:
    return _ret;
}
#else
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define BUF_SIZE    (1+sizeof(canbus_addr_t)+CANBUS_DATA_SIZE_MAX+1)

static int canbus_recv_udp(const int fd, canbus_frame_t* msg) {
    int _ret=-1;
    uint8_t buf[BUF_SIZE] = {0};
    uint8_t *p=buf;
    canbus_addr_t *i=(canbus_addr_t*)&buf[1];
    char addr[4];
    uint16_t port;
    
    memset(buf, 0, BUF_SIZE);
    if(socket_recv4(fd, (char*)buf, BUF_SIZE, addr, &port)>=(int)BUF_SIZE) {
        msg->dlc=p[0];
        msg->id=(*i);
        if(msg->dlc)
            memcpy(msg->data, &p[1+sizeof(canbus_addr_t)], msg->dlc);    
        _ret=0;
    }

    return _ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canbus_recv_data(const int fd, canbus_frame_t* msg) {
    int _ret=-1;
    
    if(fd<0) goto _exit;
    if(!msg) goto _exit;
    
#ifndef __USE_CANUDP
    _ret=canbus_recv_regular(fd, msg);
#else
    _ret=canbus_recv_udp(fd, msg);
#endif

_exit:
    return _ret;
}