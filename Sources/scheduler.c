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
static taskId getNextTaskId();

/* Schedule policy function */
static void scheduler(void);

sTaskInfo* schedulerTaskInfo[3] = {NULL};
sTaskInfo* currTaskInfo = NULL;
taskId globalId = INVALID_TASK_ID;
Queue* queue = NULL;

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
				schedulerTaskInfo[i]->returnAddress = r14;
				schedulerTaskInfo[i]->state = READY;
				enqueue(queue, i);
				break;
			}
		}

		schedulerTaskInfo[taskId]->state = READY;
		/* Enque to the ready tasks */
		enqueue(queue, taskId);
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
	//	do
	//	{
	//		/* We have a autostart task */
	//		if(schedulerTaskInfo[i]->autoStart == 1)
	//		{
	//			id = schedulerTaskInfo[i]->id;
	//			OS_activateTask(id);
	//			break;
	//		}
	//	}while(--i);
	queue = createQueue(NUMBER_OF_TASKS);
	OS_activateTask(TASK_A_ID);
	scheduler();
	return ERROR;
}

static void scheduler(void)
{
	taskId id;
	globalId = 0xEE;

	while(globalId == INVALID_TASK_ID)
	{
		globalId = getNextTaskId();
	}
	if(schedulerTaskInfo[globalId]->state == READY)
	{
		schedulerTaskInfo[globalId]->state = RUNNING;
		/* If the return address is null, means the task has not been preempted */
		if(schedulerTaskInfo[globalId]->returnAddress == NULL)
		{
			schedulerTaskInfo[globalId]->task();
		}
		else
		{
			asm("mov pc, %0" : : "r" (schedulerTaskInfo[globalId]->returnAddress));
		}
	}
}

static taskId getNextTaskId()
{
	taskId index = (taskId)INVALID_TASK_ID;
	uint32_t topPriority = 0;
	uint8_t i = 0;
	
	/* If size is bigger than zero, means that we have at least one ready task */
#if 0
	if(queue->size >  0)
	{
		/* Get the index of the ready task with the greatest priority */
		// @TODO: Implement logic for more than one ready task
		i = (taskId)front(queue);
		dequeue(queue);
	}
#endif
	for(; i < NUMBER_OF_TASKS; i++)
	{
		if(schedulerTaskInfo[i]->state == READY)
		{
			if(schedulerTaskInfo[i]->priority >= topPriority)
			{
				topPriority = schedulerTaskInfo[i]->priority;
				index = (taskId)i;
			}
		}
	}
	return index;
}

