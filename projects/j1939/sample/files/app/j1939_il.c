
#include <j1939/il/J1939_IL.h>

const J1939_IL_periodic_t J1939_IL_periodic_tx_g[J1939_IL_NB_IPDU_PERIODIC_EMS] = {
    /* Table des périodes pour les I-PDUs périodiques */
    { .period=1000, .first=1, TIMER_0_ID },	/* TIMER_0_ID */
    { .period=1000, .first=1, TIMER_1_ID },	/* TIMER_1_ID */
};