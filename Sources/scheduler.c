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
//Queue* queue = NULL;

register int r14 asm ("r14");

/***********************************************************************  
 If there is a task in RUNNING state, save the return address in its 
 respective TCB structure and then set as READY the corresponding
 task
 **********************************************************************/

eErrorID OS_activateTask(taskId taskId)
{
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
			schedulerTaskInfo[i]->returnAddress = NULL;
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
	case 0: schedulerTaskInfo[0] = taskInfo; 
	schedulerTaskInfo[0]->sp = &schedulerTaskInfo[0]->stack[TASK_STACK_SIZE-2];
	schedulerTaskInfo[0]->stack[TASK_STACK_SIZE-1] = schedulerTaskInfo[0]->returnAddress;
	break;
	case 1: schedulerTaskInfo[1] = taskInfo; 
	schedulerTaskInfo[1]->sp = &schedulerTaskInfo[1]->stack[TASK_STACK_SIZE-2];
	schedulerTaskInfo[1]->stack[TASK_STACK_SIZE-1] = schedulerTaskInfo[1]->returnAddress;
	break;
	case 2: schedulerTaskInfo[2] = taskInfo; 
	schedulerTaskInfo[2]->sp = &schedulerTaskInfo[2]->stack[TASK_STACK_SIZE-2];
	schedulerTaskInfo[2]->stack[TASK_STACK_SIZE-1] = schedulerTaskInfo[2]->returnAddress;
	break;
	default: printf("Task not defined");
	}
	return ERROR;
}

eErrorID OS_startOS()
{
#if 0
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
	queue = createQueue(NUMBER_OF_TASKS);
#endif
	OS_activateTask(TASK_A_ID);
	return ERROR;
}

static void scheduler(void)
{
	globalId = 0xEE;

	while(globalId == INVALID_TASK_ID)
	{
		globalId = getNextTaskId();
	}
	//@TODO: Remove unnecessary ready verification
	if(schedulerTaskInfo[globalId]->state == READY)
	{
		schedulerTaskInfo[globalId]->state = RUNNING;
		asm("mov sp, %0" : : "r" (schedulerTaskInfo[globalId]->sp));
		//schedulerTaskInfo[globalId]->sp = schedulerTaskInfo[globalId]->sp - 2;
	}
}

static taskId getNextTaskId()
{
	taskId index = (taskId)INVALID_TASK_ID;
	uint32_t topPriority = 0;
	uint8_t i = 0;

#if 0
	/* If size is bigger than zero, means that we have at least one ready task */
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

