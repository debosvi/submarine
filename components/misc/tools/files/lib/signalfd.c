/* ISC license. */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <skalibs/strerr2.h>

ssize_t __real_signalfd(int fd, const sigset_t *mask, int flags);

int __wrap_signalfd(int fd, const sigset_t *mask, int flags) {
    strerr_warni1x("wrap 'signalfd' syscall");
    
    return open("/dev/null", O_RDWR);
}
