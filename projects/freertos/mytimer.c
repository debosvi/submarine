
/* Standard includes. */
#include <stdio.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"

#include "timers.h"

static const char * const myTimer_Name  = "myTimer_Name";
#define NB_STACK_WORD   (32)
static const unsigned myTimer_Param = 0x100;
static StaticTimer_t myTimer_Data;
static TimerHandle_t myTimer_Handle;

#define myTimer_TICK_PERIOD		(100)
#define myTimer_AUTORELOAD		(1)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static void myTimer_Fct(TimerHandle_t tmr) {
    printf("%s: timer (%p)\n", __PRETTY_FUNCTION__, tmr);
}

int myTimer_init(void) {
	myTimer_Handle = xTimerCreateStatic(
		&myTimer_Name[0],
		myTimer_TICK_PERIOD,
		myTimer_AUTORELOAD,
		(void*)&myTimer_Param,
		myTimer_Fct,
		&myTimer_Data);
 
    if(myTimer_Handle) {
		if(xTimerStart(myTimer_Handle, 0)==pdPASS) {
			printf("%s: timer started\n", __PRETTY_FUNCTION__);
			return 1;
		}
		printf("%s: timer not started\n", __PRETTY_FUNCTION__);
		return 0;
	}
	printf("%s: timer creation failure\n", __PRETTY_FUNCTION__);
	return 0;
}