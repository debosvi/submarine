
#include <errno.h>
#include <string.h>

#include <skalibs/iopause.h>
#include <skalibs/strerr2.h>

#include <canbus/canbus.h>

static int prog_send=0;
static canbus_addr_t msg_id=0;
static char msg_data[8];
    
int main(int ac, char **av) {
    int fd=-1;
    (void)av;
    
    if(ac>1) {
        prog_send=1;
        msg_id=canbus_gen_id(CANBUS_EQP_PWR, CANBUS_ID_PWR_STATUS);
        msg_data[0]=0x01;
        msg_data[1]=0x02;
        msg_data[2]=0x03;
        msg_data[3]=0x04;
        msg_data[4]=0x05;
        msg_data[5]=0x06;
        msg_data[6]=0x07;
        msg_data[7]=0x08;
    }
    
    fd=canbus_open("/dev/can0", 0);
    if(fd<0) return 1;
    
    {
        iopause_fd x = { .fd=fd, .events=IOPAUSE_READ, .revents=0 };
        tain_t deadline=TAIN_INFINITE;
        int r=-1;
        
        if(prog_send) {
            x.events = IOPAUSE_WRITE;
        }
               
        r=iopause_g(&x, 1, &deadline);
        if(r<0) {
            strerr_warnw2x("iopause error, errno: ", strerror(errno));
        }
        
        if(!r) {
            strerr_warnw1x("iopause timeout");
        }
            
        if(prog_send) {        
            if(x.revents & IOPAUSE_WRITE) {
                strerr_warnw1x("iopause write");
                canbus_send_data(fd, msg_id, msg_data, 8);
            }
        }
        else {
            size_t dlc=0;
            
            if(x.revents & IOPAUSE_READ) {
                strerr_warnw1x("iopause read");
                canbus_recv_data(fd, &msg_id, msg_data, &dlc);
            }
        }
    }
    
    canbus_close(fd);   
    
    return 0;
}