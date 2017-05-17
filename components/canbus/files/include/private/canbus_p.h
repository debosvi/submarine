
#ifndef __CANBUS_PRIV_H__
#define __CANBUS_PRIV_H__

#include <errno.h>

#ifndef __USE_CANUDP
    #include <net/if.h>
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    
    #include <linux/can.h>
#else
    #include <skalibs/socket.h>
#endif

#include <skalibs/djbunix.h>
#include <skalibs/strerr2.h>

#include <canbus/canbus.h>

#ifdef __USE_CANUDP
extern const char canbus_udp_addr[4];
extern const char canbus_mcast_addr[4];
extern const uint16_t canbus_udp_port;
#endif

#endif // __CANBUS_PRIV_H__