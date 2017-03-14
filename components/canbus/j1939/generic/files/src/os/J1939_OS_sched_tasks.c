
#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_sched_tasks(void) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    J1939_taskId_t idx = 0;

    /*  Tasks management */
    if(J1939_OS_main_ctx_g.active_task) {
        J1939_OS_main_ctx_g.current_task = 0;
        idx = 1;
        while(J1939_OS_main_ctx_g.current_task < J1939_NB_TASKS) {
            if(J1939_OS_main_ctx_g.active_task & idx) {
                J1939_tasks_g[J1939_OS_main_ctx_g.current_task]();
            }

            idx = idx << 1;
            J1939_OS_main_ctx_g.current_task++;
        }
    }
           
// exit:
//     if(_ret!=J1939_ERR_SUCCESS) {
//     }
    return _ret;
}
