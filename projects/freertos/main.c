
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

extern void myTask_Rx_init(void);
extern void myTask_Tx_init(void);
extern void myTimer_init(void);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main( void ) {
    printf("%s: start\n", __PRETTY_FUNCTION__);
    
    signal(SIGINT, sig_handler);
    
    myTask_Rx_init();
    myTask_Tx_init();
    myTimer_init();
	
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