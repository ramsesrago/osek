/*
 * osek_config.h
 *
 *  Created on: Mar 24, 2016
 *      Author: uidj2420
 */

#ifndef OSEK_CONFIG_H_
#define OSEK_CONFIG_H_

#define NUMBER_OF_TASKS		(3)

#if (NUMBER_OF_TASKS == 1)
	#define TASK_A_ID			(0)
#elif (NUMBER_OF_TASKS == 2)
	#define TASK_A_ID			(0)
	#define TASK_B_ID			(1)
#elif (NUMBER_OF_TASKS == 3)
	#define TASK_A_ID			(0)
	#define TASK_B_ID			(1)
	#define TASK_C_ID			(2)
#endif

#define TASK_STACK_SIZE	(30)

#endif /* OSEK_CONFIG_H_ */
