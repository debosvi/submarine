
#include <errno.h>
#include <string.h>

#include <skalibs/strerr2.h>

#include <canprot/canprot.h>
#include <private/canprot_p.h>
#include <restricted/canprot_r.h>

const canprot_msg_t msg1 = { .id=(canbus_addr_t)0x00f00100, .type=CANPROT_MSG_TYPE_TX, .cycle=CANPROT_MSG_CYCLE_ONESHOT, .ms=0, .bytes=3 };
const canprot_msg_t msg2 = { .id=(canbus_addr_t)0x00f00200, .type=CANPROT_MSG_TYPE_TX, .cycle=CANPROT_MSG_CYCLE_CYCLIC, .ms=1000, .bytes=5 };

#define CANPROT_SIGNAL_11_ID    (0)
const canbus_data_t sig11_def[] = { 0x54 };
const canbus_data_t sig11_init[] = { 0x54 };
#define CANPROT_SIGNAL_12_ID    (1)
const canbus_data_t sig12_def[] = { 0xa5, 0x87 };
const canbus_data_t sig12_init[] = { 0xa5, 0x87 };
 
const canprot_sig_t sig11 = { .msg=&msg1, .pos=0, .bits=8, .def=sig11_def, .init=sig11_init, .def_sz=1, .init_sz=1 };
const canprot_sig_t sig12 = { .msg=&msg1, .pos=8, .bits=16, .def=sig11_def, .init=sig11_init, .def_sz=2, .init_sz=2 };

#define CANPROT_SIGNAL_21_ID    (2)
const canbus_data_t sig21_def[] = { 0x45, 0x87 };
const canbus_data_t sig21_init[] = { 0x45, 0x87 };
#define CANPROT_SIGNAL_22_ID    (3)
const canbus_data_t sig22_def[] = { 0xbc };
const canbus_data_t sig22_init[] = { 0xbc };
#define CANPROT_SIGNAL_23_ID    (4)
const canbus_data_t sig23_def[] = { 0x5a, 0x15 };
const canbus_data_t sig23_init[] = { 0x5a, 0x15 };

const canprot_sig_t sig21 = { .msg=&msg2, .pos=0, .bits=16, .def=sig21_def, .init=sig21_init, .def_sz=2, .init_sz=2 };
const canprot_sig_t sig22 = { .msg=&msg2, .pos=16, .bits=8, .def=sig22_def, .init=sig22_init, .def_sz=1, .init_sz=1 };
const canprot_sig_t sig23 = { .msg=&msg2, .pos=24, .bits=16, .def=sig23_def, .init=sig23_init, .def_sz=2, .init_sz=2 };

const canprot_msg_t* canprot_msgs_decl_g[] = { &msg1, &msg2, 0 };
const canprot_sig_t* canprot_sigs_decl_g[] = { &sig11, &sig12, &sig21, &sig22, &sig23, 0 };

#define CANPROT_MSG_MAX_ID      (2)
#define CANPROT_SIGNAL_MAX_ID   (5)
canprot_msg_state_t canprot_msg_cur_g[CANPROT_MSG_MAX_ID];    
    
int main(void) {
    int r=-1;
    
    PROG = PROG_NAME;
    
    strerr_warni1x("canprot_init");
    if(canprot_init()) {
        strerr_warnwu1x("canprot_init");
        goto _exit;
    }
    
    strerr_warni1x("canprot_check_valid_decl");
    r=canprot_check_valid_decl();
    if(r) strerr_warnwu1x("canprot_check_valid_decl error");    
    
_exit:
    strerr_warni1x("canprot_fini");
    if(canprot_fini()) {
        strerr_warnwu1x("canprot_fini");
    }
    
    return 0;
}