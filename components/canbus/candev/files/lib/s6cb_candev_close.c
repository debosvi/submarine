/* ISC license. */

#include <private/candev_p.h>

#if defined(S6CANBUS_CANDEV_REGULAR)

#define __USE_MISC

#include <sys/types.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int s6cb_candev_close(const int fd) {
    return close(fd);
}

#elif defined(S6CANBUS_CANDEV_FAKE)

int s6cb_candev_close(const int fd) {
    return 1;
}

#endif
