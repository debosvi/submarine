
#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_activate_task(const J1939_taskId_t taskId) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    
    if(taskId>=J1939_OS_main_ctx_g.max_tasks) { _ret=J1939_ERR_BADID; goto exit; }
    
    J1939_disable_it();
    
    J1939_OS_main_ctx_g.active_task |= _BITWISE_GEN_8(taskId);
    
    if(J1939_OS_main_ctx_g.tasks_cpt[taskId] < J1939_OS_MAX_TASK_ACTIVATION) {
        J1939_OS_main_ctx_g.tasks_cpt[taskId]++;
    }
    
    J1939_enable_it();
           
exit:
//     if(_ret!=J1939_ERR_SUCCESS) {
//     }
    return _ret;
}
