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

sTaskInfo* schedulerTaskInfo[3] = {NULL};

register int r14 asm ("r14");

eErrorID OS_activateTask(taskId taskId)
{
	/* Ask if the scheduler is NON OR FULL PREEMPTIVE */
	int i;
	eErrorID status = ERROR;
	for(i = 0; i < 3; i++)
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

eErrorID OS_terminateTask()
{
	int i;
	eErrorID status = ERROR;
	for(i = 0; i < 3; i++)
	{
		if(schedulerTaskInfo[i]->state == RUNNING)
		{
			schedulerTaskInfo[i]->state = SUSPENDED;
			status = SUCCESSFUL;
			break;
		}
	}
	return status;
}

eErrorID OS_chainTask(taskId taskId)
{
	int i;
	eErrorID status = ERROR;
	for(i = 0; i < 3; i++)
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
}

eErrorID OS_startScheduler()
{
	int id = 0xEE;
	int i;

	/* Auto start initialization */
	for(i = 0; i < 3; i++)
	{
		if(schedulerTaskInfo[i]->autoStart == 1)
		{
			id = schedulerTaskInfo[i]->id;
			break;
		}
	}
	/* We have a autostart task */
	if(id != 0xEE)
	{
		OS_activateTask(id);
		schedulerTaskInfo[id]->task();
	}
	while(1)
	{
		delay();
		id = checkPriority();
		if(schedulerTaskInfo[id]->state == READY)
		{
			schedulerTaskInfo[id]->task();
		}
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

/*
 * Function to provide a short delay
 */
void delay()
{
	unsigned int i, n;
	for(i=0; i < 30000; i++)
	{
		for(n=0; n < 200; n++)
		{
			asm("nop");
		}
	}
}

