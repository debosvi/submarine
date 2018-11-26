
#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_alarm_set(const J1939_timerId_t timerId, const J1939_time_t first_ms, const J1939_time_t cyclic_ms) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    
    if(timerId>=J1939_OS_main_ctx_g.max_timers) { _ret=J1939_ERR_BADID; goto exit; }
    if(!cyclic_ms) { _ret=J1939_ERR_BADID; goto exit; }
    
    J1939_disable_it();
    
    J1939_OS_main_ctx_g.timers[timerId].timeout_ms = first_ms;
    J1939_OS_main_ctx_g.timers[timerId].cyclic_ms = cyclic_ms;
    J1939_OS_main_ctx_g.timers[timerId].running = J1939_TRUE;
    
    J1939_enable_it();
           
exit:
//     if(_ret!=J1939_ERR_SUCCESS) {
//     }
    return _ret;
}
