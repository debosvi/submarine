
#include <stdio.h>
#include <poll.h>

#include <j1939/os/J1939_OS.h>

static J1939_TASK(TASK_0_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

static J1939_TASK(TASK_1_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

static J1939_TASK(TASK_2_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

static J1939_ALARM_CALLBACK(TIMER_0_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

static J1939_ALARM_CALLBACK(TIMER_1_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

static J1939_ALARM_CALLBACK(TIMER_2_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

static J1939_ALARM_CALLBACK(TIMER_3_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

static J1939_ALARM_CALLBACK(TIMER_4_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

static J1939_ALARM_CALLBACK(TIMER_5_ID) {
    fprintf(stderr, "%s: call\n", __PRETTY_FUNCTION__);
}

const J1939_OS_task_t J1939_tasks_all[J1939_NB_TASKS] = {
    J1939_TASK_DEF(TASK_0_ID),
    J1939_TASK_DEF(TASK_1_ID),
    J1939_TASK_DEF(TASK_2_ID),
};

const J1939_OS_task_t* J1939_tasks_g = &J1939_tasks_all[0];

const J1939_OS_timerCB_t J1939_timers_all[J1939_NB_TIMERS] = {
    J1939_ALARM_CALLBACK_DEF(TIMER_0_ID),
    J1939_ALARM_CALLBACK_DEF(TIMER_1_ID),
    J1939_ALARM_CALLBACK_DEF(TIMER_2_ID),
    J1939_ALARM_CALLBACK_DEF(TIMER_3_ID),
    J1939_ALARM_CALLBACK_DEF(TIMER_4_ID),
    J1939_ALARM_CALLBACK_DEF(TIMER_5_ID),

};

const J1939_OS_timerCB_t* J1939_timers_g = &J1939_timers_all[0];

int main(void) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
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