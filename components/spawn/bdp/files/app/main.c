
#include "skalibs/strerr2.h"
#include "skalibs/selfpipe.h"
#include "skalibs/env.h"
#include "skalibs/iopause.h"

const char const *def_name = "unknown";

static char cont_g = 1;

static tain_t deadline ;

static int init_signals(void) {
    int s=selfpipe_init();
    if(s<0) return -1;
    
    selfpipe_trap(SIGTERM) ;
    selfpipe_trap(SIGINT) ;
    selfpipe_trap(SIGKILL) ;
    
    return s;
}

static void handle_isup(void) {
    static char nfd=3;
    if(nfd>=0)  {
//         strerr_warnw1x("notify up.");
        if(write(nfd, "U", 1)>0) {
            strerr_warnw1x("notified up.");
            nfd=-1;
        }
    }        
}

static void handle_signals(void) {
    int c = selfpipe_read();
    
    switch(c) {
        case SIGTERM: strerr_warnw1x("SIGTERM caught."); cont_g=0; break;
        case SIGINT: strerr_warnw1x("SIGINT caught."); cont_g=0; break;
        case SIGKILL: strerr_warnw1x("SIGKILL caught."); cont_g=0; break;
        default: strerr_warnw1x("signal uncaught."); break;
    }    
}

int main(void) {
    
    int sfd=init_signals();
    int r=0;
    
    PROG = env_get ("PROCNAME");
    if(!PROG) PROG=def_name;
    
    strerr_warni1x("is my process name.");
            
    while(cont_g) {
        iopause_fd x[1] = { { sfd, IOPAUSE_READ, 0 }};
        tain_addsec_g(&deadline, 1);
        r=iopause_g(x, 1, &deadline) ;
        if (r < 0) strerr_diefu1sys(111, "iopause") ;
        else if (!r) {
            handle_isup();
            continue;
        }
        else 
        {
            if (x[0].revents & IOPAUSE_EXCEPT)
                strerr_diefu1x(111, "iopause: trouble with pipes") ;
            if (x[0].revents & IOPAUSE_READ) handle_signals() ;
        } 
    }
    
    selfpipe_finish() ;
    return 0;
}
