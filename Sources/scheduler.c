/*
 * scheduler.c
 *
 *  Created on: Mar 13, 2016
 *      Author: uidj2420
 */
#include "common.h"
#include "scheduler.h"

/* Check priority */
static int checkPriority();

/* Schedule policy function */
static void scheduler(void);

sTaskInfo* schedulerTaskInfo[3] = {NULL};
sTaskInfo* currTaskInfo = NULL;

register int r14 asm ("r14");

/***********************************************************************  
 If there is a task in RUNNING state, save the return address in its 
 respective TCB structure and then set as READY the corresponding
 task
 **********************************************************************/

eErrorID OS_activateTask(taskId taskId)
{
	/* Ask if the scheduler is NON OR FULL PREEMPTIVE */
	uint8_t i;
	eErrorID status = ERROR;
	//@TODO: What if the user activates the same task???
	/* Check if the id is valid */
	if(taskId >= 0 && taskId < NUMBER_OF_TASKS)
	{
		for(i = 0; i < NUMBER_OF_TASKS; i++)
		{
			/* Check if there is a task running */
			if(schedulerTaskInfo[i]->state == RUNNING)
			{
				schedulerTaskInfo[i]->returnAddress = (uint32_t*)r14;
				break;
			}
		}

		schedulerTaskInfo[taskId]->state = READY;
		status = SUCCESSFUL;
	}
	scheduler();
	return status;
}

eErrorID OS_terminateTask()
{
	int i;
	eErrorID status = ERROR;
	//@TODO: Clean up stacks
	for(i = 0; i < NUMBER_OF_TASKS; i++)
	{
		if(schedulerTaskInfo[i]->state == RUNNING)
		{
			schedulerTaskInfo[i]->state = SUSPENDED;
			status = SUCCESSFUL;
			break;
		}
	}
	scheduler();
	return status;
}

eErrorID OS_chainTask(taskId taskId)
{
	int i;
	eErrorID status = ERROR;
	for(i = 0; i < NUMBER_OF_TASKS; i++)
	{
		if(schedulerTaskInfo[i]->id == taskId)
		{
			schedulerTaskInfo[i]->state = READY;
			status = SUCCESSFUL;
			break;
		}
	}
	return status;
}

eErrorID OS_createTask(sTaskInfo* taskInfo)
{
	switch(taskInfo->id)
	{
	case 0: schedulerTaskInfo[0] = taskInfo; break;
	case 1: schedulerTaskInfo[1] = taskInfo; break;
	case 2: schedulerTaskInfo[2] = taskInfo; break;
	default: printf("Task not defined");
	}
	return ERROR;
}

eErrorID OS_startOS()
{
	uint8_t id = 0xEE;
	uint8_t i = NUMBER_OF_TASKS;

	/* Auto start initialization */
	do
	{
		/* We have a autostart task */
		if(schedulerTaskInfo[i]->autoStart == 1)
		{
			id = schedulerTaskInfo[i]->id;
			OS_activateTask(id);
			break;
		}
	}while(--i);
	OS_activateTask(TASK_A_ID);
	scheduler();
	return ERROR;
}

static void scheduler(void)
{
	taskId id;

	id = checkPriority();
	if(schedulerTaskInfo[id]->state == READY)
	{
		schedulerTaskInfo[id]->task();
	}
}

static int checkPriority()
{
	int i = 0;

	if((schedulerTaskInfo[0]->priority > schedulerTaskInfo[1]->priority) && (schedulerTaskInfo[0]->state == READY))
	{
		i =  schedulerTaskInfo[0]->id;
	}
	else if((schedulerTaskInfo[0]->priority < schedulerTaskInfo[1]->priority) && (schedulerTaskInfo[1]->state == READY))
	{
		i =  schedulerTaskInfo[1]->id;
	}
	if((schedulerTaskInfo[i]->priority > schedulerTaskInfo[2]->priority) && (schedulerTaskInfo[i]->state == READY))
	{
		i =  schedulerTaskInfo[0]->id;
	}
	else if((schedulerTaskInfo[i]->priority < schedulerTaskInfo[2]->priority) && (schedulerTaskInfo[2]->state == READY))
	{
		i =  schedulerTaskInfo[2]->id;
	}

	return i;
}


