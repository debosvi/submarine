
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <skalibs/strerr2.h>

#include <canprot/canprot.h>

#include "private/canprot_p.h"
#include "restricted/canprot_r.h"

const canprot_msg_t msg1 = { .id=(canbus_addr_t)0x00f00100, .type=CANPROT_MSG_TYPE_TX, .cycle=CANPROT_MSG_CYCLE_ONESHOT, .ms=0, .bytes=3 };
const canprot_msg_t msg2 = { .id=(canbus_addr_t)0x00f00200, .type=CANPROT_MSG_TYPE_TX, .cycle=CANPROT_MSG_CYCLE_CYCLIC, .ms=1000, .bytes=5 };

#define CANPROT_SIGNAL_11_ID    (0)
const canbus_data_t sig11_def[] = { 0x54 };
const canbus_data_t sig11_init[] = { 0x45 };
#define CANPROT_SIGNAL_12_ID    (1)
const canbus_data_t sig12_def[] = { 0xa5, 0x87 };
const canbus_data_t sig12_init[] = { 0x5a, 0x78 };
 
const canprot_sig_t sig11 = { .msg=&msg1, .pos=0, .bits=8, .def_val=sig11_def, .init_val=sig11_init, .sz_val=1 };
const canprot_sig_t sig12 = { .msg=&msg1, .pos=8, .bits=16, .def_val=sig12_def, .init_val=sig12_init, .sz_val=2 };

#define CANPROT_SIGNAL_21_ID    (2)
const canbus_data_t sig21_def[] = { 0xe1, 0x87 };
const canbus_data_t sig21_init[] = { 0x54, 0x6d };
#define CANPROT_SIGNAL_22_ID    (3)
const canbus_data_t sig22_def[] = { 0xbc };
const canbus_data_t sig22_init[] = { 0xcb };
#define CANPROT_SIGNAL_23_ID    (4)
const canbus_data_t sig23_def[] = { 0xf5, 0x15 };
const canbus_data_t sig23_init[] = { 0xb6, 0x37 };

const canprot_sig_t sig21 = { .msg=&msg2, .pos=0, .bits=16, .def_val=sig21_def, .init_val=sig21_init, .sz_val=2 };
const canprot_sig_t sig22 = { .msg=&msg2, .pos=16, .bits=8, .def_val=sig22_def, .init_val=sig22_init, .sz_val=1 };
const canprot_sig_t sig23 = { .msg=&msg2, .pos=24, .bits=16, .def_val=sig23_def, .init_val=sig23_init, .sz_val=2 };

const canprot_msg_t* canprot_msgs_decl_g[] = { &msg1, &msg2, 0 };
const canprot_sig_t* canprot_sigs_decl_g[] = { &sig11, &sig12, &sig21, &sig22, &sig23, 0 };

#define CANPROT_MSG_MAX_ID      (2)
#define CANPROT_SIGNAL_MAX_ID   (5)
canbus_frame_t msg1_frame;    
canbus_frame_t msg2_frame;    
canprot_msg_state_t canprot_msg_cur_g[] = {
    { .frame=&msg1_frame, .tick=0},
    { .frame=&msg2_frame, .tick=0},
}; 

static void print_msg(const canprot_idx_t idx, const char no_head) {
    if(!no_head) {
        fprintf(stderr, "print msg idx(%d), id(0x%08x), rx(%d), tx(%d), oneshot(%d), cyclic(%d), cycle time(%d), nb bytes(%d)\n",
            idx, canprot_msgs_decl_g[idx]->id, 
            (canprot_msgs_decl_g[idx]->type==CANPROT_MSG_TYPE_RX?1:0), (canprot_msgs_decl_g[idx]->type==CANPROT_MSG_TYPE_TX?1:0),
            (canprot_msgs_decl_g[idx]->cycle==CANPROT_MSG_CYCLE_ONESHOT?1:0), (canprot_msgs_decl_g[idx]->cycle==CANPROT_MSG_CYCLE_CYCLIC?1:0),
            canprot_msgs_decl_g[idx]->ms, canprot_msgs_decl_g[idx]->bytes);
    }
    fprintf(stderr, "\tframe %d, id(0x%08x), dlc(%d), data(", no_head, canprot_msg_cur_g[idx].frame->id, canprot_msg_cur_g[idx].frame->dlc);
    for(int i=0; i<canprot_msgs_decl_g[idx]->bytes; i++)
        fprintf(stderr, "0x%02x, ", canprot_msg_cur_g[idx].frame->data[i]);
    fprintf(stderr, "\e[2D)\n");    
}
    
int main(void) {
    int r=-1;
    
    PROG = PROG_NAME;
    
    strerr_warni1x("canprot_check_valid_decl");
    r=canprot_check_valid_decl();
    if(r) strerr_warnwu1x("canprot_check_valid_decl error");    
    
    strerr_warni1x("canprot_init");
    if(canprot_init()) {
        strerr_warnwu1x("canprot_init");
        goto _exit;
    }
    
    strerr_warni1x("canprot_set_data_value");
    for(int i=0; i<CANPROT_MSG_MAX_ID; i++) {
        print_msg(i, 0);
        r=canprot_set_default_value(i);
        if(r) {
            strerr_warnwu1x("canprot_set_data_value error");   
            // goto _exit;
        } 
        else print_msg(i, 1);
    }

_exit:
    strerr_warni1x("canprot_fini");
    if(canprot_fini()) {
        strerr_warnwu1x("canprot_fini");
    }
    
    return 0;
}