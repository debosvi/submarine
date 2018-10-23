/* test command lines example 
 * 
 * send new value to reach
 * cansend vcan0 00010001#001000 
 * 
 */

/* ISC license. */

#include <stdlib.h>
#include <unistd.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <skalibs/buffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/environ.h>
#include <skalibs/env.h>
#include <skalibs/genset.h>
#include <skalibs/iopause.h>
#include <skalibs/sgetopt.h>
#include <skalibs/strerr2.h>
#include <skalibs/tai.h>
#include <skalibs/types.h>

#include <s6canbus/s6canbus.h>

#define USAGE "s6canbus-rudder [-v verbosity] [-d device] [-n]"
#define dieusage() strerr_dieusage(100, USAGE)

static const char* default_device_name = "can0";

// CANBUS stuffs 

static uint32_t address_from_pgn(const uint16_t pgn, const uint8_t src) {
    return (CAN_EFF_FLAG+(pgn<<8)+src);
}

static uint8_t src_from_address(const uint32_t add) {
    return (add&0xff);
}

static uint16_t pgn_from_address(const uint32_t add) {
    if(add&CAN_EFF_MASK) return ((add>>8)&0xffff);
    return 0;
}

const uint8_t node_src_address = S6CB_DEVICE_RUDDER1;

#define address_from_pgn_g(pgn) address_from_pgn(pgn, node_src_address)

static struct can_frame rx_canframe;

typedef GENSETB_TYPE(struct can_frame, 10) canframes_array_t;

static canframes_array_t canframes_array;

// event loop stuffs 
static int cont = 1 ;
static tain_t deadline ;

#define BASIC_TTO_MS    (10)

// others

typedef struct {
    s6cb_pgn_t pgn;
    uint16_t reach_value;
    uint16_t current_value;
    int tick;
    int tto_tick;
} rudder_value_t;

typedef struct { 
    int fd; 
} myown_t;

static rudder_value_t rudder_values[2] = {
    { .pgn=S6CB_PGN_BUILD_ID(S6CB_PGN_RUDDER,0), .reach_value=0x200, .current_value=0x200, .tick=0, .tto_tick=100 },
    { .pgn=S6CB_PGN_BUILD_ID(S6CB_PGN_RUDDER,1), .reach_value=0x200, .current_value=0x200, .tick=0, .tto_tick=250 }
};
static uint16_t step_value = 50;

static void build_can_frame(rudder_value_t* p_rudder, const uint8_t code) {
    if(!p_rudder) return;
    
    uint32_t idx = gensetb_new(&canframes_array);
    struct can_frame* p_can=gensetb_p(struct can_frame, &canframes_array, idx) ;
    
    p_can->can_id = address_from_pgn_g(p_rudder->pgn);
    p_can->can_dlc = 3;
    p_can->data[0] = code;
    p_can->data[1] = (p_rudder->current_value>>8)&0x0ff;
    p_can->data[2] = (p_rudder->current_value>>0)&0x0ff;    
}

static void send_values(rudder_value_t* p_rudder) {
    if(!p_rudder) return;
    
    if(p_rudder->tick>0) return;
    
    buffer_putsflush(buffer_2, "send\n") ;
    build_can_frame(p_rudder, 0x01);
 
    p_rudder->tick = p_rudder->tto_tick/BASIC_TTO_MS + p_rudder->tick;
}

static void update_value(rudder_value_t* p_rudder) {
    if(!p_rudder) return;
    
    if(p_rudder->tick>0) return;
    buffer_putsflush(buffer_2, "update\n") ;
   
    int step = abs(p_rudder->reach_value-p_rudder->current_value);
    if(step) {
        step = (step<step_value?step:step_value);
        if(p_rudder->reach_value>p_rudder->current_value)
            p_rudder->current_value+=step;
        else
            p_rudder->current_value-=step;
    }
    
    send_values(p_rudder);
    p_rudder->tick--;
}

static int send_frame(char *p_tx, void *own) {
    if(!p_tx) return 0;
    myown_t* p_own = (myown_t*)own;
    
    int rtx=write(p_own->fd, p_tx, sizeof(struct can_frame));
    if (rtx > 0) {
        return 1;
    }
    
    return 0;
}

static void send_allframes(const int fd) {
    myown_t myown;
    myown.fd=fd;
    
    int rtx=gensetb_iter(&canframes_array, send_frame, &myown);
    if (rtx > 0) {
//         p_rudder->tick = p_rudder->tto_tick/BASIC_TTO_MS + p_rudder->tick;
    }
}

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    unsigned int closestdin = 1;
    char *dev=(char*)default_device_name;
    int cfd=-1;
    iopause_fd x[1] = { { -1, IOPAUSE_READ, 0 } } ;

    PROG = "s6canbus-rudder" ;
    environ=(char**)envp;
    
    GENSETB_init(struct can_frame, &canframes_array, 10);
    
    tain_now_g();
    tain_copynow(&deadline);
    
    {
        subgetopt_t l = SUBGETOPT_ZERO ;
        for (;;) {
            int opt = subgetopt_r(argc, argv, "v:d:n", &l) ;
            if (opt == -1) break ;
            switch (opt) {
                case 'v' : if (!uint0_scan(l.arg, &verbosity)) dieusage() ; break ;
                case 'd' : dev = (char*)l.arg; break ;
                case 'n' : closestdin = 0; break ;
                default : dieusage() ;
            }
        }
        argc -= l.ind ; argv += l.ind ;
    }
    
    if (argc < 0) dieusage() ;

    if(closestdin) close(0) ;

    cfd=s6canbus_open(dev);
    if (cfd<0) strerr_diefu2sys(111, "open CAN device: ", dev);
    x[0].fd=cfd;
    
    while (cont) {
        int r ;
        int global_send=0;
        
        if(rudder_values[0].tick<=0) buffer_putsflush(buffer_2, "val 0 to send\n") ;
        if(rudder_values[1].tick<=0) buffer_putsflush(buffer_2, "val 1 to send\n") ;
        
        x[0].events = IOPAUSE_READ + (global_send?IOPAUSE_WRITE:0);

        buffer_putsflush(buffer_2, "iopause -------------------------------------------------\n") ;
        r = iopause_g(x, 1, &deadline) ;
        if (r < 0) strerr_diefu1sys(111, "iopause") ;
        else if (!r) {
            { 
                tain_t step_dline; 
                tain_from_millisecs (&step_dline, BASIC_TTO_MS); 
                tain_add_g(&deadline, &step_dline); 
            } 

            buffer_putsflush(buffer_2, "tto\n") ;
            for(int i=0; i<2; i++) {
                update_value(&rudder_values[i]);
            }            
        }
        else {
            if (x[0].revents & IOPAUSE_READ) {
                buffer_putsflush(buffer_2, "read\n") ;
                int rrx=read(x[0].fd, &rx_canframe, sizeof(struct can_frame));
                if (rrx > 0) { 
                    if(src_from_address(rx_canframe.can_id) != S6CB_DEVICE_CCS) {
                    }
                    else {
                        for(int i=0; i<2; i++) {
                            rudder_value_t* p_rudder = &rudder_values[i];
                            if(pgn_from_address(rx_canframe.can_id)==p_rudder->pgn) {
                                char nb_s[UINT16_FMT];
                                
                                int n=uint16_fmt(nb_s, i);
                                buffer_puts(buffer_2, "new value to reach (") ;
                                buffer_put(buffer_2, nb_s, n) ;
                                buffer_puts(buffer_2, ")\n") ;
                                buffer_flush(buffer_2) ;
                                p_rudder->reach_value = (rx_canframe.data[1]<<8)+(rx_canframe.data[2]<<0);
                            }
                        }
                    }
                }
            }
            else if (x[0].revents & IOPAUSE_WRITE) {
                buffer_putsflush(buffer_2, "write\n") ;
                send_allframes(x[0].fd);
            }
        }
    }

    exit(EXIT_SUCCESS);
}

