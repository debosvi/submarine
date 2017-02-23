
#define __USE_MISC

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <skalibs/strerr2.h>
#include <skalibs/iopause.h>
#include <skalibs/tai.h>
#include <skalibs/fmtscan.h>
#include <skalibs/socket.h>

#include "private/daemon_p.h"

unsigned int loop_cont_g = 1;
static tain_t deadline ;
static tain_t deadline_bcast ;

candev_t candev_g[CANDEV_MAX];
unsigned int candev_count_g = 0;

char *iface_str = (char*)"enp0s8";
canio_t canio_g[CANIO_MAXCONCURRENCY] ;
unsigned int canio_count_g = 0 ;

#define MAX_BUFFER_BCAST    (1024)
static char bcast_alloc_g[MAX_BUFFER_BCAST];
static buffer_t bcast_buf_g = BUFFER_ZERO;

#define MAX_STATIC_FD  (3)
#define SIGNAL_FD_IDX  (0)
#define BCAST_FD_IDX   (1)
#define SERVER_FD_IDX  (2)

int main(int ac, char **av) {
    int sfd=-1;     /* signal fd */
    int mfd=-1;     /* server main fd */
    int bfd=-1;     /* broadcast fd */
    
    (void)ac;
    (void)av;

    // inits
    PROG = "socketcand" ;  
    sfd=init_sig_fd();
    mfd=init_server_fd();
    bfd=init_bcast_fd(); 

    if(!buffer_init (&bcast_buf_g, buffer_read, bfd, bcast_alloc_g, MAX_BUFFER_BCAST))
        strerr_diefu1x(111, "buffer_init: trouble with broadcast buffer init");

    {
        static candev_t const zero = CANDEV_ZERO ;
        register unsigned int i = 0 ;
        for (; i < CANDEV_MAX ; i++) candev_g[i] = zero ;
    }
    {
        static canio_t const zero = CANIO_ZERO ;
        register unsigned int i = 0 ;
        for (; i < CANIO_MAXCONCURRENCY ; i++) canio_g[i] = zero ;
    }
    
    // temporary definition
    add_candev((char*)"vcan0");

    tain_now_g() ;
    tain_addsec_g(&deadline_bcast, 3) ;
    
    while (loop_cont_g) {
        iopause_fd x[MAX_STATIC_FD+canio_count_g];
        register int r ;
        
        memset(&x[0], 0, MAX_STATIC_FD+canio_count_g);
        x[SIGNAL_FD_IDX].fd = sfd; x[SIGNAL_FD_IDX].events = IOPAUSE_READ;
        x[BCAST_FD_IDX].fd = bfd; x[BCAST_FD_IDX].events = IOPAUSE_READ;
        x[SERVER_FD_IDX].fd = mfd; x[SERVER_FD_IDX].events = IOPAUSE_READ;
        
        deadline = deadline_bcast;

        {
            register unsigned int i = 0xff ;
            for (i=0; i < candev_count_g ; i++) {
                register unsigned int j = MAX_STATIC_FD + i ;
                register int fd=candev_g[i].fd;
                // strerr_warn2x(__PRETTY_FUNCTION__, ": look at CAN device fd");
                x[j].fd = fd;
                x[j].events = IOPAUSE_READ ;
                candev_g[i].xindex = j ;
            }
            for (i=0; i < canio_count_g ; i++) {
                register unsigned int j = MAX_STATIC_FD +candev_count_g+ i ;
                register int fd=buffer_fd(&canio_g[i].in);
                // strerr_warn2x(__PRETTY_FUNCTION__, ": look at CAN IO fd");
                x[j].fd = fd;                
                x[j].events = IOPAUSE_READ | (buffer_len(&canio_g[i].out)?IOPAUSE_WRITE:0);
                canio_g[i].xindex = j ;
            }
        }

        r = iopause_g(x, MAX_STATIC_FD+candev_count_g+canio_count_g, &deadline) ;
        if (r < 0) strerr_diefu1sys(111, "iopause") ;
        else if (!r) {
            tain_addsec_g(&deadline_bcast, 3) ;
            handle_bcast_send(x[BCAST_FD_IDX].fd);
        }

        if ((x[SIGNAL_FD_IDX].revents | x[BCAST_FD_IDX].revents) & IOPAUSE_EXCEPT)
            strerr_diefu1x(111, "iopause: trouble with pipes") ;
        
        if (x[SIGNAL_FD_IDX].revents & IOPAUSE_READ) handle_signals() ;
        else if (x[SERVER_FD_IDX].revents & IOPAUSE_READ) {
            int cfd=handle_accept(x[SERVER_FD_IDX].fd);
            add_canio_fd(cfd);
            continue;
        }
        else if (x[BCAST_FD_IDX].revents & IOPAUSE_READ) {
            char buf[256];
            int len=0;
            int ret=0;
                    
            memset(buf, 0, 256);
            len=buffer_get(&bcast_buf_g, buf, 256);
            if((len<0) && (errno==EAGAIN))
                len=strlen(buf);
            
            if(len) {
                ret=handle_bcast_recv(buf, len);
                if(ret) 
                    buffer_unget(&bcast_buf_g, len-ret);
            }
            continue;
        }

        {
            register unsigned int i = 0 ;


            for (; i < candev_count_g ; i++) {
                candev_t *item=&candev_g[i];
                unsigned int idx = item->xindex ;
                {
                    char i0[16], i1[16];
                    memset(i0, 0, 16);
                    memset(i1, 0, 16);
                    int_fmt(i0, i);
                    int_fmt(i1, idx);
                    // strerr_warn4x("loop dev: ", i0, ", index: " , i1);
                }

                if(x[idx].revents & IOPAUSE_READ) handle_candev(item);
            }
        }

        {
            register unsigned int i = 0 ;
            for (; i < canio_count_g ; i++) {
                canio_t *item=&canio_g[i];
                unsigned int idx = item->xindex ;
                {
                    char i0[16], i1[16];
                    memset(i0, 0, 16);
                    memset(i1, 0, 16);
                    int_fmt(i0, i);
                    int_fmt(i1, idx);
                    // strerr_warn6x("loop io: ", i0, ", index: " , i1, ", type: ", (item->type==CANIO_FD_SERVER?"server":"legacy"));
                }

                if(x[idx].revents & IOPAUSE_READ) {
                    int got=0;
                    unsigned int len=0;

                    if(buffer_fill(&item->in)<=0) {
                        remove_canio_idx(i--);
                        continue;
                    }
                    
                    while(1) {
                        unsigned int bl=buffer_len(&item->in)+1;
                        char buf[bl];

                        if(!got) {
                            unsigned int lg1=buffer_len(&item->in);
                            unsigned int lg2=0;
                            if(!lg1) break;
                           
                            lg2=buffer_getnofill(&item->in, &buf[len], lg1);
                            len+=lg2;
                            buf[len]=0;
                        }
                        
                        got=handle_client(item, buf, len);
                        if(got<0) {
                            if(item->nb_error++>=5) loop_cont_g=0;
                            break;
                        }
                        else {
                            if(got>0) {
                                if(got<(int)len) {
                                    buffer_unget(&item->in, len-got);
                                }
                                got=0;
                                len=0;
                                item->nb_error=0;
                            }
                        }
                    } // while

                    // int len=0;
                    
                    // memset(buf, 0, 256);
                    // len=buffer_get(&item->in, buf, 256);

                    // if(!len)
                        // remove_canio_idx(i--);
                    // else while(handle_client(item, buf, len)>=0);
                }
                else if(x[idx].revents & IOPAUSE_WRITE) {
                    buffer_flush(&item->out);
                }
            }
        }
    }
    
    // main termination
    selfpipe_finish();
    fd_close(sfd);
    fd_close(mfd);
    fd_close(bfd);

    // close all clients
    while(canio_count_g>0) 
        remove_canio_idx(0);
    
    stralloc_free(&beacon_sa_g);
    
    exit(EXIT_SUCCESS);
}
