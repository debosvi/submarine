/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>

#include <string.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <private/s6canbus_p.h>

int s6canbus_set_loopback(const int fd, const s6canbus_flag_t flag) {
    int loopback = 0; /* 0 = disabled (default), 1 = enabled */

    if(flag&S6CANBUS_FLAG_ENABLE) loopback=1;
    if(setsockopt(fd, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, sizeof(loopback))<0) return -1;

    return 0;
}
