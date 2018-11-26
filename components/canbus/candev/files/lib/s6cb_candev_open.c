/* ISC license. */

#include <private/candev_p.h>

#if S6CANBUS_CANDEV_REGULAR

#define __USE_MISC

#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int s6cb_candev_open(const char *dev) {
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

#elif S6CANBUS_CANDEV_FAKE

#include <skalibs/bytestr.h>

int s6cb_candev_open(const char *pathname) {
    static int candev_fd=0;

    uint32_t idx;
    size_t l=str_len(pathname);
    
    if(l>=S6CANBUS_CANDEV_PRIV_DEVNAME_SIZE) return -1;

    if(gensetdyn_new(&s6cb_candev_internal_data_g, &idx)) {
        s6cb_candev_internal_t *p=(s6cb_candev_internal_t*)gensetdyn_p(&s6cb_candev_internal_data_g, idx);
        l= (l<S6CANBUS_CANDEV_PRIV_DEVNAME_SIZE?l:S6CANBUS_CANDEV_PRIV_DEVNAME_SIZE);
        p->fd=candev_fd;
        byte_copy(p->dev, l, pathname);
    }
    return candev_fd++;
}

#endif
