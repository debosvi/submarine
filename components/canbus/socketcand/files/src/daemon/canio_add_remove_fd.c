
#define __USE_MISC

#include <stdlib.h>
#include <errno.h>

#include <arpa/inet.h>

#include <skalibs/alloc.h>
#include <skalibs/socket.h>
#include <skalibs/iopause.h>

#include "private/canmsg_p.h"
#include "private/daemon_p.h"

///////////////////////////////////////////////////////////////////////////////
static int check_client_already_there(const uint32_t ip, const uint16_t port, const char* const dname) {
    for(unsigned int i=0; i<canio_count_g; i++) {
        canio_t_ref p=&canio_g[i];
        if((p->type==CANIO_FD_CLIENT) && !strcmp(p->dname, dname) && (p->ip==ip) && (p->port==port))
            return 1;
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
static int open_client_connection(const uint32_t ip, const uint16_t port) {
    int ret=-1;
    int fd=socket_tcp4_nb();
    
    if(fd<0) goto exit;
    
    if(socket_connect4 (fd, (char*)&ip, port)<0) {
        int r=-1;
        tain_t dline ;

        if(errno!=EINPROGRESS) goto exit;
        tain_addsec_g(&dline, 1) ;
        r=socket_waitconn_g(fd, &dline);
        if(!r) goto exit;
    }
    ret=0;
    
exit:    
    if(ret<0) {
        if(fd>=0) close(fd);
        fd=-1;
    }
    return fd;
}

///////////////////////////////////////////////////////////////////////////////
static int store_client(canio_t *io, const int fd) {
    int ret=1;
    char *in=0;
    char *out=0;
    
    if(fd<0) goto exit;
            
    in = alloc(CANIO_INBUF_MAX);
    if(!in) goto exit;

    out = alloc(CANIO_OUTBUF_MAX);
    if(!out) goto exit;
    
    io->ai = in;
    io->ao = out;
    buffer_init (&io->in, buffer_read, fd, io->ai, CANIO_INBUF_MAX);
    buffer_init (&io->out, buffer_write, fd, io->ao, CANIO_OUTBUF_MAX);
    ret=0;
    
exit:
    if(ret && in) free(in);
    if(ret && out) free(out);
        
    return fd;
}

///////////////////////////////////////////////////////////////////////////////
void add_canio_ip(const uint32_t ip, const uint16_t port, const char* const dname) {
    canio_t const zero = CANIO_ZERO ;
    int ret=1;
    int fd=-1;
    canio_t_ref io=&canio_g[canio_count_g];
    
    if(canio_count_g>=CANIO_MAXCONCURRENCY) return;
    
    if(check_client_already_there(ip, port, dname)) {
        strerr_warn2x(__PRETTY_FUNCTION__, ": client already found");
        return;
    }
    
    fd=open_client_connection(ip, port);
    
    (*io) = zero;
    io->type=CANIO_FD_CLIENT;
    if(store_client(io, fd)<0) goto exit;
    io->ip=ip;
    io->port=port;
    strncpy(&io->dname[0], dname, CANDEV_NAMELG);
    
    canio_count_g++;
    ret=0;
    
exit:
    if(ret) 
        (*io) = zero;
}

///////////////////////////////////////////////////////////////////////////////
void add_canio_fd(const int fd) {
    canio_t const zero = CANIO_ZERO ;
    int ret=1;
    canio_t_ref io=&canio_g[canio_count_g];
    
    if(canio_count_g>=CANIO_MAXCONCURRENCY) return;
    
    (*io) = zero;
    io->type=CANIO_FD_SERVER;
    
    if(store_client(io, fd)<0) goto exit;    
        
    handle_client(io, 0, 0);
    
    canio_count_g++;
    ret=0;
    
exit:
    if(ret) 
        (*io) = zero;
}

///////////////////////////////////////////////////////////////////////////////
void remove_canio_idx(const unsigned int i) {
    canio_t const zero = CANIO_ZERO ;
    if(i>=canio_count_g) return;

    fd_close(buffer_fd(&canio_g[i].in));
    free(canio_g[i].ai); 
    free(canio_g[i].ao); 

    canio_g[i] = canio_g[canio_count_g-1] ;
    canio_g[--canio_count_g] = zero;
}

///////////////////////////////////////////////////////////////////////////////
void remove_canio_ptr(canio_t *io) {
    unsigned int idx = (unsigned int)((io-&canio_g[0])/sizeof(canio_t));
    if(idx<canio_count_g)
        remove_canio_idx(idx);        
}

