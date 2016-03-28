/*
 * scheduler.h
 *
 *  Created on: Mar 13, 2016
 *      Author: uidj2420
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "osek_config.h"
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

typedef uint32_t taskId;

typedef enum
{
	SUSPENDED = 0,
	RUNNING,
	READY,
	WAIT
}eTaskState;

typedef struct
{
	taskId id;
	eSchedule schedule;
	uint32_t priority;
	uint32_t autoStart;	
	eTaskState state;
	void (*task)(void);
	uint32_t* returnAddress;
}sTaskInfo;


/* The specified task is transferred from the suspended state into the ready state */
eErrorID OS_activateTask(taskId);

/* The calling task is transferred from the running state into the suspended state */
eErrorID OS_terminateTask();

/* After termination of the calling task an other task is activated sequentially */
eErrorID OS_chainTask(taskId);

/* Function to create tasks in the scheduler */
eErrorID OS_createTask(sTaskInfo*);

/* Function to start scheduling */
eErrorID OS_startOS();

#endif /* SCHEDULER_H_ */
