
#include <skalibs/strerr2.h>

#include <private/bdp_can.h>

canbus_msg_t bdp_canbus_all_msg_g[3] = { CANBUS_MSG_ZERO,CANBUS_MSG_ZERO,CANBUS_MSG_ZERO };

#define BDP_ONGOING_MSG_SEND_NB (8)
canbus_msg_t* bdp_canbus_ongoing_msg_g[BDP_ONGOING_MSG_SEND_NB] = { 0,0,0 };

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void set_msg_default(void) {
    bdp_canbus_all_msg_g[0].id=canbus_gen_id(CANBUS_EQP_PWR, CANBUS_ID_PWR_STATUS);
    bdp_canbus_all_msg_g[0].dlc=3;
    bdp_canbus_all_msg_g[0].data[0]=0x01;
    bdp_canbus_all_msg_g[0].data[1]=0x02;
    bdp_canbus_all_msg_g[0].data[2]=0x03;
    
    bdp_canbus_all_msg_g[1].id=canbus_gen_id(CANBUS_EQP_PWR, CANBUS_ID_PWR_STATUS);
    bdp_canbus_all_msg_g[1].dlc=8;
    bdp_canbus_all_msg_g[1].data[0]=0x01;
    bdp_canbus_all_msg_g[1].data[1]=0x02;
    bdp_canbus_all_msg_g[1].data[2]=0x03;
    bdp_canbus_all_msg_g[1].data[3]=0x04;
    bdp_canbus_all_msg_g[1].data[4]=0x05;
    bdp_canbus_all_msg_g[1].data[5]=0x06;
    bdp_canbus_all_msg_g[1].data[6]=0x07;
    bdp_canbus_all_msg_g[1].data[7]=0x08;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void handle_send(const int fd, const unsigned idx) {
    int last=0;
    if(idx>=BDP_ONGOING_MSG_SEND_NB) return;
    
    if(canbus_send_data(fd, bdp_canbus_ongoing_msg_g[idx])<0)
        strerr_warnwu1x("canbus_send_data");

    last=get_ongoing_nb();
    last--;
    if(last>0) {
        bdp_canbus_ongoing_msg_g[idx] = bdp_canbus_ongoing_msg_g[last];
    }
    bdp_canbus_ongoing_msg_g[last]=0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void handle_read(const int fd) {
    canbus_msg_t msg = CANBUS_MSG_ZERO;
    if(canbus_recv_data(fd, &msg)<0) {
        strerr_warnwu1x("canbus_recv_data");
        return;
    }
    if(msg.id&CANBUS_EQP_PWR) {
        // strerr_warnw1x("receiver is sender");
        return;
    }
    strerr_warnw1x("receiver is NOT sender");
    
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int get_ongoing_nb(void) {
    int nb=0;
    int i=0;
    for(; i<BDP_ONGOING_MSG_SEND_NB; i++) {
        if(bdp_canbus_ongoing_msg_g[i]) nb++;
        else break;
    }
    return nb;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int get_ongoing_less(void) {
    int ret=0;
    register canbus_addr_t less=0;
    int i=1;
    
    if(!bdp_canbus_ongoing_msg_g[0]) return -1;
    less=bdp_canbus_ongoing_msg_g[0]->id;
    
    for(; i<BDP_ONGOING_MSG_SEND_NB; i++) {
        if(bdp_canbus_ongoing_msg_g[i] && bdp_canbus_ongoing_msg_g[i]->id<less) {
            less=bdp_canbus_ongoing_msg_g[0]->id;
            ret=i;
        }
        else break;
    }
    return ret;
}

void add_ongoing(const unsigned idx) {
    int pos=get_ongoing_less();
    pos++;
    if(pos<BDP_ONGOING_MSG_SEND_NB)
        bdp_canbus_ongoing_msg_g[pos] = &bdp_canbus_all_msg_g[idx]; 
}