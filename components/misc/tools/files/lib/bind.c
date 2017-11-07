/* ISC license. */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <sys/ioctl.h>

#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <skalibs/strerr2.h>

int __real_bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);

int __wrap_bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen) {
    strerr_warni1x("wrap 'bind' syscall");
    
    if(addr && addr->sa_family!=PF_CAN) {
    	return __real_bind(sockfd, addr, addrlen);
    }
    
	return 0;
}
