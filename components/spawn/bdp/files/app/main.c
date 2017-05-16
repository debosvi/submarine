
#include <errno.h>

#include <skalibs/djbunix.h>
#include <skalibs/selfpipe.h>
#include <skalibs/iopause.h>
#include <skalibs/strerr2.h>

#include <subm/equipment.h>
#include <private/bdp_can.h>

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
    int canfd=-1;
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
    
    set_msg_default();
    canfd=canbus_open("/dev/can0", 1);
    if(canfd<0) {
        strerr_warnwu1x("init CAN communication");
        cont_g=0;
    }
    
    tain_now_g();
    
    while(cont_g) {
        iopause_fd x[2];
        tain_t deadline=TAIN_ZERO;
        tain_t tto=TAIN_ZERO;
        
        tain_from_millisecs(&tto, 1000);
        
        x[0].fd=sigfd; x[0].events=IOPAUSE_READ;
        x[1].fd=canfd; x[1].events=IOPAUSE_READ + (get_ongoing_nb()>0 ? IOPAUSE_WRITE : 0);
        
        tain_add_g(&deadline, &tto);
        
        r=iopause_g(x, 2, &deadline);
        
        if(r<0) {
            strerr_warnw2x("iopause error, errno: ", strerror(errno));
            cont_g=0;
            continue;
        }
        
        if(!r) {
            strerr_warnw1x("iopause timeout");
            add_ongoing(0);
            continue;
        }
        
        if(x[0].revents & IOPAUSE_READ) handle_signal();
        if(x[1].revents & IOPAUSE_WRITE) {
            while(1) {
                int idx=get_ongoing_less();
                if(idx<0) break;
                strerr_warnw1x("handle_send");
                handle_send(x[1].fd, idx);
            } 
        }        
        if(x[1].revents & IOPAUSE_READ) {
            // strerr_warnw1x("handle_read");
            handle_read(x[1].fd);           
        }        
        
    }
    
    selfpipe_finish();
    
    return 0;
}
