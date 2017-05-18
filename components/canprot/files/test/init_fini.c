
#include <errno.h>
#include <string.h>

#include <skalibs/strerr2.h>

#include <canprot/canprot.h>

#include "private/canprot_p.h"
#include "restricted/canprot_r.h"

const canprot_msg_t msg1 = CANPROT_MSG_ZERO;
const canprot_msg_t msg2 = CANPROT_MSG_ZERO;

const canprot_sig_t sig11 = CANPROT_SIG_ZERO;
const canprot_sig_t sig12 = CANPROT_SIG_ZERO;
const canprot_sig_t sig21 = CANPROT_SIG_ZERO;
const canprot_sig_t sig22 = CANPROT_SIG_ZERO;
const canprot_sig_t sig23 = CANPROT_SIG_ZERO;

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
    
    strerr_warni1x("canprot_get_msgs_count");
    r=canprot_get_msgs_count();
    if(r<=0) strerr_warnwu1x("canprot_get_msgs_count error");
    
    strerr_warni1x("canprot_get_sigs_count");
    r=canprot_get_sigs_count();
    if(r<=0) strerr_warnwu1x("canprot_get_sigs_count error");
    
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