
#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_term_current_task(void) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    
    J1939_disable_it();
   
    if(J1939_OS_main_ctx_g.tasks_cpt[J1939_OS_main_ctx_g.current_task]) {
        J1939_OS_main_ctx_g.tasks_cpt[J1939_OS_main_ctx_g.current_task]--;
    }
    
    if(!J1939_OS_main_ctx_g.tasks_cpt[J1939_OS_main_ctx_g.current_task]) {
        J1939_taskId_t idx = _BITWISE_GEN_8(J1939_OS_main_ctx_g.current_task);
        J1939_OS_main_ctx_g.active_task &= ~idx;
    }
    
    J1939_enable_it();
           
// exit:
//     if(_ret!=J1939_ERR_SUCCESS) {
//     }
    return _ret;
}
