/*
* I2C LCD.c
*
* Created: 2018-01-28 5:07:27 PM
* Author : Fluffy
*/

#include <avr/io.h>
#include <util/delay.h>
#include "I2C_LCD.h"
#include <avr/interrupt.h>

#define F_CPU 1000000UL

void Temp_Init();
void Timer0Init();

uint16_t GetTemp();

uint8_t setTemp = 180;
uint32_t time = 0;	//In 1/4 seconds.

int main(void)
{
	DDRD = 0x01;	// Set pin as output.
	
	sei();
	Timer0Init();
	Temp_Init();
	LCD_Init();
	
	LCD_Display('T');
	LCD_Display('E');
	LCD_Display('M');
	LCD_Display('P');
	LCD_Display(':');
	LCD_Display('-');
	LCD_Display('-');
	LCD_Display(DEGREE);
	
	LCD_SetCursor(LINE_2 + 2);
	
	LCD_Display('S');
	LCD_Display('E');
	LCD_Display('T');
	LCD_Display(' ');
	LCD_Display('T');
	LCD_Display('E');
	LCD_Display('M');
	LCD_Display('P');
	LCD_Display(':');
	LCD_Display('-');
	LCD_Display('-');
	LCD_Display(DEGREE);

	while (1)
	{
		_delay_ms(500);
		LCD_SetCursor(5);
		uint16_t temp = GetTemp();
		LCD_Display(temp/100 + 48);
		LCD_Display((temp%100)/10 + 48);
		LCD_Display('.');
		LCD_Display(temp%10 + 48);
		LCD_Display(DEGREE);
		
		LCD_SetCursor(LINE_2 + 11);
		LCD_Display(setTemp/100 + 48);
		LCD_Display((setTemp%100)/10 + 48);
		LCD_Display('.');
		LCD_Display(setTemp%10 + 48);
		LCD_Display(DEGREE);
		
		if ((PORTD == 0x00) & (temp > (setTemp + 25)) & (time > 3600))	// Best values for 15 degrees are -1 +3.
		{
			LCD_SetCursor(11);
			LCD_Display('O');
			LCD_Display('N');
			PORTD = 0x01;
		}
		if ((PORTD == 0x01) & (temp < (setTemp - 5)))
		{
			LCD_SetCursor(11);
			LCD_Display('O');
			LCD_Display('F');
			LCD_Display('F');
			PORTD = 0x00;
			time = 0;	// Reset the "time". This is to measure the off cycle.
		}
	}
}

void Temp_Init()
{
	ADMUX = 0x40;	// Internal 5V ref.
	ADCSRA = 0xE3;	// Enable in freerun mode, clock set to 125 kHz.
}

void Timer0Init()
{
	TCCR0 = 0x05;	//Prescaler is 1024.
	TIMSK = 0x01;
}

uint16_t GetTemp()
{
	uint16_t uiRead = ADCL;
	uiRead += (ADCH << 8);
	
	float read = (float)uiRead;
	//float result = 0.408*read-26.753;
	float result = (-0.00002*read*read+0.1157*read-29.301)*10;
	return (uint16_t)result;
}

ISR(TIMER0_OVF_vect)
{
	time++;
}