
#include "private/J1939_IL_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_IL_status_t J1939_IL_start(J1939_IL_mode_t mode) {
    J1939_IL_status_t _ret=J1939_IL_ERR_OK;
    
#if defined(WITH_TX_MIN_DELAY_TIME) || defined (IL_RX_MONITORING_USED)
    uint8_t i=0;
#endif

    J1939_IL_main_ctx_g = J1939_IL_ctx_zero;

#if !defined(J1939_IL_INITIAL_VALUE_USED)
    (void)mode;
#else

    switch ( mode ) {
        case J1939_IL_OPE:
        /*  initialisation des messages de transfert (et des ipdus associes) */
        /*  et initialisation des messages de reception */
        {
            _ret = J1939_IL_init_all(J1939_IL_NB_MSG);

#ifdef WITH_TX_MIN_DELAY_TIME
            for (i=(UINT8)0 ; i<NB_IPDU_TX_MONITORED; i++)
            {
                if(Tab_IPDUControlTrf[i].ProtectionEnCours != NULL)
                {
                    *(Tab_IPDUControlTrf[i].ProtectionEnCours) = (LGM_BOOL)LGM_FALSE;
                }
                if(Tab_IPDUControlTrf[i].EmissionEnCours != NULL)
                {
                    *(Tab_IPDUControlTrf[i].EmissionEnCours) = (LGM_BOOL)LGM_FALSE;
                }
                if(Tab_IPDUControlTrf[i].DemandeEmission != NULL)
                {
                    *(Tab_IPDUControlTrf[i].DemandeEmission) = (LGM_BOOL)LGM_FALSE;
                }
#ifdef MIXED_FRAME_RETRIGGERRED_BY_EVENT
                if(Tab_IPDUControlTrf[i].EventTransmission != NULL)
                {
                    *(Tab_IPDUControlTrf[i].EventTransmission) = (LGM_BOOL)LGM_FALSE;
                }
#endif /* MIXED_FRAME_RETRIGGERRED_BY_EVENT */
            }
#endif /* WITH_TX_MIN_DELAY_TIME */

#ifdef IL_RX_MONITORING_USED
            for (i=(UINT8)0 ; i<NB_IPDU_STAT_RCP; i++)
            {
                if(TabIPDUStaticRcp[i].firstDM != (ttime)0)
                {
                    TabTimeOutWaitTime[TabIPDUStaticRcp[i].DMIdx] = TabIPDUStaticRcp[i].firstDM;
                }
            }
#endif /* IL_RX_MONITORING_USED */

#ifdef NB_IPDU_COND
            for (i=(UINT8)0 ; i<NB_IPDU_COND; i++)
            {
                TabCondition[i] = (LGM_BOOL)LGM_TRUE;
            }
#endif /* NB_IPDU_COND */
        }            
            break;
        
        case J1939_IL_MAINT:
                _ret = J1939_IL_ERR_NOT_IMPL;
                break;

        default: break;
    }

#endif /* J1939_IL_INITIAL_VALUE_USED */
           
    return _ret;
}
