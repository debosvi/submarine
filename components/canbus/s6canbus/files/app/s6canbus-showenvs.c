/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/environ.h>
#include <skalibs/sgetopt.h>
#include <skalibs/strerr2.h>
#include <skalibs/types.h>

#define USAGE "s6canbus-showenvs [-v verbosity] prog..."
#define dieusage() strerr_dieusage(100, USAGE)

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    
    PROG = "s6canbus-showenvs" ;
    environ=(char**)envp;

    {
        subgetopt_t l = SUBGETOPT_ZERO ;
        for (;;) {
            int opt = subgetopt_r(argc, argv, "v:", &l) ;
            if (opt == -1) break ;
            switch (opt) {
                case 'v' : if (!uint0_scan(l.arg, &verbosity)) dieusage() ; break ;
                default : dieusage() ;
            }
        }
        argc -= l.ind ; argv += l.ind ;
    }
    if (argc < 1) dieusage() ;
    
    char** e = (char**)envp;
    while(1) {
        if(*e) {
            buffer_puts(buffer_2, *e) ;
            buffer_puts(buffer_2, "\n") ;
            e++;
        }
        else break;        
    }
    
    buffer_flush(buffer_2) ;
    
    xpathexec_run(argv[0], argv, envp) ;
}

