/*
 * RTOS_Interface.h
 *
 *  Created on: 10 Dec 2023
 *      Author: Selim
 */

#ifndef RTOS_LAYER_RTOS_INTERFACE_H_
#define RTOS_LAYER_RTOS_INTERFACE_H_

typedef struct
{
	void (*Copy_pvTaskFunc)(void);
	u8 Copy_u8State;
	u8 Copy_u8Priority;
	u16 Copy_u16Periodicity;
	u16 Copy_u16FirstDelay;
}CreateTask_FuncArgus;

typedef enum
{
  NOK,
  OK,
}Error_States;

typedef enum
{
	TASK_RESUMED,
	TASK_SUSPENDED
}Task_States;

void RTOS_voidStart(void);

u8 RTOS_u8CreateTask(CreateTask_FuncArgus * FuncArgus);

void RTOS_voidSuspendTask(u8 Copy_u8Priority);

void RTOS_voidResumeTask(u8 Copy_u8Priority);

void RTOS_voidDeleteTask(u8 Copy_u8Priority);

#endif /* RTOS_LAYER_RTOS_INTERFACE_H_ */
