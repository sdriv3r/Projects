/*
* Comm.c
*
* Created: 2017-11-22 8:37:15 PM
*  Author: Fluffy
*/

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/eeprom.h>

#include "Comm.h"
#include "Variables.h"

unsigned char serialBuff[16];
uint8_t serialCount = 0;;
uint8_t red;
uint8_t green;
uint8_t blue;

void initSerial()
{
	int UBBRValue = 51;
	UBRRH = (unsigned char) (UBBRValue >> 8);
	UBRRL = (unsigned char) UBBRValue;			// baud rate is 12410
	UCSRB|= (1<<TXEN)|(1<<RXEN)/*|(1<<RXCIE)*/;		// enable receiver and transmitter. Also enable receive interrupt.
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void readLine()
{
	serialCount = 0;
	memset(serialBuff, 0, sizeof(serialBuff));
	
	serialBuff[serialCount] = receive();
	
	while (serialBuff[serialCount] != '\r')
	{
		if (UCSRA & (1 << RXC))
		{
			serialCount++;
			serialBuff[serialCount] = receive();
		}
	}
	serialCount++;
	
	serialBuff[serialCount] = '\0';
	
	if((serialCount>3)&!checksumValid())
	{
		requestResend();
		serialCount = 0;
	}
}

void setValue()
{
	if(serialBuff[0] == 'r')
	{
		if (eeprom_read_byte((uint8_t*)0) != (uint8_t)serialBuff[2])
		{
			eeprom_write_byte((uint8_t*)0, (uint8_t)serialBuff[2]);
		}
		red = serialBuff[2];
	}
	else if (serialBuff[0] == 'g')
	{
		if (eeprom_read_byte((uint8_t*)1) != (uint8_t)serialBuff[2])
		{
			eeprom_write_byte((uint8_t*)1, (uint8_t)serialBuff[2]);
		}
		green = serialBuff[2];
	}
	else if (serialBuff[0] == 'b')
	{
		if (eeprom_read_byte((uint8_t*)2) != (uint8_t)serialBuff[2])
		{
			eeprom_write_byte((uint8_t*)2, (uint8_t)serialBuff[2]);
		}
		blue = serialBuff[2];
	}
}

uint8_t checksumValid()
{
	return ((serialBuff[0]^serialBuff[1]^serialBuff[2]) == serialBuff[3]);
}

void requestResend()
{
	transmit('c');
	transmit('h');
	transmit('e');
	transmit('c');
	transmit('k');
	transmit('s');
	transmit('u');
	transmit('m');
	transmit('\n');
}

void transmit (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));                // wait while register is free
	UDR = data;
}

unsigned char receive()
{
	unsigned char data;
	while(!(UCSRA) & (1<<RXC));                   // wait while data is being received
	data = UDR;
	UCSRB &= ~(1<<RXEN);
	UCSRB |=(1<<RXEN);
	transmit(data);
	_delay_ms(20);
	return data;
}