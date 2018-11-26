
#ifndef _J1939_IL_PRIV_H__
#define _J1939_IL_PRIV_H__

#include "j1939/il/J1939_IL.h"

#include "j1939_section_1.inc"

typedef uint8_t J1939_IL_IPDU_idx_t;     /**<  255 ipdus possible (ems + rcp) dans la NM */

typedef struct {
#ifdef J1939_FIFO_RECEIVED_USED
    J1939_BOOL              active;         /**< Indique si la tache interaction est activee */
    J1939_IL_IPDU_idx_t     ipdu_rcv[J1939_IL_SIZE_BUF_IPDU_RCP]; /**< Buffer de reception des IPDU */
    uint8_t                 idx_add;        /**< Index de gestion du buffer de reception */
    uint8_t                 idx_read;       /**< Index de gestion du buffer de reception */
#else
    J1939_IL_IPDU_idx_t     ipdu_rcv;       /**< Indique l'identifiant de l'IPDU recu */
#endif
} J1939_IL_context_t;

extern J1939_IL_context_t J1939_IL_main_ctx_g;
#ifdef J1939_FIFO_RECEIVED_USED
#define J1939_IL_CONTEXT_ZERO   { .active=J1939_FALSE, .idx_add=0, .idx_read=0, .ipdu_rcv={0} }
#else                           
#define J1939_IL_CONTEXT_ZERO   { .ipdu_rcv=0 }
#endif

extern const J1939_IL_context_t J1939_IL_ctx_zero;

#if defined(J1939_IL_INITIAL_VALUE_USED)
extern J1939_IL_status_t J1939_IL_init_all(J1939_IL_IPDU_idx_t max);
#endif

#include "j1939_section_0.inc"

#endif // _J1939_IL_PRIV_H__

/*----------------------------- end of file -----------------------------*/
