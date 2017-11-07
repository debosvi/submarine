/* ISC license. */

#define _GNU_SOURCE
// #include <stdio.h>
// #include <string.h>
// 
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>

#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <skalibs/strerr2.h>

#include <private/s6sys_wrapper_p.h>

extern ssize_t __real_socket(int domain, int type, int protocol);

int __wrap_socket(int domain, int type, int protocol) {
    strerr_warni1x("wrap 'socket' syscall");
    
    if(domain!=PF_CAN) {
    	return __real_socket(domain, type, protocol);
    }
    
	return open("/dev/null", O_RDWR);
}
