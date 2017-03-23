
/* Standard includes. */
#include <stdio.h>
#include <signal.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"

#include "task.h"


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void sig_handler(const int sig) {
    printf("interruption handled = %d.\n", sig);
    
    if(sig==SIGINT)
        vTaskEndScheduler();
    
}

static const char * const myTaskName  = "myTaskName";
#define NB_STACK_WORD   (256)
static int myTaskStack[NB_STACK_WORD];
static const unsigned myTaskParam = 0x1234;
static StaticTask_t myTaskData;
static TaskHandle_t myTaskHandle;

#define MYTASK_FREQUENCY_MS			( 1000 / portTICK_PERIOD_MS )

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void myTaskFct(void *parg) {
    TickType_t xNextWakeTime;
    unsigned arg = *(unsigned*)parg;
    const TickType_t xBlockTime = pdMS_TO_TICKS( MYTASK_FREQUENCY_MS );
    
    printf("%s: arg(%u)\n", __PRETTY_FUNCTION__, arg);
    
    xNextWakeTime = xTaskGetTickCount();

    for( ;; ) {
        printf("%s: loop\n", __PRETTY_FUNCTION__);
        vTaskDelayUntil( &xNextWakeTime, xBlockTime );
    }
}


static const char * const myTaskName2  = "myTaskName2";
#define NB_STACK_WORD2   (256)
static int myTaskStack2[NB_STACK_WORD2];
static const unsigned myTaskParam2 = 0x4567;
static StaticTask_t myTaskData2;
static TaskHandle_t myTaskHandle2;

#define MYTASK2_FREQUENCY_MS			( 300 / portTICK_PERIOD_MS )

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void myTaskFct2(void *parg) {
    TickType_t xNextWakeTime;
    unsigned arg = *(unsigned*)parg;
    const TickType_t xBlockTime = pdMS_TO_TICKS( MYTASK2_FREQUENCY_MS );
    
    printf("%s: arg(%u)\n", __PRETTY_FUNCTION__, arg);
    
    xNextWakeTime = xTaskGetTickCount();

    for( ;; ) {
        printf("%s: loop\n", __PRETTY_FUNCTION__);
        vTaskDelayUntil( &xNextWakeTime, xBlockTime );
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main( void ) {
    printf("%s: start\n", __PRETTY_FUNCTION__);
    
    signal(SIGINT, sig_handler);
    
    myTaskHandle = xTaskCreateStatic(
        myTaskFct, 
        myTaskName,
        NB_STACK_WORD,
        (void*)&myTaskParam,
        1,
        (void*)&myTaskStack[0],
        &myTaskData);
    printf("%s: task created\n", __PRETTY_FUNCTION__);
    
    myTaskHandle2 = xTaskCreateStatic(
        myTaskFct2, 
        myTaskName2,
        NB_STACK_WORD2,
        (void*)&myTaskParam2,
        1,
        (void*)&myTaskStack2[0],
        &myTaskData2);
    printf("%s: task2 created\n", __PRETTY_FUNCTION__);
        
    vTaskStartScheduler();
    printf("%s: end\n", __PRETTY_FUNCTION__);
            
    while( 1) {
        __asm volatile( "NOP" );
        __asm volatile( "NOP" );
    }
                                 
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void vAssertCalled( unsigned long ulLine, const char * const pcFileName ) {
    printf("%s: line(%lu), file(%s)\n", __PRETTY_FUNCTION__, ulLine, pcFileName);

    taskENTER_CRITICAL();
    while( 1) {
        __asm volatile( "NOP" );
        __asm volatile( "NOP" );
    }
    taskEXIT_CRITICAL();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName ) {
    printf("%s: task name(%s)\n", __PRETTY_FUNCTION__, pcTaskName);
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	vAssertCalled( __LINE__, __FILE__ );
}

#define NB_TIMER_WORD   (32)
static int myTimerStack[NB_TIMER_WORD];
static StaticTask_t myTimerData;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize ) {
    (*ppxTimerTaskTCBBuffer) = &myTimerData;
    (*ppxTimerTaskStackBuffer) = (StackType_t*)&myTimerStack[0];
    (*pulTimerTaskStackSize) = NB_TIMER_WORD;
}

#define NB_IDLE_WORD   (32)
static int myIdleStack[NB_TIMER_WORD];
static StaticTask_t myIdleData;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize ){
    (*ppxIdleTaskTCBBuffer) = &myIdleData;
    (*ppxIdleTaskStackBuffer) = (StackType_t*)&myIdleStack[0];
    (*pulIdleTaskStackSize) = NB_IDLE_WORD;
}