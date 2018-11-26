/* ISC license. */

#include <unistd.h> // dup2

#include <skalibs/types.h>
#include <skalibs/sgetopt.h>
#include <skalibs/strerr2.h>
#include <skalibs/djbunix.h>
#include <skalibs/environ.h>
#include <skalibs/env.h>

#include <s6canbus/candev.h>

#define USAGE "subm_rudder [-v verbosity] [-d device] [-n]"
#define dieusage() strerr_dieusage(100, USAGE)

const char* default_device_name = "can0";

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    unsigned int closestdin = 1;
    char *dev=(char*)default_device_name;
    int cfd=-1;

    PROG = "subm_rudder" ;
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
    if (argc < 0) dieusage() ;

    if(closestdin) close(0) ;

    cfd=s6cb_candev_open(dev);
    if (cfd<0) strerr_diefu2sys(111, "open CAN device: ", dev) ;

    char canbuf[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    uint32_t id=0x1234;
    
    ssize_t w=s6cb_candev_write(cfd, id, canbuf, 6);
    if (w<0) strerr_diefu1sys(111, "write on CAN device") ;

    ssize_t r=s6cb_candev_read(cfd, &id, (void*)canbuf);
    if (r<0) strerr_diefu1sys(111, "read on CAN device") ;
   
    return 0;
}

