
#define __USE_MISC

#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <skalibs/socket.h>

#include "private/daemon_p.h"

void determine_address(struct in_addr* l_addr) {
    struct ifreq ifr;
    int probe_socket = -1;

    if(!l_addr) return;
    
    probe_socket = socket_tcp();
    if(probe_socket < 0) strerr_diefu1sys(111, "could not create socket");

    strerr_warn2x("using network interface: ", iface_str);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, iface_str, IFNAMSIZ-1);
    ioctl(probe_socket, SIOCGIFADDR, &ifr);

    close(probe_socket);

    (*l_addr) = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;
    strerr_warn2x("listen adress is: ", inet_ntoa(*l_addr));
}

