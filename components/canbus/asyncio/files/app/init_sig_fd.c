
#include <skalibs/strerr2.h>
#include <skalibs/sig.h>
#include <skalibs/selfpipe.h>

int init_sig_fd(void) {
    int fd = selfpipe_init() ;
    if (fd < 0) strerr_diefu1sys(111, "init selfpipe") ;

    if (sig_ignore(SIGPIPE) < 0) strerr_diefu1sys(111, "ignore SIGPIPE") ;

    {
        sigset_t set ;
        sigemptyset(&set) ;
        sigaddset(&set, SIGTERM) ;
        sigaddset(&set, SIGHUP) ;
        sigaddset(&set, SIGQUIT) ;
        sigaddset(&set, SIGCHLD) ;
        sigaddset(&set, SIGINT) ;
        if (selfpipe_trapset(&set) < 0) strerr_diefu1sys(111, "trap signals") ;
    }

    return fd;
}

