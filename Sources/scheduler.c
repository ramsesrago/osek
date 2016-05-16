/*
 * scheduler.c
 *
 *  Created on: Mar 13, 2016
 *      Author: uidj2420
 */
#include "common.h"
#include "scheduler.h"
#include "service/queue.h"

/* Get the next task ID */
static uint32_t getNextTaskId();

/* Schedule policy function */
static void scheduler(void);

/* Init task task function */
static void initTaskStack(uint32_t);

static void linkRegister(void);

sTaskInfo_t* schedulerTaskInfo[4] = { NULL };

uint32_t runningTask;
uint32_t nextRunningTask;

void PendSV_Handler();

void SVC_Handler();

static uint32_t get_IPSR(void);

/* Function to switch context */
static void switchContext(void);

static inline void * rd_stack_ptr(void);
static inline void save_context(void);
static inline void load_context(void);
static inline void * rd_thread_stack_ptr(void);
static inline void wr_thread_stack_ptr(void * ptr);

//register int r7 asm ("r7");

uint32_t* mainStack = NULL;

/***********************************************************************  
 If there is a task in RUNNING state, save the return address in its 
 respective TCB structure and then set as READY the corresponding
 task
 **********************************************************************/

eErrorID OS_activateTask(uint32_t taskId)
{
	eErrorID status = ERROR;
	//@TODO: What if the user activates the same task???
	/* Check if the id is valid */
	if (taskId >= 0 && taskId < NUMBER_OF_TASKS)
	{
		schedulerTaskInfo[taskId]->state = READY;
		status = SUCCESSFUL;
	}
	Schedule();
	return status;
}

eErrorID OS_terminateTask()
{
	eErrorID status = ERROR;
	//@TODO: Clean up stacks
	schedulerTaskInfo[runningTask]->state = SUSPENDED;
	Schedule();
	return status;
}

eErrorID OS_chainTask(uint32_t taskId) 
{
	eErrorID status = ERROR;
	schedulerTaskInfo[runningTask]->state = SUSPENDED;
	/* Verify if the taskId is valid */
	if (taskId >= 0 && taskId < NUMBER_OF_TASKS)
	{
		schedulerTaskInfo[taskId]->state = READY;
		status = SUCCESSFUL;
	}
	Schedule();
	return status;
}

eErrorID OS_createTask(sTaskInfo_t* taskInfo) 
{
	switch (taskInfo->id) {
	case 0:
		schedulerTaskInfo[0] = taskInfo;
		initTaskStack(schedulerTaskInfo[0]->id);
		break;
	case 1:
		schedulerTaskInfo[1] = taskInfo;
		initTaskStack(schedulerTaskInfo[1]->id);
		break;
	case 2:
		schedulerTaskInfo[2] = taskInfo;
		initTaskStack(schedulerTaskInfo[2]->id);
		break;
	case 3:
		schedulerTaskInfo[3] = taskInfo;
		initTaskStack(schedulerTaskInfo[3]->id);
		break;
	default:
		printf("Task not defined");
	}
	return ERROR;
}

eErrorID OS_startOS()
{
	uint32_t i = NUMBER_OF_TASKS - 1;
	/* Auto start initialization */
	do
	{
		if(schedulerTaskInfo[i]->autoStart == 1)
		{
			schedulerTaskInfo[i]->state = READY;
		}
	}while(i--);
	/* Init in IDLE task */
	runningTask = TASK_IDLE_ID;
	Schedule();
	return ERROR;
}

static void scheduler(void)
{
	nextRunningTask = getNextTaskId();
	/* The set running will be set in when switching the context */
	if(nextRunningTask != runningTask)
	{
		SCB_ICSR |= (1 << 28);
	}
	//asm("mov sp, %0" : : "r" (schedulerTaskInfo[runningTask]->sp));
}

static uint32_t getNextTaskId() 
{
	uint32_t index = TASK_IDLE_ID;
	uint32_t topPriority = 0;
	uint8_t i = 0;

	for (; i < NUMBER_OF_TASKS; i++) 
	{
		if (schedulerTaskInfo[i]->state == READY) 
		{
			if (schedulerTaskInfo[i]->priority >= topPriority) 
			{
				topPriority = schedulerTaskInfo[i]->priority;
				index = (uint32_t)i;
			}
		}
	}
	return index;
}

static void initTaskStack(uint32_t taskId) 
{
	uint32_t* stackBaseAddr;
	sStackFrame_t* stackFrameTask = NULL;

	/* Calculate the last address to write (base addrees) for the stack */
	stackBaseAddr =	(uint32_t*) ((uint32_t) (&schedulerTaskInfo[taskId]->stack[0]) + sizeof(uint32_t)*(TASK_STACK_SIZE));

	/* Calculate the address where the stack frame begins */
	stackFrameTask = (sStackFrame_t*) (stackBaseAddr - sizeof(sStackFrame_t)/sizeof(uint32_t));

	schedulerTaskInfo[taskId]->sp = (uint32_t*) stackFrameTask;
	schedulerTaskInfo[taskId]->r7 = (uint32_t) stackBaseAddr;

	/* Init stack frame with zeros */
	memset(stackFrameTask, 0, sizeof(sStackFrame_t));

	stackFrameTask->lr = linkRegister;
	stackFrameTask->r0 = taskId;
	stackFrameTask->pc = (uint32_t) schedulerTaskInfo[taskId]->task;
	stackFrameTask->psr = 0x01000000;
}

static void linkRegister(void) 
{
	while (1);
}

void PendSV_Handler()
{
	asm volatile ("MRS %0, msp\n\t"
				//"MOV r0, %0 \n\t"
				: "=r" (mainStack) );
	//mainStack = (uint32_t*)rd_stack_ptr();
	switchContext();
}

static void switchContext(void)
{
	uint32_t* r7backup = mainStack - 1;

	/* Check if there was a running task */
	if(schedulerTaskInfo[runningTask]->state == RUNNING)
	{
		schedulerTaskInfo[runningTask]->state = READY;
	}
	if(*mainStack != MAIN_RETURN)
	{
		schedulerTaskInfo[runningTask]->r7 = *r7backup;
		schedulerTaskInfo[runningTask]->sp = (uint32_t*)rd_thread_stack_ptr();
	}
	*mainStack = THREAD_RETURN;
	runningTask = nextRunningTask;
	//asm volatile ("MSR sp, %0\n\t" : : "r" (schedulerTaskInfo[nextRunningTask]->sp) );
	*r7backup = schedulerTaskInfo[nextRunningTask]->r7;
	//asm("mov pc, %0" : : "r" (schedulerTaskInfo[runningTask]->sp));
	/* Set the new task in running */
	schedulerTaskInfo[runningTask]->state = RUNNING;
}

static inline void* rd_stack_ptr(void)
{
	void * result=NULL;
	asm volatile ("MRS %0, msp\n\t"
			//"MOV r0, %0 \n\t"
			: "=r" (result) );
	return result;
}

//This saves the context on the PSP, the Cortex-M3 pushes the other registers using hardware
static inline void save_context(void)
{
	uint32_t scratch;
	asm volatile ("MRS %0, psp\n\t"
			"STMDB %0!, {r4, r5, r6, r8, r9, r10, r11}\n\t"
			"MSR psp, %0\n\t"  : "=r" (scratch) );
}

//This loads the context from the PSP, the Cortex-M3 loads the other registers using hardware
static inline void load_context(void)
{
	uint32_t scratch;
	asm volatile ("MRS %0, psp\n\t"
			"LDMFD %0!, {r4, r5, r6, r8, r9, r10, r11}\n\t"
			"MSR psp, %0\n\t"  : "=r" (scratch) );
}

//This reads the PSP so that it can be stored in the task table
static inline void * rd_thread_stack_ptr(void)
{
	void* result = NULL;
	asm volatile ("MRS %0, psp\n\t" : "=r" (result) );
	return(result);
}

//This writes the PSP so that the task table stack pointer can be used again
static inline void wr_thread_stack_ptr(void * ptr)
{
	asm volatile ("MSR msp, %0\n\t" : : "r" (ptr) );
}

static uint32_t get_IPSR(void)
{
	uint32_t result;
	asm volatile ("MRS %0, ipsr" : "=r" (result) );
	return(result);
}

void SVC_Handler()
{
	scheduler();
}

