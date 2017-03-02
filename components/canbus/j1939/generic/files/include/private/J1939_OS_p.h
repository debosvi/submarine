
#ifndef _J1939_OS_PRIV_H__
#define _J1939_OS_PRIV_H__

#include "j1939/os/J1939_OS.h"

typedef struct {
    J1939_BOOL      running;    /**< Indicate if timer is running */
    J1939_time_t    timeout;    /**< Time when the timer timeout will be elapsed */
    J1939_time_t    period;     /**< Cyclic period */
} J1939_OS_timer_t;

typedef uint8_t J1939_OS_task_cpt_t;

typedef struct {
    J1939_OS_task_cpt_t*    tasks_cpt;      /**< Compteur d'activation des tâches */
    J1939_OS_timer_t*       timers;         /**< gestion des compteurs */
    
    J1939_taskId_t          active_task;    /**< Variable pour l'activation des tâches */
    J1939_taskId_t          current_task;   /**< Tâche en cours d'exécution */
} J1939_OS_context_t;

extern J1939_OS_context_t J1939_OS_main_ctx_g;
#define J1939_OS_CONTEXT_ZERO   { .tasks_cpt=0, .timers=0, .active_task=0, .current_task=0 }
extern const J1939_OS_context_t J1939_OS_ctx_zero;

#endif // _J1939_OS_PRIV_H__

/*----------------------------- end of file -----------------------------*/
