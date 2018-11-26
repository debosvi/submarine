
#include <skalibs/strerr2.h>
#include <skalibs/sig.h>
#include <skalibs/selfpipe.h>

extern unsigned int loop_cont_g;

void handle_signals (void) {
    for (;;) {
        switch (selfpipe_read()) {
            case -1 : strerr_diefu1sys(111, "selfpipe_read") ;
            case 0 : return ;

            case SIGCHLD:
            case SIGTERM:
            case SIGHUP:
            case SIGQUIT:
            case SIGINT:
                strerr_warn3x(PROG, ": ", "now quitting ...");
                loop_cont_g = 0;
                break ;

            default :
                strerr_dief1x(101, "internal error: inconsistent signal state. Please submit a bug-report.") ;
        }
    }
}

