/* ISC license. */

#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <skalibs/types.h>
#include <skalibs/sgetopt.h>
#include <skalibs/strerr2.h>
#include <skalibs/djbunix.h>
#include <skalibs/environ.h>

#include <s6canbus/s6canbus.h>

#define USAGE "s6canbus-notmine [ -v verbosity ] [ -e ] prog..."
#define dieusage() strerr_dieusage(100, USAGE)

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    int fd=-1;
    s6canbus_flag_t flag=S6CANBUS_FLAG_DISABLE;

    PROG = "s6canbus-notmine" ;
    environ=(char**)envp;
    
    {
        subgetopt_t l = SUBGETOPT_ZERO ;
        for (;;) {
            int opt = subgetopt_r(argc, argv, "v:e", &l) ;
            if (opt == -1) break ;
            switch (opt) {
                case 'v' : if (!uint0_scan(l.arg, &verbosity)) dieusage() ; break ;
                case 'e' : flag=S6CANBUS_FLAG_ENABLE ; break ;
                default : dieusage() ;
            }
        }
        argc -= l.ind ; argv += l.ind ;
    }
    if (argc < 1) dieusage() ;

    fd=s6canbus_get_openfd();
    if (s6canbus_set_notmine(fd, flag)<0) strerr_diefu1sys(111, "set CAN not self loopback") ;

    xpathexec_run(argv[0], argv, envp) ;
}

