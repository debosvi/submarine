SHELL=/bin/bash 

CC ?= gcc

RTOS_DIR_GEN = $(PWD)/../../../FreeRTOS
RTOS_DIR_PLUS = $(PWD)/../../../FreeRTOS-Plus

HEADER_RTOS_GEN = -Irtos/include
HEADER_RTOS_GEN += -Irtos/portable/MSVC-MingW
HEADER_RTOS_GEN += -I$(RTOS_DIR_GEN)/Demo/Common/include/

HEADER_RTOS_PLUS= -I$(RTOS_DIR_PLUS)/Source/FreeRTOS-Plus-Trace/Include

TARGET = rtos_demo_pc

OBJS=main.o myTaskRX.o myTaskTX.o mytimer.o

OBJS_GEN=

OBJS_GEN+=rtos/tasks.o
OBJS_GEN+=rtos/list.o
OBJS_GEN+=rtos/queue.o
OBJS_GEN+=rtos/timers.o

# OBJS_GEN+=rtos/portable/MSVC-MingW/port.o rtos/event_groups.o
OBJS_GEN+=rtos/portable/MSVC-MingW/port.o rtos/croutine.o
# OBJS_GEN+=plus/trcBase.o plus/trcKernelPort.o plus/trcKernel.o plus/trcUser.o plus/trcHardwarePort.o
# OBJS_GEN+=minimal/TimerDemo.o minimal/QueueSet.o minimal/death.o minimal/TaskNotify.o minimal/AbortDelay.o
# OBJS_GEN+=minimal/QueueOverwrite.o minimal/IntSemTest.o minimal/EventGroupsDemo.o minimal/GenQTest.o
# OBJS_GEN+=minimal/BlockQ.o minimal/PollQ.o minimal/QPeek.o minimal/semtest.o minimal/integer.o minimal/flop.o
# OBJS_GEN+=minimal/recmutex.o minimal/countsem.o minimal/dynamic.o minimal/QueueSetPolling.o minimal/blocktim.o
# OBJS_GEN+=$(patsubst %.c,%.o,$(wildcard minimal/*.c))
OBJS_GEN+=MemMang/heap_1.o

CFLAGS = -ggdb -O0
CFLAGS = -O2

CFLAGS += -Wall $(HEADER_RTOS_GEN) $(HEADER_RTOS_PLUS) -I. 
LDFLAGS = -Wl,-Bdynamic

ALL_SRCS=$(patsubst %.o,%.c,$(OBJS) $(OBJS_GEN))
     
all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(ALL_SRCS): FreeRTOSConfig.h

list:
	echo -e $(OBJS_GEN)
	
rtos_demo_pc: $(OBJS) $(OBJS_GEN)
	$(CC) $(LDFLAGS) -o $@ $^ -lWINMM
	
clean:
	rm -f $(OBJS) $(OBJS_GEN) $(TARGET)