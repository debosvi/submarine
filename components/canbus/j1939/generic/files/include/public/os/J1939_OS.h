
#ifndef __J1939_OS_H__
#define __J1939_OS_H__

#include "J1939_config.h"		// from specific part of J1939 stack

#include "j1939/os/J1939_Types.h"

#define J1939_ALARM_CALLBACK(AlarmID)       void AlarmID##_callback (void)  /**< Sub-task name */
#define J1939_ALARM_CALLBACK_BIS(AlarmID)   J1939_ALARM_CALLBACK(AlarmID)   /**< Sub-task name */
#define J1939_ALARM_CALLBACK_DEF(AlarmID)   AlarmID##_callback              /**< Sub-task name */

#define J1939_TASK_DEF(taskID)      taskID##_func               /**< Sub-task name */
#define J1939_TASK(taskID)          void taskID##_func(void)    /**< Sub-task definition */

#define J1939_ISR(Function) void Function(void)

#define J1939_disable_it()
#define J1939_enable_it()

#define J1939_it_enter()  
#define J1939_it_exit() 

typedef void (*J1939_OS_task_t)(void);
typedef void (*J1939_OS_timerCB_t)(void);

extern const J1939_OS_task_t* J1939_tasks_g;
extern const J1939_OS_timerCB_t* J1939_timers_g;

typedef uint8_t     J1939_timerId_t;
typedef uint8_t     J1939_taskId_t;
typedef uint16_t    J1939_time_t;

#define J1939_INVALID_TIMEOUT       (J1939_time_t)0xFFFF

typedef enum {
    J1939_ERR_SUCCESS= 0,   /**< No error */
    J1939_ERR_NULLPTR,      /**< NULL pointer argument */
    J1939_ERR_BADID,        /**< Bad timer or task identifier */
    J1939_ERR_INVAL,        /**< Invalid argument(s), if not J1939_ERR_BADID */
    J1939_ERR_ALLOC,        /**< Allocation failed */
    J1939_ERR_ALREADY,      /**< request already done */
    J1939_ERR_COUNT         /**< Error count */
} J1939_error_t;

extern J1939_error_t J1939_OS_init_static(void);
extern J1939_error_t J1939_OS_init_alloc(const J1939_timerId_t max_timers, const J1939_taskId_t max_tasks);

// default static init
#define J1939_OS_init J1939_OS_init_static

extern J1939_error_t J1939_OS_activate_task(const J1939_taskId_t taskId);
extern J1939_error_t J1939_OS_term_current_task(void);

extern J1939_error_t J1939_OS_sched_timers(void);
extern J1939_error_t J1939_OS_sched_tasks(void);

extern J1939_error_t J1939_OS_alarm_set(const J1939_timerId_t timerId, const J1939_time_t first_ms, const J1939_time_t cyclic_ms);
extern J1939_error_t J1939_OS_alarm_reset(const J1939_timerId_t timerId);
extern J1939_time_t  J1939_OS_alarm_gettime(const J1939_timerId_t timerId);

extern J1939_error_t J1939_OS_copymem(void* dest, const void* src, uint8_t lg );

#endif // __J1939_OS_H__
/*-------------------------------- end of file -------------------------------*/

