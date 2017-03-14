
#include "private/J1939_IL_p.h"

#ifdef J1939_IL_INITIAL_VALUE_USED

///////////////////////////////////////////////////////////////////////////////
J1939_IL_status_t J1939_IL_init_all(J1939_IL_IPDU_idx_t max) {
    J1939_IL_status_t _ret=J1939_IL_ERR_OK;
    J1939_IL_IPDU_idx_t i;    /*  indice de boucle pour chaque msg de TabIDMessage */

    for (i=0; i<max; i++) {
        J1939_IL_IPDU_idx_t idx = TabIDMessage[i].msgIdx;
        switch ( TabIDMessage[i].typeMessage ) {

#if defined(NB_MSG_EMS_STAT) && defined(NB_MSG_TRF_STAT)
            case EMS_STATIC_MSG:
            {
                J1939_IL_static_trf_elt_t *p=&J1939_IL_static_trf_elt_g[idx];
#ifndef OPTIMIZATION_ORDERING_USED
                (*p->ptrTrf) (
                    TabIPDUStaticEms[TabIDIpdu[p->ipduIdx].ipduIdx].dataPtr, 
                    p->init,
                    p->nb_bits, 
                    p->bit_pos);
#else
                TRF_FUNCTION(
                    TabIPDUStaticEms[TabIDIpdu[p->ipduIdx].ipduIdx].dataPtr,
                    p->init,
                    p->nb_bits, 
                    p->bit_pos);
#endif
                break;
#endif

#ifdef NB_MSG_RCP_STAT
            case RCP_STATIC_MSG:
                /*  initialisation du buffer de reception octet par octet */
                LGM_CopyBytes(TabStaticStorage[idx].dataPtr, TabStaticStorage[idx].initialValue,
                    TabStaticStorage[idx].sizeInBytes);
                break;
#endif

        default: break;
    }
    
    return _ret;
}

#endif /*  J1939_IL_INITIAL_VALUE_USED */
