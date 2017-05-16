
#include <private/canbus_p.h>

#ifndef __USE_CANUDP
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static int canbus_send_regular(const int fd, const canbus_addr_t id, const char* data, const size_t dlc) {
    int _ret=-1;

    
_exit:
    return _ret;
}
#else
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define DATA_SIZE    (8)
#define BUF_SIZE    (1+sizeof(canbus_addr_t)+DATA_SIZE+1)

static int canbus_send_udp(const int fd, const canbus_addr_t id, const char* data, const size_t dlc) {
    int _ret=-1;
    char buf[BUF_SIZE];
    char *p=buf;
    canbus_addr_t *i=(canbus_addr_t*)&buf[1];
    
    memset(buf, 0, BUF_SIZE);
    p[0]=(char)dlc; 
    (*i)=id;
    memcpy(&p[1+sizeof(canbus_addr_t)], data, DATA_SIZE);    

    _ret=socket_send4 (fd, buf, BUF_SIZE, canbus_udp_addr, canbus_udp_port);
    return _ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canbus_send_data(const int fd, const canbus_addr_t id, const char* data, const size_t dlc) {
    int _ret=-1;
    
    if(fd<0) goto _exit;
    if(!data && !dlc) goto _exit;
    
#ifndef __USE_CANUDP
    _ret=canbus_send_regular(fd, id, data, dlc);
#else
    _ret=canbus_send_udp(fd, id, data, dlc);
#endif

_exit:
    return _ret;
}