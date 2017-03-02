
#ifndef __J1939_OS_H__
#define __J1939_OS_H__

#include "j1939/os/J1939_Types.h"

// #include "p_J1939_OS.h"

#define J1939_ALARM_CALLBACK(AlarmID)       void AlarmID##_callback (void)  /**< Sub-task name */
#define J1939_ALARM_CALLBACK_BIS(AlarmID)   J1939_ALARM_CALLBACK(AlarmID)   /**< Sub-task name */
#define J1939_ALARM_CALLBACK_DEF(AlarmID)   AlarmID##_callback              /**< Sub-task name */

#define J1939_INVALID_TIMEOUT       (uint16_t)0xFFFF

#define J1939_TASK_DEF(taskID)      taskID##_func               /**< Sub-task name */
#define J1939_TASK(taskID)          void taskID##_func(void)    /**< Sub-task definition */

#define J1939_ISR(Function) void Function(void)

#define J1939_Disable_Interrupts()
#define J1939_Enable_Interrupts()

#define J1939_Interrupt_Enter()  
#define J1939_Interrupt_Exit() 

#define MAX_TASK_ACTIVATION (uint8_t)255

typedef void (*J1939_OS_task_t)(void);
typedef void (*J1939_OS_timerCB_t)(void);

typedef uint8_t     J1939_timerId_t;
typedef uint8_t     J1939_taskId_t;
typedef uint16_t    J1939_time_t;

typedef enum {
    J1939_ERR_SUCCESS= 0,   /**< No error */
    J1939_ERR_NULLPTR,      /**< NULL pointer argument */
    J1939_ERR_BADID,        /**< Bad timer or task identifier */
    J1939_ERR_INVAL,        /**< Invalid argument(s), if not J1939_ERR_BADID */
    J1939_ERR_ALLOC,        /**< Allocation failed */
    J1939_ERR_COUNT         /**< Error count */
} J1939_error_t;

extern J1939_error_t J1939_OS_init(void);
extern J1939_error_t J1939_ActivateTask(J1939_taskId_t taskId);
extern J1939_error_t J1939_TerminateTask(void);
extern J1939_error_t J1939_SchedulerTimers(void);
extern J1939_error_t J1939_SchedulerTasks(void);
extern J1939_error_t J1939_CopyBytes (void* dest, const void* src, uint8_t lg );
extern J1939_error_t J1939_SetAlarm(J1939_timerId_t timerId, J1939_time_t first_ms, J1939_time_t cyclic_ms);
extern J1939_error_t J1939_CancelAlarm(J1939_timerId_t timerId);
extern J1939_time_t  J1939_GetAlarmTime(J1939_timerId_t timerId);

// specific part APIs which MUST be implemented
extern J1939_timerId_t J1939_OS_getMaxTimers(void);     /**< Used at least by J1939_OS_Init method */
extern J1939_taskId_t J1939_OS_getMaxTasks(void);       /**< Used at least by J1939_OS_Init method */

#endif // __J1939_OS_H__
/*-------------------------------- end of file -------------------------------*/

