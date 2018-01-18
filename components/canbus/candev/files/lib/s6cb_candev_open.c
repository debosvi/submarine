/* ISC license. */

#include <private/candev_p.h>

#if defined(S6CANBUS_CANDEV_REGULAR)

int s6cb_candev_open(const char *pathname) {
    int s=socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (s != -1) {
        int enable_canfd = 1; /* 0 = disabled (default), 1 = enabled */

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

        if(setsockopt(s, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &enable_canfd, sizeof(enable_canfd))<0)  {
            close(s);
            return -1;
        }

    }

    return s;
}

#else if defined(S6CANBUS_CANDEV_REGULAR)

int s6cb_candev_open(const char *pathname) {

}

#endif
