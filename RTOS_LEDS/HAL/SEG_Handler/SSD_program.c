/******************************************************************************
 *                                                                            *
 *************************  SWC     : SSD_program     *************************
 *************************  Date    : 25/02/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/


//#define F_CPU 8000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "../../LIB/stdtypes.h"
#include "../../LIB/BIT_MATH.h"

/* MCAL */
#include "../../MCAL/DIO_V1/DIO_int.h"

/* HAL */
#include "SSD_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"

static u8 PRV_u8Numbers[10]= {SSD_ZERO, SSD_ONE, SSD_TWO, SSD_THREE, SSD_FOUR, SSD_FIVE, SSD_SEX, SSD_SEVEN, SSD_EIGHT, SSD_NINE};

void SSD_voidInit(void)
{
	DIO_u8setPortDirection(SSD_DATA_PORT, OUTPUT);
	DIO_u8setPinDirection(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, OUTPUT);
	DIO_u8setPinDirection(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, OUTPUT);
}


void SSD_voidDisplayNumber(u8 copy_u8DesiredNumber, u8 copy_u8Id)
{
	if(copy_u8DesiredNumber<=9)
	{
		switch(copy_u8Id)
		{
		    case SSD_1:
#if SSD_TYPE == SSD_COM_CATHODE
			DIO_u8setPortValue(SSD_DATA_PORT, PRV_u8Numbers[copy_u8DesiredNumber]);
			DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, LOW);

#elif SSD_TYPE == SSD_COM_ANNODE
			DIO_u8setPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[copy_u8DesiredNumber]);
			DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, HIGH);
#endif
			break;

		    case SSD_2:
#if SSD_TYPE == SSD_COM_CATHODE
			DIO_u8setPortValue(SSD_DATA_PORT, PRV_u8Numbers[copy_u8DesiredNumber]);
			DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, LOW);

#elif SSD_TYPE == SSD_COM_ANNODE
			DIO_u8setPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[copy_u8DesiredNumber]);
			DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, HIGH);
#endif
			break;
		}
	}
	else
	{
		// return Error state
	}
}


void SSD_voidDisplayMultiplexedNumber(u8 copy_u8DesiredNumber)
{
	if(copy_u8DesiredNumber<=99)
	{
		u8 local_u8Ones = copy_u8DesiredNumber%10;
		u8 local_u8Tens = copy_u8DesiredNumber/10;

#if SSD_TYPE == SSD_COM_CATHODE
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, HIGH);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, HIGH);
		DIO_u8setPortValue(SSD_DATA_PORT, PRV_u8Numbers[local_u8Tens]);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, LOW);
		_delay_ms(10);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, HIGH);

		DIO_u8setPortValue(SSD_DATA_PORT, PRV_u8Numbers[local_u8Ones]);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, LOW);
		_delay_ms(10);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, HIGH);

#elif SSD_TYPE == SSD_COM_ANNODE
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, LOW);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, LOW);
		DIO_u8setPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[local_u8Tens]);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, HIGH);
		_delay_ms(10);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, LOW);

		DIO_u8setPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[local_u8Ones]);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, HIGH);
		_delay_ms(10);
		DIO_u8setPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, LOW);
#endif
	}
	else
	{
		// return Error state
	}
}
