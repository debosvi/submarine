/* ISC license. */

#define _GNU_SOURCE
#include <stdarg.h>

#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <sys/ioctl.h>

#include <skalibs/strerr2.h>

#include <private/s6sys_wrapper_p.h>

extern int __real_ioctl(int d, int req, ...);

int __wrap_ioctl(int d, int req, ...) {
    strerr_warni1x("wrap 'ioctl' syscall");
    
    if(req!=SIOCGIFINDEX) {
        va_list args; 
        void *p; 
        va_start (args, req);           
        p=va_arg(args, void*); 
        va_end (args );  
        return __real_ioctl(d, req, p);
    }
    
    return 0;
}
