
#include <stdio.h>

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
