/* ISC license. */

#include <private/candev_p.h>

// #define __USE_MISC
// 
// #include <sys/types.h>
// #include <string.h>
#include <unistd.h>
// 
// #include <sys/socket.h>
// #include <sys/ioctl.h>
// #include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

ssize_t s6cb_candev_read(const int fd, void* const buf, uint32_t* const id) {
    if(fd<0) return (errno=EBADF,-1);
    if(!buf || !id) return (errno=EFAULT,-1);
    
    struct can_frame frame;

    ssize_t nbytes = read(fd, &frame, sizeof(struct can_frame));

    if (nbytes < 0) {
        return -1;
    }

    /* paranoid check ... */
    if (nbytes < (ssize_t)sizeof(struct can_frame)) {
        return -1;
    }
    
    int i=0;
    char* p=(char*)buf;
    for(; i<(int)frame.can_dlc; i++) p[i]=frame.data[i];
    for(; i<S6CANBUS_DATA_MINSIZE; i++) p[i]=0;
    (*id)=frame.can_id;
    return frame.can_dlc;
}
