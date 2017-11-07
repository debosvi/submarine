/* ISC license. */

#define _GNU_SOURCE

#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <skalibs/strerr2.h>

#include <private/s6sys_wrapper_p.h>

extern ssize_t __real_setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);

int __wrap_setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen) {
    strerr_warni1x("wrap 'setsockopt' syscall");
    
    if(level!=SOL_CAN_RAW) {
    	return __real_setsockopt(s, level, optname, optval, optlen);
    }
    
	return 0;
}
