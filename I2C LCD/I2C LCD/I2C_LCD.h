/*
 * I2C_LCD.h
 *
 * Created: 2018-01-29 10:36:39 PM
 *  Author: Fluffy
 */ 

#define DEGREE 0xDF
#define LINE_2 64

#ifndef I2C_LCD_H_
#define I2C_LCD_H_

void LCD_Init();
void LCD_Display(char c);
void LCD_SetCursor(uint8_t position);


void I2C_Init();
void SendI2C(char c);



#endif /* I2C_LCD_H_ */