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

#include <skalibs/djbunix.h>
#include <skalibs/environ.h>
#include <skalibs/env.h>
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

#define PDU_FORMAT_RUDDER   (0x01)
#define PGN_RUDDER          (0x01<<8)
#define PGN1                (PGN_RUDDER + 0x00)
#define PGN2                (PGN_RUDDER + 0x01)

static uint32_t address_from_pgn(const uint16_t pgn, const uint8_t src) {
    return (CAN_EFF_FLAG+(pgn<<8)+src);
}

static uint8_t src_from_address(const uint32_t add) {
    return (add&0xff);
}

static uint16_t pgn_from_address(const uint32_t add) {
    return ((add>>8)&0xffff);
}


const uint8_t node_src_address = 0x01;

#define address_from_pgn_g(pgn) address_from_pgn(pgn, node_src_address)

static struct can_frame rx_canframe;
static struct can_frame tx_canframe;
static int send_canframe = 1;

// event loop stuffs 
static int cont = 1 ;
static tain_t deadline ;
static tain_t step_dline;
static tain_t send_dline;

// others
static uint16_t reach_value = 1234;
static uint16_t current_value = 1234;
static uint16_t step_value = 10;

static void update_value(void) {
    int step = abs(reach_value-current_value);
    step = (step<step_value?step:step_value);
    if(reach_value>current_value)
        current_value+=step;
    else
        current_value-=step;
}

int main (int argc, char const *const *argv, char const *const *envp) {
    unsigned int verbosity = 1;
    unsigned int closestdin = 1;
    char *dev=(char*)default_device_name;
    int cfd=-1;
    iopause_fd x[1] = { { -1, IOPAUSE_READ, 0 } } ;

    PROG = "s6canbus-rudder" ;
    environ=(char**)envp;
    
    tx_canframe.can_id = address_from_pgn_g(PGN1);
    tx_canframe.can_dlc = 3;
    tx_canframe.data[0] = 0x01;
    tx_canframe.data[1] = 0x00;
    tx_canframe.data[2] = 0x00;
    
    tain_from_millisecs (&step_dline, 100) ;
    tain_now_g();
    tain_add_g(&send_dline, &step_dline);

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
        
        x[0].events = IOPAUSE_READ + (send_canframe?IOPAUSE_WRITE:0);
        deadline = send_dline;

        r = iopause_g(x, 1, &deadline) ;
        if (r < 0) strerr_diefu1sys(111, "iopause") ;
        else if (!r) {
            tain_add_g(&send_dline, &step_dline);
            send_canframe = 1;
            
            tx_canframe.data[1] = (current_value>>8)&0x0ff;
            tx_canframe.data[2] = (current_value>>0)&0x0ff;
            update_value();
        }
        else {
            if (x[0].revents & IOPAUSE_READ) {
                int rrx=read(x[0].fd, &rx_canframe, sizeof(struct can_frame));
                if (rrx > 0) { 
                    if(pgn_from_address(rx_canframe.can_id)==PGN1) {
                        reach_value = (rx_canframe.data[1]<<8)+(rx_canframe.data[2]<<0);
                    }
                }
            }
            else if (x[0].revents & IOPAUSE_WRITE) {
                int rtx=write(x[0].fd, &tx_canframe, sizeof(struct can_frame));
                if (rtx > 0) send_canframe=0;
            }

        }
    }

    exit(EXIT_SUCCESS);
}

