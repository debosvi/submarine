
#include <malloc.h>

#include "private/J1939_OS_p.h"

#if !defined(J1939_NB_TIMERS)
#error "You must define J1939_NB_TIMERS value in J1939_config.h"
#endif

#if !defined(J1939_NB_TASKS)
#error "You must define J1939_NB_TASKS value in J1939_config.h"
#elif J1939_NB_TASKS>J1939_OS_MAX_TASKS
#error "You must define J1939_NB_TASKS less than 8 in J1939_config.h"
#endif

static J1939_OS_task_cpt_t j1939_os_task_cpt_g[J1939_NB_TASKS];
static J1939_OS_timer_t j1939_os_timers_g[J1939_NB_TIMERS];

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_init_static(void) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;

    J1939_OS_main_ctx_g.tasks_cpt=j1939_os_task_cpt_g;
    J1939_OS_main_ctx_g.max_tasks=J1939_NB_TASKS;
    
    J1939_OS_main_ctx_g.timers=j1939_os_timers_g;        
    J1939_OS_main_ctx_g.max_timers=J1939_NB_TIMERS;
        
    _ret=J1939_OS_init_internal();    
    
// exit:
    if(_ret!=J1939_ERR_SUCCESS) {
        J1939_OS_main_ctx_g = J1939_OS_ctx_zero;
    }
    return _ret;
}
