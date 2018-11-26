/* ISC license. */

#include <unistd.h> // dup2

#include <linux/can.h>
#include <linux/can/raw.h>

#include <skalibs/types.h>
#include <skalibs/sgetopt.h>
#include <skalibs/strerr2.h>
#include <skalibs/djbunix.h>
#include <skalibs/environ.h>
#include <skalibs/iopause.h>

#include <s6canbus/s6canbus.h>

#define USAGE "s6asyncio [-v verbosity] [-d device]"
#define dieusage(c) strerr_dieusage(c, USAGE)

const char* default_device_name = "can0";

unsigned int loop_cont_g = 1;
static tain_t deadline ;

#define MAX_STATIC_FD  (2)
#define SIGNAL_FD_IDX  (0)
#define CANDEV_FD_IDX  (1)

extern void handle_signals (void);
extern int init_sig_fd(void);


int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    char *dev=(char*)default_device_name;
    int cfd=-1;     /* candev fd */
    int sfd=-1;     /* signal fd */
    struct can_frame cframe;
    int new_frame=0;
    
    PROG = "s6asyncio" ;
    environ=(char**)envp;
        
    {
        subgetopt_t l = SUBGETOPT_ZERO ;
        for (;;) {
            int opt = subgetopt_r(argc, argv, "hv:d:", &l) ;
            if (opt == -1) break ;
            switch (opt) {
                case 'v' : if (!uint0_scan(l.arg, &verbosity)) dieusage(100) ; break ;
                case 'd' : dev = (char*)l.arg; break ;
                case 'h' : dieusage(0);
                default : dieusage(100);
            }
        }
        argc -= l.ind ; argv += l.ind ;
    }
    if (argc < 0) dieusage(100) ;
    
    sfd=init_sig_fd();
    if(sfd<0) strerr_diefu1x(101, "open signalfd");
    
    cfd=s6canbus_open(dev);
    if(cfd<0) strerr_diefu1x(101, "open can device");

    cframe.can_id = 0x010 | CAN_EFF_FLAG;
    cframe.can_dlc = 6;
    memset(&cframe.data[0], 0xA5, 6);
    
    tain_now_g() ;
    tain_addsec_g(&deadline, 3) ;
    
    while (loop_cont_g) {
        iopause_fd x[MAX_STATIC_FD];
        register int r ;
        
        memset(&x[0], 0, MAX_STATIC_FD);
        x[SIGNAL_FD_IDX].fd = sfd; x[SIGNAL_FD_IDX].events = IOPAUSE_READ;
        x[CANDEV_FD_IDX].fd = cfd; x[CANDEV_FD_IDX].events = (new_frame? IOPAUSE_WRITE : 0);
        
//         deadline = deadline_bcast;
        
        r = iopause_g(x, MAX_STATIC_FD, &deadline) ;
        if (r < 0) strerr_diefu1sys(111, "iopause") ;
        else if (!r) {
            new_frame=1;
            tain_addsec_g(&deadline, 3) ;
        }
        
        if ((x[SIGNAL_FD_IDX].revents | x[CANDEV_FD_IDX].revents) & IOPAUSE_EXCEPT)
            strerr_diefu1x(111, "iopause: trouble with pipes") ;
        
        if (x[SIGNAL_FD_IDX].revents & IOPAUSE_READ) handle_signals() ;
        
        if (x[CANDEV_FD_IDX].revents & IOPAUSE_WRITE) {
            int rw;
            new_frame=0;
            rw=write(cfd, &cframe, sizeof(struct can_frame));
            if(rw<=0) strerr_warni1x("unable to send can frame");
        }
    }
    
    return 0;
}

