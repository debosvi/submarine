
#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_alarm_reset(const J1939_timerId_t timerId) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    
    if(timerId>=J1939_OS_main_ctx_g.max_timers) { _ret=J1939_ERR_BADID; goto exit; }
    
    J1939_disable_it();
    
    J1939_OS_main_ctx_g.timers[timerId].running = J1939_FALSE;
    
    J1939_enable_it();
           
exit:
//     if(_ret!=J1939_ERR_SUCCESS) {
//     }
    return _ret;
}
