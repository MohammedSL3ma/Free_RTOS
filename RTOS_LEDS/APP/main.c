/*
 * main.c
 *
 *  Created on: 17 Dec 2023
 *      Author: Selim
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/stdtypes.h"

#include "../MCAL/DIO_V1/DIO_int.h"

#include "../HAL/LEDS_Handler/LED_interface.h"
#include "../HAL/SEG_Handler/SSD_interface.h"

#include "../RTOS_Layer/RTOS_Interface.h"



#define SSD_COUNT (u8) 0
#define LED1      (u8) 1
#define LED2      (u8) 2
#define LED3      (u8) 3


void LED_1(void);
void LED_2(void);
void LED_3(void);
void SSD_voidCount(void);

void create_task(void)
{
	CreateTask_FuncArgus SSD_task;
	SSD_task.Copy_u8Priority = SSD_COUNT;
	SSD_task.Copy_u8State = TASK_RESUMED;
	SSD_task.Copy_u16Periodicity = 1000;
	SSD_task.Copy_u16FirstDelay = 0 ;
	SSD_task.Copy_pvTaskFunc = &SSD_voidCount;
	RTOS_u8CreateTask(&SSD_task);

	CreateTask_FuncArgus LED_1_task;
	LED_1_task.Copy_u8Priority = LED1;
	LED_1_task.Copy_u8State = TASK_SUSPENDED;
	LED_1_task.Copy_u16Periodicity = 60000;
	LED_1_task.Copy_u16FirstDelay = 0 ;
	LED_1_task.Copy_pvTaskFunc = &LED_1;
	RTOS_u8CreateTask(&LED_1_task);

	CreateTask_FuncArgus LED_2_task;
	LED_2_task.Copy_u8Priority = LED2;
	LED_2_task.Copy_u8State = TASK_SUSPENDED;
	LED_2_task.Copy_u16Periodicity = 5000;
	LED_2_task.Copy_u16FirstDelay = 0;
	LED_2_task.Copy_pvTaskFunc = &LED_2;
	RTOS_u8CreateTask(&LED_2_task);

	CreateTask_FuncArgus LED_3_task;
	LED_3_task.Copy_u8Priority = LED3;
	LED_3_task.Copy_u8State = TASK_SUSPENDED;
	LED_3_task.Copy_u16Periodicity = 10000;
	LED_3_task.Copy_u16FirstDelay = 0;
	LED_3_task.Copy_pvTaskFunc = &LED_3;
	RTOS_u8CreateTask(&LED_3_task);



}

void main(void)
{

	LED_voidInit(PORT_B,PIN_3);
	LED_voidInit(PORT_B,PIN_4);
	LED_voidInit(PORT_B,PIN_5);
	SSD_voidInit();


	create_task();
	RTOS_voidStart();
	while(1)
	{

	}
}

void LED_1(void)
{
	LED_voidOn(PORT_B,PIN_3,LED_FORWARD_CONNECTION);
	LED_voidOff(PORT_B,PIN_4,LED_FORWARD_CONNECTION);
	LED_voidOff(PORT_B,PIN_5,LED_FORWARD_CONNECTION);
}
void LED_2(void)
{
	LED_voidOff(PORT_B,PIN_3,LED_FORWARD_CONNECTION);
	LED_voidOn(PORT_B,PIN_4,LED_FORWARD_CONNECTION);
	LED_voidOff(PORT_B,PIN_5,LED_FORWARD_CONNECTION);
}
void LED_3(void)
{
	LED_voidOff(PORT_B,PIN_3,LED_FORWARD_CONNECTION);
	LED_voidOff(PORT_B,PIN_4,LED_FORWARD_CONNECTION);
	LED_voidOn(PORT_B,PIN_5,LED_FORWARD_CONNECTION);
}

void SSD_voidCount(void)
{
	static u8 local_u8Counter = 0;
	local_u8Counter++;
	if(local_u8Counter <= 60)
	{
		SSD_voidDisplayMultiplexedNumber(local_u8Counter);
		RTOS_voidResumeTask(LED1);
		RTOS_voidSuspendTask(LED2);
		RTOS_voidSuspendTask(LED3);
	}
	else if(local_u8Counter > 60 && local_u8Counter <= 66)
	{
		SSD_voidDisplayMultiplexedNumber(local_u8Counter - 60);
		RTOS_voidResumeTask(LED2);
		RTOS_voidSuspendTask(LED1);
		RTOS_voidSuspendTask(LED3);
	}
	else if(local_u8Counter > 66 && local_u8Counter <= 76)
	{
		SSD_voidDisplayMultiplexedNumber(local_u8Counter - 66);
		RTOS_voidResumeTask(LED3);
		RTOS_voidSuspendTask(LED1);
		RTOS_voidSuspendTask(LED2);
	}
	else
	{
		local_u8Counter = 0;
		RTOS_voidSuspendTask(LED1);
		RTOS_voidSuspendTask(LED2);
		RTOS_voidSuspendTask(LED3);

	}

}
