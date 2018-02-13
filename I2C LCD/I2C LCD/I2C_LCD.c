/*
* I2C_LCD.c
*
* Created: 2018-01-29 10:36:18 PM
*  Author: Fluffy
*/

#include <avr/io.h>
#include "I2C_LCD.h"

void LCD_Init()
{
	I2C_Init();
	
	SendI2C(0x2C); // Set 4 bit operation
	SendI2C(0x28);
	
	SendI2C(0x2C); // Set 4 bit operation
	SendI2C(0x28);
	
	SendI2C(0x8C); // Set 2 lines and default font
	SendI2C(0x88);
	
	SendI2C(0x0C); // Turn on display
	SendI2C(0x08);
	SendI2C(0xCC);
	SendI2C(0xC8);
	
	SendI2C(0x0C); // Increment address by 1 and shift cursor right.
	SendI2C(0x08);
	SendI2C(0x6C);
	SendI2C(0x68);
}

void LCD_Display(char c)
{
	SendI2C((c&0xF0)+ 0x0D);
	SendI2C((c&0xF0)+ 0x09);
	
	SendI2C((c << 4) + 0x0D);
	SendI2C((c << 4) + 0x09);
}

void LCD_SetCursor(uint8_t position)
{
	SendI2C((position & 0xF0) + 0x8C);
	SendI2C((position & 0xF0) + 0x88);
	
	SendI2C((position << 4) + 0x0C);
	SendI2C((position << 4) + 0x08);
}


void I2C_Init()
{
	TWBR = 0x01;	// Set divisor to 1.
	TWSR = 0x00;	// Set prescaler to 1. Total frequency should be 41.66 kHz.
}

void SendI2C(char c)
{
	TWCR |= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);	// Send START.
	
	while (!(TWCR & (1<<TWINT)));	// Wait for START to be sent.
	
	TWDR = 0x4E;	// Slave address.
	TWCR = (1<<TWINT) | (1<<TWEN);	// Transmit.
	
	while (!(TWCR & (1<<TWINT)));	// Wait for transmission to end.
	
	TWDR = c;	// Loading DATA.
	
	TWCR = (1<<TWINT) | (1<<TWEN);	// Transmitting DATA.
	
	while (!(TWCR & (1<<TWINT)));	// Wait for transmission to end.
	
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);	// Send STOP;
}