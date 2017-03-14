
#include "private/J1939_IL_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_IL_status_t J1939_IL_stop(J1939_IL_shutdown_t mode) {
    J1939_IL_status_t _ret=J1939_IL_ERR_OK;
#if defined(J1939_IL_IL_PERIODIC_TX_USED) || defined(J1939_IL_WITH_TX_CONTROL)
    J1939_IL_IPDU_idx_t i=0;
#endif
    
    switch(mode) {
        case J1939_IL_SHUT_IMMEDIATE:
            /*  arreter tous les timers : */
            /*     - des messages periodiques */
            /*     - des deadlines monitoring en emission */
            /*     - des deadlines monitoring en reception */

#ifdef J1939_IL_IL_PERIODIC_TX_USED
            for (i=0; i<J1939_IL_NB_IPDU_PERIODIC_EMS; i++) {
                J1939_OS_alarm_reset(J1939_IL_periodic_t[i].id);
            }
#endif

#ifdef J1939_IL_WITH_TX_CONTROL
            for (i=0 ; i<J1939_IL_NB_IPDU_TX_MONITORED; i++) {
#ifdef J1939_IL_WITH_TX_MIN_DELAY_TIME
                if(Tab_IPDUControlTrf[i].MinimumDelayTime != (UINT16)0) {
                    J1939_OS_alarm_reset(Tab_IPDUControlTrf[i].MDT_TimerID);
                }
#endif // J1939_IL_WITH_TX_MIN_DELAY_TIME
            }
#endif // J1939_IL_WITH_TX_CONTROL


#ifdef J1939_IL_RX_MONITORING_USED
            J1939_IL_stop_RX_monitoring();
#endif

            break;
 
        default: break;
    }

    
    return _ret;
}
