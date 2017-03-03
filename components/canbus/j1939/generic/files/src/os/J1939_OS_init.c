
#include <malloc.h>

#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_init(const J1939_timerId_t max_timers, const J1939_taskId_t max_tasks) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    void *alloc=0;
    
    if(!max_timers || !max_tasks) { _ret=J1939_ERR_INVAL; goto exit; }
    
    alloc=malloc(max_tasks*sizeof(J1939_OS_task_cpt_t));
    if(!alloc) { _ret=J1939_ERR_ALLOC; goto exit; }
    J1939_OS_main_ctx_g.tasks_cpt=alloc;
    J1939_OS_main_ctx_g.max_tasks=max_tasks;
    
    alloc=malloc(max_timers*sizeof(J1939_OS_timer_t));
    if(!alloc) { _ret=J1939_ERR_ALLOC; goto exit; }
    J1939_OS_main_ctx_g.timers=alloc;        
    J1939_OS_main_ctx_g.max_timers=max_timers;
        
    {
        J1939_timerId_t i=0;
        for(; i<J1939_OS_main_ctx_g.max_timers; i++)
            J1939_OS_main_ctx_g.timers[i] = J1939_OS_timer_zero;
    }
    
    {
        J1939_taskId_t i=0;
        for(; i<J1939_OS_main_ctx_g.max_tasks; i++)
            J1939_OS_main_ctx_g.tasks_cpt[i] = 0;
    }
    
    
exit:
    if(_ret!=J1939_ERR_SUCCESS) {
        if(J1939_OS_main_ctx_g.tasks_cpt) free(J1939_OS_main_ctx_g.tasks_cpt);
        if(J1939_OS_main_ctx_g.timers) free(J1939_OS_main_ctx_g.timers);
        J1939_OS_main_ctx_g = J1939_OS_ctx_zero;
    }
    return _ret;
}
