
#define __USE_MISC

//#include <net/if.h>
#include <arpa/inet.h>

#include <skalibs/socket.h>

#include "private/daemon_p.h"

int init_server_fd(void) {
    struct in_addr i_addr;
    int iface_port=SERVER_PORT;

    int fd = socket_tcp4_nb() ;
    if (fd < 0) strerr_diefu1sys(111, "init server socket") ;

    determine_address(&i_addr);

    if(socket_bind4_reuse (fd, (char*)&i_addr, iface_port)<0)
        strerr_diefu1sys(111, "init server bind and reuse") ;

    if(socket_listen(fd, CANIO_MAXCONCURRENCY)<0)
        strerr_diefu1sys(111, "init server listen") ;

    return fd;
}

