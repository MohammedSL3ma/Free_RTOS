/*
 * LCD_Prg.c
 *
 *  Created on: Sep 18, 2021
 *      Author: hp
 */
#include "../../LIB/stdtypes.h"
#include "../../MCAL/DIO_V1/DIO_int.h"
#include "util/delay.h"
#include "../LCD_Handler/LCD_cfg.h"

#define LCD_4_BIT_FUNCTION_SET_CMD_1       (u8)0b00100000
#define LCD_4_BIT_FUNCTION_SET_CMD_2       (u8)0b00100000
#define LCD_4_BIT_FUNCTION_SET_CMD_3       (u8)0b11000000
#define LCD_4_BIT_DISPLAY_ON_CMD_1         (u8)0b00000000
#define LCD_4_BIT_DISPLAY_ON_CMD_2         (u8)0b11000000
#define LCD_4_BIT_DISPLAY_CLEAR_CMD_1      (u8)0b00000000
#define LCD_4_BIT_DISPLAY_CLEAR_CMD_2      (u8)0b00010000
#define LCD_4_BIT_ENTRY_MODE_SET_CMD_1     (u8)0b00000000
#define LCD_4_BIT_ENTRY_MODE_SET_CMD_2     (u8)0b01100000


#define LCD_8_BIT_FUNCTION_SET_CMD       (u8)0b00111000
#define LCD_8_BIT_DISPLAY_ON_CMD         (u8)0b00001100
#define LCD_8_BIT_DISPLAY_CLEAR_CMD      (u8)0b00000001
#define LCD_8_BIT_ENTRY_MODE_SET_CMD     (u8)0b00000110
#define NULL     (void *)0


void LCD_8_BitvidsendCommand(u8 Copy_u8command);
void LCD_8_BitvidwriteCharacter(u8 Copy_u8character);
void LCD_4_BitvidsendCommand(u8 Copy_u8command);
void LCD_4_BitvidwriteCharacter(u8 Copy_u8character);

void LCD_4_BitvidInit(void)
{
	DIO_u8setPortDirection(LCD_DATA_PORT,HALF_INPUT_HALF_OUTPUT);
	DIO_u8setPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
	DIO_u8setPinDirection(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);
	DIO_u8setPinDirection(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);
	_delay_ms(40);
	LCD_4_BitvidsendCommand(LCD_4_BIT_FUNCTION_SET_CMD_1);
	LCD_4_BitvidsendCommand(LCD_4_BIT_FUNCTION_SET_CMD_2);
	LCD_4_BitvidsendCommand(LCD_4_BIT_FUNCTION_SET_CMD_3);
	_delay_ms(1);
	LCD_4_BitvidsendCommand(LCD_4_BIT_DISPLAY_ON_CMD_1);
	LCD_4_BitvidsendCommand(LCD_4_BIT_DISPLAY_ON_CMD_2);
	_delay_ms(1);
	LCD_4_BitvidsendCommand(LCD_4_BIT_DISPLAY_CLEAR_CMD_1);
	LCD_4_BitvidsendCommand(LCD_4_BIT_DISPLAY_CLEAR_CMD_2);
	_delay_ms(2);
	LCD_4_BitvidsendCommand(LCD_4_BIT_ENTRY_MODE_SET_CMD_1);
	LCD_4_BitvidsendCommand(LCD_4_BIT_ENTRY_MODE_SET_CMD_2);
}
void LCD_4_BitvidsendCommand(u8 Copy_u8command)
{
	DIO_u8setPinValue(LCD_RS_PORT, LCD_RS_PIN, LOW);
	DIO_u8setPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
	DIO_u8setPortValue(LCD_DATA_PORT,((Copy_u8command) & (HALF_LOW_HALF_HIGH)));
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_RS_PORT, LCD_RS_PIN, LOW);
	DIO_u8setPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
	DIO_u8setPortValue(LCD_DATA_PORT,((Copy_u8command<<4) & (HALF_LOW_HALF_HIGH)));
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
	_delay_ms(2);
}
void LCD_4_BitvidwriteCharacter(u8 Copy_u8character)
{
	DIO_u8setPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);
	DIO_u8setPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
	DIO_u8setPortValue(LCD_DATA_PORT,((Copy_u8character) & (HALF_LOW_HALF_HIGH)));
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);
	DIO_u8setPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
	DIO_u8setPortValue(LCD_DATA_PORT,((Copy_u8character<<4) & (HALF_LOW_HALF_HIGH)));
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
	_delay_ms(2);
}

void LCD_8_BitvidInit(void)
{
	DIO_u8setPortDirection(LCD_DATA_PORT,FULL_OUTPUT);
	DIO_u8setPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
	DIO_u8setPinDirection(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);
	DIO_u8setPinDirection(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);
	_delay_ms(40);
	LCD_8_BitvidsendCommand(LCD_8_BIT_FUNCTION_SET_CMD);
	_delay_ms(1);
	LCD_8_BitvidsendCommand(LCD_8_BIT_DISPLAY_ON_CMD);
	_delay_ms(1);
	LCD_8_BitvidsendCommand(LCD_8_BIT_DISPLAY_CLEAR_CMD);
	_delay_ms(2);
	LCD_8_BitvidsendCommand(LCD_8_BIT_ENTRY_MODE_SET_CMD);

}
void LCD_8_BitvidsendCommand(u8 Copy_u8command)
{
	DIO_u8setPinValue(LCD_RS_PORT, LCD_RS_PIN, LOW);
	DIO_u8setPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
	DIO_u8setPortValue(LCD_DATA_PORT,Copy_u8command);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
	_delay_ms(2);
}
void LCD_8_BitvidwriteCharacter(u8 Copy_u8character)
{
	DIO_u8setPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);
	DIO_u8setPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
	DIO_u8setPortValue(LCD_DATA_PORT,Copy_u8character);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
	_delay_ms(2);
}
void LCD_8_BitvidreadCharacter(u8 Copy_u8character)
{
	DIO_u8setPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);
	DIO_u8setPinValue(LCD_RW_PORT, LCD_RW_PIN, HIGH);
	DIO_u8setPortValue(LCD_DATA_PORT,Copy_u8character);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(2);
	DIO_u8setPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
	_delay_ms(2);
}
void LCD_8_BitvidwriteString(const char* Copy_p2cString)
{
	if(Copy_p2cString != NULL)
	{
		u8 Local_u8Counter=0;
		while(Copy_p2cString[Local_u8Counter]!='\0')
		{
			LCD_8_BitvidwriteCharacter(Copy_p2cString[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
}
void LCD_8_BitvidGoToXY(u8 Copy_u8XPos , u8 Copy_u8YPos)
{
	u8 Local_u8Address;
	if(Copy_u8XPos==0)
	{
		Local_u8Address=Copy_u8YPos;
	}
	else if(Copy_u8XPos==1)
	{
		Local_u8Address=Copy_u8YPos + 0X40;
	}
	LCD_8_BitvidsendCommand(Local_u8Address+128);
}
void LCD_8_BitvidwriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8PatternNumber, u8 Copy_u8XPos , u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress=0 , Local_u8Iterator;
	/*Calculate CGRam Address whose each block is 8 bytes*/
	Local_u8CGRAMAddress=Copy_u8PatternNumber*8;
	/*Send CGRam Address Command to LCD, with setting bit 6, clearing bit 7*/
	LCD_8_BitvidsendCommand(Local_u8CGRAMAddress+64);
	/*Write the Pattern into CGRam*/
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		LCD_8_BitvidwriteCharacter(Copy_pu8Pattern[Local_u8Iterator]);
	}
	/*Go Back to DDRam to Display the Pattern*/
	LCD_8_BitvidGoToXY(Copy_u8XPos,Copy_u8YPos);
	/*Display the Pattern Written in CGRam*/
	LCD_8_BitvidwriteCharacter(Copy_u8PatternNumber);
}
void LCD_8_BitvidwriteInt(u32 copy_u8number)
{
	u32 temp = copy_u8number;
	u8 digit[7];
	u8 lenght = 0;
	s8 i;
	if(temp==0)
	{
		LCD_8_BitvidwriteCharacter('0');
	}
	else
	{
		while(temp!=0)
		{
			digit[lenght]=temp%10;
			temp/=10;
			lenght++;
		}
		for(i=lenght-1;i>=0;i--)
		{
			LCD_8_BitvidwriteCharacter(digit[i]+'0');
		}
	}
}


