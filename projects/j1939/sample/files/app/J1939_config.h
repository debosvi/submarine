
#ifndef __J1939_CONFIG_H__
#define __J1939_CONFIG_H__

#define J1939_OS_USE_MEM_ALLOCATOR  0
#define J1939_IL_OPTIM_SIZE_USED    0

#define TIMER_0_ID  (0)
#define TIMER_1_ID  (1)
#define TIMER_2_ID  (2)
#define TIMER_3_ID  (3)
#define TIMER_4_ID  (4)
#define TIMER_5_ID  (5)
#define J1939_NB_TIMERS     (6)

#define TASK_0_ID   (0)
#define TASK_1_ID   (1)
#define TASK_2_ID   (2)
#define J1939_NB_TASKS      (3)

// TBD, generated part
#define J1939_IL_SIZE_BUF_IPDU_RCP  (1)
#define J1939_IL_NB_MSG             (1)

// TBC
#define J1939_IL_FIFO_RECEIVED_USED
#define J1939_IL_BUFFER_RECEIVED_USED

#define J1939_IL_PERIODIC_TX_USED
#define J1939_IL_NB_IPDU_PERIODIC_EMS   (2)

#define J1939_IL_NB_MSG_TRF_STAT (1)

#define J1939_IL_RX_MONITORING_USED

#define J1939_IL_DEFAULT_VALUE_USED
#define J1939_IL_INITIAL_VALUE_USED
    
#endif // __J1939_CONFIG_H__
