
#include <skalibs/socket.h>

#include "private/daemon_p.h"

int handle_accept(int fd) {
    uint32_t ip=0;
    uint16_t port=0;
    int cfd = socket_accept4_nb(fd, (char*)&ip, &port);
    if(cfd<0) strerr_diefu1sys(111, "could not accept incoming socket");
    // strerr_warn3x("client connected: ", inet_ntoa(ip), itoa(port));

    return cfd;
}

