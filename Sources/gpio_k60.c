/*
 * File:		gpio_k60.c
 * Purpose:		LED and Switch Example
 *
 *                      Configures GPIO for the LED and push buttons on the TWR-K60N512
 *                      Blue LED - On
 *                      Green LED - Toggles on/off
 *                      Orange LED - On if SW2 pressed
 *                      Yellow LED - On if SW1 pressed
 *
 *                      Also configures push buttons for falling IRQ's. ISR
 *                        configured in vector table in isr.h
 *
 */

/*
 * Authors:
 * - Ramsés Ramírez, Oswaldo González
 *   Tecnológico de Monterrey
 */

#include "common.h"
#include "scheduler.h"

#define GPIO_PIN_MASK       0x1Fu
#define GPIO_PIN(x)         (((1) << (x & GPIO_PIN_MASK)))

#define CORE_CLOCK			(96000000)
#define SYSTICK_FREQUENCY	(1000)

/* Interrupt declarations */
void porta_isr(void);
void porte_isr(void);
void lptmr_isr(void);
void SysTick_Handler();

/* Function declarations */
void init_gpio(void);
void init_systick(void);

/* Task declarations */
TASK(taskA);
TASK(taskB);
TASK(taskC);

sTaskInfo taskInfo[NUMBER_OF_TASKS] = {
		[0] = {
				.id = TASK_A_ID,
				.schedule = FULL,
				.priority = 0,
				.autoStart = 0,
				.returnAddress = &task_taskA,
				.task = task_taskA
		},
		[1] = {
				.id = TASK_B_ID,
				.schedule = FULL,
				.priority = 1,
				.autoStart = 0,
				.returnAddress = &task_taskB,
				.task = task_taskB
		},
		[2] = {
				.id = TASK_C_ID,
				.schedule = FULL,
				.priority = 2,
				.autoStart = 0,
				.returnAddress = &task_taskC,
				.task = task_taskC
		}
};

//void (* const tasks[])(void) =
//{
//		taskA,
//		taskB,
//		taskC
//};

uint32_t var = 0;

/********************************************************************/

int main (void)
{
	printf("TWR-K60N512 Scheduler!\n");

	/* Turn on all port clocks */
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

	/* Enable LPT Module */
	SIM_SCGC5 |= SIM_SCGC5_LPTIMER_MASK;

	/* Enable GPIOA and GPIOE interrupts in NVIC */
	enable_irq(87); //GPIOA Vector is 103. IRQ# is 103-16 = 87
	enable_irq(91); //GPIOE Vector is 107. IRQ# is 107-16 = 91
	enable_irq(85); //GPIOE Vector is 107. IRQ# is 101-16 = 85

	/* Initialize GPIO on TWR-K60N512 */
	init_gpio();
	/* Initialize systick */
	//init_systick();

	/* Create tasks in the scheduler */
	OS_createTask(&taskInfo[TASK_A_ID]);
	OS_createTask(&taskInfo[TASK_B_ID]);
	OS_createTask(&taskInfo[TASK_C_ID]);

	/* Start OS */
	OS_startOS();

	for(;;)
	{

	}

	return 0;
}

TASK(taskA)
{
	for(;;)
	{
		//printf("Hello I am task 1\n");
		//Toggle the green LED on PTA10
		var = 5;
		GPIOA_PTOR |= GPIO_PDOR_PDO(GPIO_PIN(10));
		var = 10;
	}
}

TASK(taskB)
{
	for(;;)
	{
		//printf("Hello I am task 2\n");
		//Toggle the green LED on PTA29
		var = 15;
		GPIOA_PTOR |= GPIO_PDOR_PDO(GPIO_PIN(29));
		var = 20;
	}
}

TASK(taskC)
{
	for(;;)
	{
		//printf("Hello I am task 3\n");
		//Toggle the green LED on PTA28
		var = 25;
		GPIOA_PTOR |= GPIO_PDOR_PDO(GPIO_PIN(28));
		var = 30;
	}
}

/*
 * Initialize GPIO for Tower switches and LED's
 *
 *   PTA19 - SW1
 *   PTE26 - SW2
 *
 *   PTA10 - Blue (E4)
 *   PTA29 - Green (E3)
 *   PTA28 - Yellow (E2)
 *   PTA11 - Orange (E1)
 *
 */
void init_gpio()
{
	//Set PTA19 and PTE26 (connected to SW1 and SW2) for GPIO functionality, falling IRQ,
	//   and to use internal pull-ups. (pin defaults to input state)
	PORTA_PCR19 = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0xA) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR26 = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0xA) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

	//Set PTA10, PTA11, PTA28, and PTA29 (connected to LED's) for GPIO functionality
	PORTA_PCR10 = (0 | PORT_PCR_MUX(1));
	PORTA_PCR11 = (0 | PORT_PCR_MUX(1));
	PORTA_PCR28 = (0 | PORT_PCR_MUX(1));
	PORTA_PCR29 = (0 | PORT_PCR_MUX(1));

	//Change PTA10, PTA11, PTA28, PTA29 to outputs
	GPIOA_PDDR = GPIO_PDDR_PDD(GPIO_PIN(10) | GPIO_PIN(11) | GPIO_PIN(28) | GPIO_PIN(29) );	
}

void init_systick(void)
{
#if 0
	SYST_CSR = 0x00U;
	SYST_RVR = SysTick_RVR_RELOAD(0x00632EA0);
	SYST_CVR = SysTick_CVR_CURRENT(0x00);
	SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK); 
#endif
	SYST_RVR = CORE_CLOCK/SYSTICK_FREQUENCY;
	SYST_CSR = SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK | SysTick_CSR_CLKSOURCE_MASK;
}

/********************************************************************/

/*
 * ISR for PORTA interrupts
 */
void porta_isr(void)
{
	static int i = -1;
	PORTA_ISFR = 0xFFFFFFFF;  //Clear Port A ISR flags
	if(i < 3) i++;
	else i = -1;
	switch(i)
	{
		case 0: OS_activateTask(TASK_B_ID); break;
		case 1: OS_activateTask(TASK_C_ID); break;
		case 2: OS_activateTask(TASK_A_ID); break;
		default: break;
	}
}

/*
 * ISR for PORTE interrupts
 */
void porte_isr(void)
{
	PORTE_ISFR = 0xFFFFFFFF;  //Clear Port E ISR flags
	printf("SW2 Pressed\n");
}

/*
 * ISR for PORTC interrupts
 */
void portc_isr(void)
{
	PORTC_ISFR = 0xFFFFFFFF;  //Clear Port C ISR flags
}
void SysTick_Handler()
{
	printf("systick\n");
}
