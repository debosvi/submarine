/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <s6canbus/s6canbus.h>

int s6canbus_open(const char* const dev) {
    int s=socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (s != -1) {
        struct sockaddr_can addr;
        struct ifreq ifr;
        strcpy(ifr.ifr_name, dev );
        
        if(ioctl(s, SIOCGIFINDEX, &ifr)<0) {
            close(s);
            return -1;
        }

        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        if(bind(s, (struct sockaddr *)&addr, sizeof(addr))) {
            close(s);
            return -1;
        }
    }

    return s;
}
