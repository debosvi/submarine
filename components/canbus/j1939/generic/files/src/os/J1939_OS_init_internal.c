
#include <malloc.h>

#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_init_internal(void) {
    if(J1939_OS_main_ctx_g.timers && J1939_OS_main_ctx_g.max_timers) {
        J1939_timerId_t i=0;
        for(; i<J1939_OS_main_ctx_g.max_timers; i++)
            J1939_OS_main_ctx_g.timers[i] = J1939_OS_timer_zero;
    }
    
    if(J1939_OS_main_ctx_g.tasks_cpt && J1939_OS_main_ctx_g.max_tasks) {
        J1939_taskId_t i=0;
        for(; i<J1939_OS_main_ctx_g.max_tasks; i++)
            J1939_OS_main_ctx_g.tasks_cpt[i] = 0;
    }    
    return J1939_ERR_SUCCESS;
}
