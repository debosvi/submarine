
#include <errno.h>

#include <skalibs/djbunix.h>
#include <skalibs/selfpipe.h>
#include <skalibs/iopause.h>
#include <skalibs/strerr2.h>

#include <subm/equipment.h>

static int cont_g=1;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void handle_signal() {
    register int sig=selfpipe_read();
    
    switch(sig) {
        case SIGKILL: strerr_warnw1x("SIGKILL"); break;
        case SIGTERM: strerr_warnw1x("SIGTERM"); cont_g=0; break;
        case SIGINT: strerr_warnw1x("SIGINT"); cont_g=0; break;
        case SIGHUP: strerr_warnw1x("SIGHUP"); break;
        default: strerr_warnw1x("signal not managed"); break;       
    }
    
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int equipment_fct(void) {
    int sigfd = -1;
    int r=-1;
    
    
    
    sigfd=selfpipe_init();
    if(sigfd<0) {
        strerr_warnwu1x("init signal trap system");
        cont_g=0;
    }
    
    selfpipe_trap(SIGINT) ;
    selfpipe_trap(SIGKILL) ;
    selfpipe_trap(SIGTERM) ;
    selfpipe_trap(SIGHUP) ;
    
    tain_now_g();
    
    while(cont_g) {
        iopause_fd x = { .fd=sigfd, .events=IOPAUSE_READ };
        tain_t deadline=TAIN_INFINITE;
        
        r=iopause_g(&x, 1, &deadline);
        
        if(r<0) {
            strerr_warnw2x("iopause error, errno: ", strerror(errno));
            cont_g=0;
            continue;
        }
        
        if(!r) {
            strerr_warnw1x("iopause timeout");
            cont_g=0;
            continue;
        }
        
        if(x.revents & IOPAUSE_READ) handle_signal();
        
    }
    
    selfpipe_finish();
    
    return 0;
}
