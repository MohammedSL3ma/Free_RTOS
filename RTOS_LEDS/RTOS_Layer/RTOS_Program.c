/*
 * RTOS_Program.c
 *
 *  Created on: 10 Dec 2023
 *      Author: Selim
 */
#include "../LIB/stdtypes.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/Timer_V2/Timer_int.h"
#include "../MCAL/EXTINT_V1/EXTINT_int.h"
#include "RTOS_Config.h"
#include "RTOS_Interface.h"
#include "RTOS_Private.h"

#define   NULL    (void*) 0
#define   TIMER0_u8_COMP_MATCH_VAL  125
/*
 * The index of task in array will be also the number of priority of the same task
 */
static CreateTask_FuncArgus System_Tasks[TASK_NUM]={{NULL}};



void RTOS_voidStart(void)
{
	timer_config_type RTOS_TimerConfig;
	RTOS_TimerConfig.timer = TIMER_0;
	RTOS_TimerConfig.operated_mode = CTC_MODE;
	RTOS_TimerConfig.compared_value = TIMER0_u8_COMP_MATCH_VAL;
	RTOS_TimerConfig.T0_T1_used_freq = TIMER_0_1_PRE_SCALER_e_64;

	Set_CallBack_TIMER_0_OC_INT(&RTOS_voidScheduler);
	Global_VidINTEnable();
	Timer_init(&RTOS_TimerConfig);

}

u8 RTOS_u8CreateTask(CreateTask_FuncArgus * FuncArgus)
{
	u8 Local_u8ErrorState = OK;
	/*Check if the required priority is empty or used before for another task*/
	if(System_Tasks[FuncArgus->Copy_u8Priority].Copy_pvTaskFunc == NULL)
	{
		System_Tasks[FuncArgus->Copy_u8Priority].Copy_u16Periodicity = FuncArgus->Copy_u16Periodicity;
		System_Tasks[FuncArgus->Copy_u8Priority].Copy_pvTaskFunc = FuncArgus->Copy_pvTaskFunc;
		System_Tasks[FuncArgus->Copy_u8Priority].Copy_u8State = TASK_RESUMED;      //Initialize the task state
		System_Tasks[FuncArgus->Copy_u8Priority].Copy_u16FirstDelay = FuncArgus->Copy_u16FirstDelay;
	}
	else
	{
		/*Priority is reserved before, don't create the task*/
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
	System_Tasks[Copy_u8Priority].Copy_u8State = TASK_SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
	System_Tasks[Copy_u8Priority].Copy_u8State = TASK_RESUMED;
}

void RTOS_voidDeleteTask(u8 Copy_u8Priority)
{
	System_Tasks[Copy_u8Priority].Copy_pvTaskFunc = NULL;
}

static void RTOS_voidScheduler(void)
{

	u8 Local_u8TaskCounter;

	/*
	 * Loop on all tasks to check their periodicity
	 */
	for(Local_u8TaskCounter=0 ; Local_u8TaskCounter<TASK_NUM ; Local_u8TaskCounter++)
	{
		/*Check if the task suspended or not*/
		if(System_Tasks[Local_u8TaskCounter].Copy_u8State == TASK_RESUMED)
		{
			if(( System_Tasks[Local_u8TaskCounter].Copy_u16FirstDelay)==0)
			{
				/*Invoke The Task Function*/
				if(System_Tasks[Local_u8TaskCounter].Copy_pvTaskFunc != NULL)
				{
					System_Tasks[Local_u8TaskCounter].Copy_pvTaskFunc();

					/*Assign The first delay parameter to periodicity minus 1*/
					System_Tasks[Local_u8TaskCounter].Copy_u16FirstDelay = ((System_Tasks[Local_u8TaskCounter].Copy_u16Periodicity)-1);
				}
				else
				{
					//do Nothing
				}
			}
			else
			{
				/*Decrement The first delay*/
				(System_Tasks[Local_u8TaskCounter].Copy_u16FirstDelay)--;
			}
		}
		else
		{
			//Task is suspended,do Nothing
		}

	}
}

