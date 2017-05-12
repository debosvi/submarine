
#include <errno.h>

#include <skalibs/djbunix.h>
#include <skalibs/selfpipe.h>
#include <skalibs/iopause.h>
#include <skalibs/strerr2.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/uint16.h>

#include <subm/equipment.h>

static int cont_g=1;

#define MIN_CONSIG      (0)
#define MAX_CONSIG      (255)
#define DEFAULT_CONSIG  (128)
static uint16_t consig_pos_g=DEFAULT_CONSIG;
static uint16_t current_pos_g=DEFAULT_CONSIG;

#define STEP_MS (20)
#define STEP_POS (10)

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
static int read_uint (const int fd, uint16_t *nb) {
    char buf[UINT16_FMT + 1];
    ssize_t r = fd_read(fd, buf, UINT16_FMT) ;
    if (r<0) {
        if (errno != ENOENT) strerr_warnwu1sys("read input") ;
        return 0 ;
    }
    buf[byte_chr(buf, r, '\n')] = 0 ;
    strerr_warnw2x("new consig: ", buf);

    if (!uint16_fmt(buf, nb) && (nb>MAX_CONSIG) ) {
        strerr_warnw1x("invalid input") ;
        return 0 ;
    }
    return 1 ;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void handle_input(const int fd) {
    uint16_t consig=0;
    
    if(read_uint(fd, &consig)) {
        consig_pos_g = consig;        
    }
    
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void handle_output(const int fd) {
    
    
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
        iopause_fd x[3] = { 
            { .fd=0, .events=IOPAUSE_READ },
            { .fd=1, .events=0 },
            { .fd=sigfd, .events=IOPAUSE_READ },
        };
        tain_t deadline=TAIN_INFINITE;
        
        if(consig_pos_g!=current_pos_g) {
            tain_t step_tai = TAIN_ZERO;
            tain_from_millisecs(&step_tai, STEP_MS);
            tain_add_g(&deadline, &step_tai);
        }
        
        r=iopause_g(x, 3, &deadline);
        
        if(r<0) {
            strerr_warnw2x("iopause error, errno: ", strerror(errno));
            cont_g=0;
            continue;
        }
        
        if(!r) {
            register uint16_t step=0;
            register int16_t diff = consig_pos_g-current_pos_g;
            strerr_warnw1x("update pos");
            if(diff>=0) {
                step=(diff>STEP_POS ? STEP_POS : diff);
            }
            else {
                step=(-diff>STEP_POS ? STEP_POS : -diff);
            }
            current_pos_g -= step;
            // cont_g=0;
            continue;
        }
        
        if(x[2].revents & IOPAUSE_READ) handle_signal();
        if(x[0].revents & IOPAUSE_READ) handle_input(x[0].fd);
        if(x[1].revents & IOPAUSE_WRITE) handle_output(x[1].fd);
        
        
    }
    
    selfpipe_finish();
    
    return 0;
}
