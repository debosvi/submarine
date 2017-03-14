
#include <stdio.h>
#include <poll.h>

#include <j1939/os/J1939_OS.h>
#include <j1939/il/J1939_IL.h>

int main(void) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    J1939_IL_status_t _status=J1939_IL_ERR_OK;
    int i=0;
    
    _ret=J1939_OS_init();
    if(_ret != J1939_ERR_SUCCESS)
        fprintf(stderr, "%s: J1939_OS_init error: %d\n", __PRETTY_FUNCTION__, _ret);
    
    _ret=J1939_OS_activate_task(TASK_1_ID);
    if(_ret != J1939_ERR_SUCCESS)
        fprintf(stderr, "%s: J1939_OS_activate_task error: %d\n", __PRETTY_FUNCTION__, _ret);
    
    _ret=J1939_OS_alarm_set(TIMER_0_ID, 5, 10);
    if(_ret != J1939_ERR_SUCCESS)
        fprintf(stderr, "%s: J1939_OS_alarm_set TIMER_0_ID error: %d\n", __PRETTY_FUNCTION__, _ret);
    
    _ret=J1939_OS_alarm_set(TIMER_1_ID, 15, 100);
    if(_ret != J1939_ERR_SUCCESS)
        fprintf(stderr, "%s: J1939_OS_alarm_set TIMER_1_ID error: %d\n", __PRETTY_FUNCTION__, _ret);
    
    _ret=J1939_OS_alarm_set(TIMER_2_ID, 25, 55);
    if(_ret != J1939_ERR_SUCCESS)
        fprintf(stderr, "%s: J1939_OS_alarm_set TIMER_2_ID error: %d\n", __PRETTY_FUNCTION__, _ret);
    
    _ret=J1939_OS_alarm_set(TIMER_3_ID, 2, 1);
    if(_ret != J1939_ERR_SUCCESS)
        fprintf(stderr, "%s: J1939_OS_alarm_set TIMER_3_ID error: %d\n", __PRETTY_FUNCTION__, _ret);
    
    _ret=J1939_OS_alarm_set(TIMER_4_ID, 0, 50);
    if(_ret != J1939_ERR_SUCCESS)
        fprintf(stderr, "%s: J1939_OS_alarm_set TIMER_4_ID error: %d\n", __PRETTY_FUNCTION__, _ret);
    
    _ret=J1939_OS_alarm_set(TIMER_5_ID, 7, 33);
    if(_ret != J1939_ERR_SUCCESS)
        fprintf(stderr, "%s: J1939_OS_alarm_set TIMER_5_ID error: %d\n", __PRETTY_FUNCTION__, _ret);
    
    _status=J1939_IL_start(J1939_IL_OPE);
    if(_status != J1939_IL_ERR_OK)
        fprintf(stderr, "%s: J1939_IL_start error: %d\n", __PRETTY_FUNCTION__, _status);
    
    _status=J1939_IL_stop(J1939_IL_SHUT_IMMEDIATE);
    if(_status != J1939_IL_ERR_OK)
        fprintf(stderr, "%s: J1939_IL_start error: %d\n", __PRETTY_FUNCTION__, _status);
    
    while(i++<128) {
        fprintf(stderr, "%s: loop %d\n", __PRETTY_FUNCTION__, i);
        
        _ret=J1939_OS_sched_tasks();
        if(_ret != J1939_ERR_SUCCESS)
            fprintf(stderr, "%s: J1939_OS_sched_tasks error: %d\n", __PRETTY_FUNCTION__, _ret);
        
        _ret=J1939_OS_sched_timers();
        if(_ret != J1939_ERR_SUCCESS)
            fprintf(stderr, "%s: J1939_OS_sched_timers error: %d\n", __PRETTY_FUNCTION__, _ret);
        
        poll(0,0,10);
    }
    
    return 0;
}