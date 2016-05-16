/*
 * scheduler.h
 *
 *  Created on: Mar 13, 2016
 *      Author: uidj2420
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "osek_config.h"

#define Schedule() if(!get_IPSR()) {asm("svc 0");}
#define DisableInterrupts() set_FAULTMASK(1)
#define EnableInterrupts() set_FAULTMASK(0)

#define MAIN_RETURN   (0xFFFFFFF9)  //Tells the handler to return using the MSP
#define THREAD_RETURN (0xFFFFFFFD)  //Tells the handler to return using the PSP

#define TASK(taskname) 				void task_##taskname(void)
#define getTaskAddress(taskName) 	task_##taskname

/* Enums declarations */
typedef enum
{
	SUCCESSFUL = 0,
	ERROR
}eErrorID;

typedef enum
{
	NON = 0,
	FULL
}eSchedule;

typedef enum
{
	SUSPENDED = 0,
	RUNNING,
	READY,
	WAIT
}eTaskState;

typedef struct
{
	uint32_t 	id;
	eSchedule 	schedule;
	uint32_t 	priority;
	uint32_t	autoStart;	
	eTaskState 	state;
	void 		(*task)(void);
	uint32_t 	stack[TASK_STACK_SIZE];
	uint32_t* 	sp;
	uint32_t    r7;
}sTaskInfo_t;

typedef struct
{
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;
	uint32_t pc;
	uint32_t psr;
} sStackFrame_t;

/* The specified task is transferred from the suspended state into the ready state */
eErrorID OS_activateTask(uint32_t);

/* The calling task is transferred from the running state into the suspended state */
eErrorID OS_terminateTask();

/* After termination of the calling task an other task is activated sequentially */
eErrorID OS_chainTask(uint32_t);

/* Function to create tasks in the scheduler */
eErrorID OS_createTask(sTaskInfo_t*);

/* Function to start scheduling */
eErrorID OS_startOS();

#endif /* SCHEDULER_H_ */
