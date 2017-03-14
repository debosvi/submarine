
#ifndef _J1939_OS_PRIV_H__
#define _J1939_OS_PRIV_H__

#include "j1939/os/J1939_OS.h"

typedef struct {
    J1939_BOOL      running;        /**< indicates if timer is running */
    J1939_time_t    timeout_ms;     /**< timeout elapse target */
    J1939_time_t    cyclic_ms;      /**< cyclic timeout period */
} J1939_OS_timer_t;
#define J1939_OS_TIMER_ZERO { .running=J1939_FALSE, .timeout_ms=J1939_INVALID_TIMEOUT, .cyclic_ms=J1939_INVALID_TIMEOUT }
extern const J1939_OS_timer_t J1939_OS_timer_zero;

typedef uint8_t J1939_OS_task_cpt_t;
#define J1939_OS_MAX_TASK_ACTIVATION    (J1939_OS_task_cpt_t)0xff
#define J1939_OS_MAX_TASKS              (8)

typedef struct {
    J1939_OS_task_cpt_t*    tasks_cpt;      /**< Compteur d'activation des tâches */
    J1939_OS_timer_t*       timers;         /**< gestion des compteurs */
    
    J1939_timerId_t         max_timers;
    J1939_taskId_t          max_tasks;    
    
    J1939_taskId_t          active_task;    /**< Variable pour l'activation des tâches */
    J1939_taskId_t          current_task;   /**< Tâche en cours d'exécution */
} J1939_OS_context_t;

extern J1939_OS_context_t J1939_OS_main_ctx_g;
#define J1939_OS_CONTEXT_ZERO   { .tasks_cpt=0, .timers=0, .active_task=0, .current_task=0, .max_timers=0, .max_tasks=0 }
extern const J1939_OS_context_t J1939_OS_ctx_zero;

extern J1939_error_t J1939_OS_init_internal(void);

#endif // _J1939_OS_PRIV_H__

/*----------------------------- end of file -----------------------------*/
