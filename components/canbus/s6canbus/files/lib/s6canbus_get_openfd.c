/* ISC license. */

#include <skalibs/env.h>
#include <skalibs/uint32.h>

#include <private/s6canbus_p.h>

int s6canbus_get_openfd(void) {
    int fd=-1;
    char *fd_envstr=(char*)env_get(s6canbus_fdstr);
    if(fd_envstr) {
        int32_scan(fd_envstr, &fd);
    }
    return fd;
}

