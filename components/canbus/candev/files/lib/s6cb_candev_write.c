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

ssize_t s6cb_candev_write(const int fd, const uint32_t id, const void* const buf, const size_t count) {
    if(fd<0) return (errno=EBADF,-1);
    if(!buf) return (errno=EFAULT,-1);
    if(count>S6CANBUS_DATA_MINSIZE) return (errno=EINVAL,-1);
    
    struct can_frame frame;
    
    frame.can_id = id;
    frame.can_dlc = count;
    
    int i=0;
    char* p=(char*)buf;
    for(; i<(int)count; i++) frame.data[i]=p[i];
    for(; i<S6CANBUS_DATA_MINSIZE; i++) frame.data[i]=0;
    
    ssize_t nbytes = write(fd, &frame, sizeof(struct can_frame));

    if (nbytes < 0) {
        return -1;
    }

    /* paranoid check ... */
    if (nbytes < (ssize_t)sizeof(struct can_frame)) {
        return -1;
    }
    
    return nbytes;
}
