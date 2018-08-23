/* ISC license. */

#include <unistd.h> // dup2

#include <skalibs/types.h>
#include <skalibs/sgetopt.h>
#include <skalibs/strerr2.h>
#include <skalibs/djbunix.h>
#include <skalibs/environ.h>
#include <skalibs/env.h>

#include <s6canbus/s6canbus.h>

#define USAGE "s6canbus-opendev [-v verbosity] [-d device] [-n] prog..."
#define dieusage() strerr_dieusage(100, USAGE)

const char* default_device_name = "can0";

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    unsigned int closestdin = 1;
    char *dev=(char*)default_device_name;
    int cfd=-1;

    PROG = "s6canbus-opendev" ;
    environ=(char**)envp;

    {
        subgetopt_t l = SUBGETOPT_ZERO ;
        for (;;) {
            int opt = subgetopt_r(argc, argv, "v:d:n", &l) ;
            if (opt == -1) break ;
            switch (opt) {
                case 'v' : if (!uint0_scan(l.arg, &verbosity)) dieusage() ; break ;
                case 'd' : dev = (char*)l.arg; break ;
                case 'n' : closestdin = 0; break ;
                default : dieusage() ;
            }
        }
        argc -= l.ind ; argv += l.ind ;
    }
    if (argc < 1) dieusage() ;

    if(closestdin) close(0) ;

    cfd=s6canbus_open(dev);
    if (cfd<0) strerr_diefu2sys(111, "open CAN device: ", dev) ;

    if(env_get2(envp, "FORCE_CANFD")) {
        dup2(cfd, 50);
        cfd=50;
    }
    
    {
        char fmt[64] = "" ;
        size_t n = 0 ;
        memcpy(fmt+n, "CANBUSFD=", 9) ; n += 9 ;
        n += uint32_fmt(fmt+n, cfd) ; fmt[n++] = 0 ;
        
        xpathexec_r(argv, envp, env_len(envp), fmt, n) ;
    }
}

