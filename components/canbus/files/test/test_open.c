
#include <errno.h>
#include <string.h>

#include <skalibs/iopause.h>
#include <skalibs/strerr2.h>

#include <canbus/canbus.h>

static int prog_send=0;
static canbus_frame_t msg;

#define CANBUS_EQP_CCS      (1) // calculateur central
#define CANBUS_EQP_PWR      (2) // boitier de puissance
#define CANBUS_EQP_GVR1     (3) // governail arri�re 1
#define CANBUS_EQP_GVR2     (4) // governail arri�re 2 
#define CANBUS_EQP_INRT     (5) // centrale inertielle
#define CANBUS_EQP_GVRK     (6) // gouvernail du kiosque

#define CANBUS_ID_INRT_BASE    (0x0100)
#define CANBUS_ID_PWR_BASE     (0x1000)
#define CANBUS_ID_GVR_BASE     (0x2000)

#define CANBUS_ID_PWR_STATUS   (0)
#define CANBUS_ID_PWR_CDEALIM  (1)
#define CANBUS_ID_PWR_CRALIM   (2)

#define CANBUS_GEN_ID(base,id)  (base+id)

#define CANBUS_EQP_MIN      (CANBUS_EQP_CCS) // equipement inf�rieur
#define CANBUS_EQP_MAX      (CANBUS_EQP_GVRK) // equipement sup�rieur
#define CANBUS_EQP_COUNT    (CANBUS_EQP_MAX-CANBUS_EQP_MIN+1) // nb equipements

#define CANBUS_EQP_MASK     (0xff)     
#define CANBUS_CMD_MASK     (0xffffff)     
#define CANBUS_CMD_SHIFT    (8)             // d�calage en bits


static canbus_addr_t canbus_gen_id(const canbus_addr_t source, const canbus_addr_t command) {
    canbus_addr_t _ret=(canbus_addr_t)-1;
    
    if(source<CANBUS_EQP_MIN) goto _exit;
    if(source>CANBUS_EQP_MAX) goto _exit;
    
    _ret=((command&CANBUS_CMD_MASK)<<CANBUS_CMD_SHIFT) + (source&CANBUS_EQP_MASK);
    
_exit:
    return _ret;
}

    
int main(int ac, char **av) {
    int fd=-1;
    (void)av;
    
    if(ac>1) {
        prog_send=1;
        msg.id=canbus_gen_id(CANBUS_EQP_CCS, CANBUS_ID_PWR_STATUS);
        msg.dlc=CANBUS_DATA_SIZE_MAX;
        msg.data[0]=0x01;
        msg.data[1]=0x02;
        msg.data[2]=0x03;
        msg.data[3]=0x04;
        msg.data[4]=0x05;
        msg.data[5]=0x06;
        msg.data[6]=0x07;
        msg.data[7]=0x08;
    }
    
    fd=canbus_open("/dev/can0", !prog_send);
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
                canbus_send_data(fd, &msg);
            }
        }
        else {
            if(x.revents & IOPAUSE_READ) {
                strerr_warnw1x("iopause read");
                canbus_recv_data(fd, &msg);
            }
        }
    }
    
    canbus_close(fd);   
    
    return 0;
}