/*
 * LED_program.c
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */


/* UTILES_LIB */
#include "../../LIB/stdtypes.h"
#include "../../LIB/BIT_MATH.h"

/* MCAL */
#include "../../MCAL/DIO_V1/DIO_int.h"

/* HAL */
#include "LED_interface.h"


void LED_voidInit(u8 copy_u8LedPort, u8 copy_u8LedPin)
{
	DIO_u8setPinDirection(copy_u8LedPort, copy_u8LedPin,OUTPUT);
}


void LED_voidOn(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType)
{
	switch(copy_u8LedConnectionType)
	{
	case LED_FORWARD_CONNECTION:
		DIO_u8setPinValue(copy_u8LedPort, copy_u8LedPin, HIGH);
		break;

	case LED_REVERSE_CONNECTION:
		DIO_u8setPinValue(copy_u8LedPort, copy_u8LedPin, LOW);
		break;

	default :
		// return Error State
		break;
	}
}


void LED_voidOff(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType)
{
	switch(copy_u8LedConnectionType)
	{
	case LED_FORWARD_CONNECTION:
		DIO_u8setPinValue(copy_u8LedPort, copy_u8LedPin, LOW);
		break;

	case LED_REVERSE_CONNECTION:
		DIO_u8setPinValue(copy_u8LedPort, copy_u8LedPin, HIGH);
		break;

	default :
		// return Error State
		break;
	}
}


void LED_voidToggle(u8 copy_u8LedPort, u8 copy_u8LedPin)
{
	DIO_u8togglePinValue(copy_u8LedPort, copy_u8LedPin);
}
