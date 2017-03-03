
#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_time_t J1939_OS_alarm_gettime(const J1939_timerId_t timerId) {
    J1939_time_t _time=J1939_INVALID_TIMEOUT;
    
    if(timerId>=J1939_OS_main_ctx_g.max_timers) { goto exit; }
    
    J1939_disable_it();
    
    if(J1939_OS_main_ctx_g.timers[timerId].running == J1939_TRUE) {
        _time = J1939_OS_main_ctx_g.timers[timerId].timeout_ms; 
    }
    
    J1939_enable_it();
           
exit:
//     if(_time==J1939_INVALID_TIMEOUT) {
//     }
    return _time;
}
