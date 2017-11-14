/* ISC license. */

#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/error.h>

#include <skalibs/types.h>
#include <skalibs/sgetopt.h>
#include <skalibs/strerr2.h>
#include <skalibs/djbunix.h>
#include <skalibs/environ.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/iopause.h>

#include <s6canbus/s6canbus.h>

#define USAGE "sample_rx_tx [-v verbosity]"
#define dieusage() strerr_dieusage(100, USAGE)

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    int cfd=-1;
    
    PROG = "sample_rx_tx" ;
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
    if (argc > 0) dieusage() ;
        
    cfd=s6canbus_get_openfd();
    
    { 
        tain_t deadline = TAIN_ZERO;
        const tain_t tto = { .sec=0, .nano=450*1000*1000 };
        struct canfd_frame frame;
        iopause_fd x[1]= { { .fd=cfd, .events=IOPAUSE_READ, .revents=0 } };

        tain_now_g();
        tain_add_g(&deadline, &tain_infinite_relative);
        strerr_warni1x("wait 1st frame");
        
        for(;;) {
            register int r=iopause_g(x, 1, &deadline);
            char ts_str[TIMESTAMP];
            timestamp_g(ts_str);

            if(r<0) strerr_diefu1sys(111, "iopause") ;
            if(!r) {
                strerr_warni2x(ts_str, ", frame not received in time");
                tain_add_g(&deadline, &tto);                
            }
            else if(x[0].events & IOPAUSE_READ) {
                strerr_warni2x(ts_str, ", frame received, set timeout for next");
                tain_add_g(&deadline, &tto);      
                int n=fd_read(x[0].fd, (char*)&frame, sizeof(struct canfd_frame));
                
            }
            else {
                strerr_warni2x(ts_str, ", frame reception error");
            }
        }
    }
    
}
