
#define __USE_MISC

#include <arpa/inet.h>

#include <skalibs/socket.h>

#include "private/daemon_p.h"

int init_bcast_fd(void) {
    int optval = 1;
    
    struct in_addr i_addr;
    int iface_port=BCAST_PORT;

    int fd = socket_udp4_nb() ;
    if (fd < 0) strerr_diefu1sys(111, "open broadcast socket") ;

    determine_address_bcast(&i_addr);

    if(setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(int)))
        strerr_diefu1sys(111, "init broadcast socket") ;
        
    if(socket_bind4_reuse (fd, (char*)&i_addr, iface_port)<0)
        strerr_diefu1sys(111, "init broadcastr bind") ;

    return fd;
}

