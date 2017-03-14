
#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_sched_timers(void) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    J1939_timerId_t timer_id = 0;

    /*  Timer management */
    for(; timer_id < J1939_NB_TIMERS; timer_id++) {
        J1939_disable_it();
        if(J1939_OS_main_ctx_g.timers[timer_id].running == J1939_TRUE)
        {
            J1939_OS_main_ctx_g.timers[timer_id].timeout_ms = J1939_OS_main_ctx_g.timers[timer_id].timeout_ms - 1;
            if(!J1939_OS_main_ctx_g.timers[timer_id].timeout_ms) {
                if(J1939_OS_main_ctx_g.timers[timer_id].cyclic_ms) {
                    J1939_OS_main_ctx_g.timers[timer_id].timeout_ms = J1939_OS_main_ctx_g.timers[timer_id].cyclic_ms;
                }
                else {
                    J1939_OS_main_ctx_g.timers[timer_id].running = J1939_FALSE;
                }
                J1939_enable_it();
                J1939_timers_g[timer_id]();
            }
            else {
                /* Nothing else to do, wait timeout to be reached */
                J1939_enable_it();
            }
        }
        else {
            /* Timer is not running, do nothing */
            J1939_enable_it();
        }
    }
           
// exit:
//     if(_ret!=J1939_ERR_SUCCESS) {
//     }
    return _ret;
}
