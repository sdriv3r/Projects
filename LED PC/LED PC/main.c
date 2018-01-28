/*
* LED PC.c
*
* Created: 2017-08-25 11:35:51 PM
* Author : Fluffy
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "Comm.h"

typedef uint8_t BOOL;
#define TRUE 1;
#define FALSE 0;

unsigned char serialBuff[16];
uint8_t serialCount;
uint8_t red;
uint8_t green;
uint8_t blue;
uint8_t timer0Count = 0;
uint8_t timer1Count = 0;
uint8_t timer2Count = 0;

void initLED()
{
	DDRD = 0xff;
}

void loadColor()
{
	red = eeprom_read_byte((uint8_t*)0);
	green = eeprom_read_byte((uint8_t*)1);
	blue = eeprom_read_byte((uint8_t*)2);
}

void initTimers()
{
	TCCR0 = 0x01; //internal clock, no prescaler

	
	TCCR1B |= (1 << WGM12) | (1 << CS10);
	
	TCCR2 |= (1 << CS20);
	
	OCR1A = 0xff;
	
	TIMSK |= (1 << TOIE0) | (1 << OCIE1A) | (1 << TOIE2);
}

int main(void)
{
	initLED();
	loadColor();
	initSerial();
	initTimers();
	
	sei(); //Enable interrupts.
	
	/* Replace with your application code */
	//PORTD |= (1 << PD4);  // RED
	//PORTD |= (1 << PD3);   // GREEN
	//PORTD |= (1 << PD2);  //BLUE
	
	_delay_ms(500);
	while (1)
	{
		if(UCSRA & (1 << RXC))
		{
			readLine();
			if (serialCount > 3)
			{
				setValue();
			}
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	timer0Count++;
	if (timer0Count == red)
	{
		PORTD &= ~(1 << PD4);
	}
	if ((timer0Count > 254) & (red != 0))
	{
		PORTD |= (1 << PD4);
		timer0Count=0;
	}
}

ISR(TIMER2_OVF_vect)
{
	timer2Count++;
	if (timer2Count == green)
	{
		PORTD &= ~(1 << PD3);
	}
	if ((timer2Count > 254) & (green != 0))
	{
		PORTD |= (1 << PD3);
		timer2Count=0;
	}
}

ISR(TIMER1_COMPA_vect)
{
	timer1Count++;
	if (timer1Count == blue)
	{
		PORTD &= ~(1 << PD2);
	}
	if ((timer1Count > 254)& (blue != 0))
	{
		PORTD |= (1 << PD2);
		timer1Count=0;
	}
}