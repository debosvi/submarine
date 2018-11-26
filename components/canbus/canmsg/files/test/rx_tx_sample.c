/* ISC license. */

#include <stdio.h>
#include <stdlib.h>

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

#define USAGE "sample_rx_tx [-v verbosity] [-r]"
#define dieusage() strerr_dieusage(100, USAGE)

#define MSG_SIZE	(45)
char all_buf[MSG_SIZE];
s6canmsg_buf_t msg_buf = S6CANMSG_BUF_ZERO;

static void init_buf(char *b, size_t n) {
    int i=0;
    for(; i<(int)n; i++) {
        b[i] = '0' + rand()%10;
    }
}

static void show_buf(char *b, size_t n) {
    if(b) {
        int i=0;
        fprintf(stderr, "buf:\n");
        for(; i<(int)n; i++) {
            if(i && !(i%8))
                fprintf(stderr, "\n");
            fprintf(stderr, "%c ", b[i]);
        }
        fprintf(stderr, "\n");
    }
}

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    unsigned int do_recv=0;
    int cfd=-1;
    
    PROG = "sample_rx_tx" ;
    environ=(char**)envp;
    
    {
        subgetopt_t l = SUBGETOPT_ZERO ;
        for (;;) {
            int opt = subgetopt_r(argc, argv, "v:r", &l) ;
            if (opt == -1) break ;
            switch (opt) {
                case 'v' : if (!uint0_scan(l.arg, &verbosity)) dieusage() ; break ;
                case 'r' : do_recv=1; break;
                default : dieusage() ;
            }
        }
        argc -= l.ind ; argv += l.ind ;
    }
    if (argc > 0) dieusage() ;
        
    cfd=s6canbus_get_openfd();
    if(!s6canmsg_init(&msg_buf, all_buf, MSG_SIZE)) strerr_diefu1sys(111, "s6canmsg_init_buf");
    init_buf(all_buf, MSG_SIZE);    
    show_buf(all_buf, MSG_SIZE);    

    { 
        tain_t deadline = TAIN_ZERO;
        const tain_t tto = { .sec=TAI_ZERO, .nano=450*1000*1000 };
        struct canfd_frame frame;
        iopause_fd x[1]= { { .fd=cfd, .events=0, .revents=0 } };
        register int r;
        char ts_str[TIMESTAMP];

        tain_now_g();
        tain_add_g(&deadline, &tain_infinite_relative);
        strerr_warni1x("wait event");
        
        for(;;) {
            int n;
            if(do_recv) x[0].events |= IOPAUSE_READ;
            else x[0].events = (S6CANMSG_HAS_DATA(&msg_buf)? IOPAUSE_WRITE: 0);
            if(x[0].events) strerr_warni1x(", wait write");

            r=iopause_g(x, 1, &deadline);
            timestamp_g(ts_str);

            if(r<0) strerr_diefu1sys(111, "iopause") ;
            if(!r) {
                strerr_warni2x(ts_str, ", frame not received in time");
                tain_add_g(&deadline, &tto);                
            }
            else if(x[0].events & IOPAUSE_READ) {
                strerr_warni2x(ts_str, ", frame received, set timeout for next");
                tain_add_g(&deadline, &tto);      
                n=fd_read(x[0].fd, (char*)&frame, sizeof(struct canfd_frame));
                
            }
            else if(x[0].events & IOPAUSE_WRITE) {
                strerr_warni2x(ts_str, ", frame to send");
                frame.can_id=0x1234;
                n=s6canmsg_next(&msg_buf, (char*)frame.data, 8);
                frame.len=n;
                
                if(fd_write(x[0].fd, (char*)&frame, sizeof(struct canfd_frame)))
                    s6canmsg_ack(&msg_buf, n);
                
            }
            else {
                strerr_warni2x(ts_str, ", frame reception error");
            }
        }
    }
    
}
