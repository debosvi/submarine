
/* Standard includes. */
#include <stdio.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"

#include "task.h"

static const char * const myTask_Tx_Name  = "myTask_Tx_Name";
#define NB_STACK_WORD   (256)
static int myTask_Tx_Stack[NB_STACK_WORD];
static const unsigned myTask_Tx_Param = 0x1234;
static StaticTask_t myTask_Tx_Data;
static TaskHandle_t myTask_Tx_Handle;

#define myTask_Tx__FREQUENCY_MS			( 300 / portTICK_PERIOD_MS )

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void myTask_Tx_Fct(void *parg) {
    TickType_t xNextWakeTime;
    unsigned arg = *(unsigned*)parg;
    const TickType_t xBlockTime = pdMS_TO_TICKS( myTask_Tx__FREQUENCY_MS );
    
    printf("%s: arg(%u)\n", __PRETTY_FUNCTION__, arg);
    
    xNextWakeTime = xTaskGetTickCount();

    for( ;; ) {
        printf("%s: loop\n", __PRETTY_FUNCTION__);
        vTaskDelayUntil( &xNextWakeTime, xBlockTime );
    }
}

int myTask_Tx_init(void) {
	myTask_Tx_Handle = xTaskCreateStatic(
        myTask_Tx_Fct, 
        myTask_Tx_Name,
        NB_STACK_WORD,
        (void*)&myTask_Tx_Param,
        1,
        (void*)&myTask_Tx_Stack[0],
        &myTask_Tx_Data);
    if(myTask_Tx_Handle) {
		printf("%s: task created\n", __PRETTY_FUNCTION__);
		return 1;
	}
	printf("%s: task creation failure\n", __PRETTY_FUNCTION__);
	return 0;
}