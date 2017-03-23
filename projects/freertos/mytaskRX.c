
/* Standard includes. */
#include <stdio.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"

#include "task.h"

static const char * const myTask_Rx_Name  = "myTask_Rx_Name";
#define NB_STACK_WORD   (256)
static int myTask_Rx_Stack[NB_STACK_WORD];
static const unsigned myTask_Rx_Param = 0x1234;
static StaticTask_t myTask_Rx_Data;
static TaskHandle_t myTask_Rx_Handle;

#define myTask_Rx__FREQUENCY_MS			( 1000 / portTICK_PERIOD_MS )

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void myTask_Rx_Fct(void *parg) {
    TickType_t xNextWakeTime;
    unsigned arg = *(unsigned*)parg;
    const TickType_t xBlockTime = pdMS_TO_TICKS( myTask_Rx__FREQUENCY_MS );
    
    printf("%s: arg(%u)\n", __PRETTY_FUNCTION__, arg);
    
    xNextWakeTime = xTaskGetTickCount();

    for( ;; ) {
        printf("%s: loop\n", __PRETTY_FUNCTION__);
        vTaskDelayUntil( &xNextWakeTime, xBlockTime );
    }
}

int myTask_Rx_init(void) {
	myTask_Rx_Handle = xTaskCreateStatic(
        myTask_Rx_Fct, 
        myTask_Rx_Name,
        NB_STACK_WORD,
        (void*)&myTask_Rx_Param,
        1,
        (void*)&myTask_Rx_Stack[0],
        &myTask_Rx_Data);
    if(myTask_Rx_Handle) {
		printf("%s: task created\n", __PRETTY_FUNCTION__);
		return 1;
	}
	printf("%s: task creation failure\n", __PRETTY_FUNCTION__);
	return 0;
}