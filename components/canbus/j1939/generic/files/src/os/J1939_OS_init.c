
#include <malloc.h>

#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_init(void) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    void *alloc=0;
    
    J1939_timerId_t m1=J1939_OS_getMaxTimers();
    J1939_taskId_t m2=J1939_OS_getMaxTasks();
    
    if(!m1 || !m2) { _ret=J1939_ERR_BADID; goto exit; }
    
    alloc=malloc(m1*sizeof(J1939_OS_task_cpt_t));
    if(!alloc) { _ret=J1939_ERR_ALLOC; goto exit; }
        
    
exit:
    if(_ret!=J1939_ERR_SUCCESS) {
        if(J1939_OS_main_ctx_g.tasks_cpt) free(J1939_OS_main_ctx_g.tasks_cpt);
        if(J1939_OS_main_ctx_g.timers) free(J1939_OS_main_ctx_g.timers);
        J1939_OS_main_ctx_g = J1939_OS_ctx_zero;
    }
    return _ret;
}
