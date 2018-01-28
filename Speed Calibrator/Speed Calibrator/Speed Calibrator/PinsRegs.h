/*
 * Pins.h
 *
 * Created: 3/7/2017 6:51:42 PM
 *  Author: Fluffy
 */ 

#include <avr/io.h>

#define FALSE 0
#define TRUE 1
#define BOOL unsigned int

#ifndef PINSREGS_H_
#define PINSREGS_H_

void Set_Global_Interrupt() {SREG |= 1<<SREG_I;}
void Clear_Global_Interrupt() {SREG &= ~(1<<SREG_I);}

void Set_Int0_Rising() {MCUCR |= (1<<ISC01) | (1<<ISC00);}

void Set_Int0_Interrupt() {GICR |= 1<<INT0;}
void Clear_Int0_Interrupt() {GICR &= ~(1<<INT0);}

void Set_PD2_Input() {DDRD &= ~(1<<DDD2);}
void Set_PD2_Output() {DDRD |= 1<<DDD2;}

void Set_PB1_Input() {DDRB &= ~(1<<DDB1);}
void Set_PB1_Output() {DDRB |= 1<<DDB1;}

void Set_Timer0_NoClock() {TCCR0 = TCCR0 & ~(1<<CS02) & ~(1<<CS01) & ~(1<<CS00);}
void Set_Timer0_NoPrescale() {TCCR0 = TCCR0 & ~(1<<CS02) & ~(1<<CS01) | (1<<CS00);}
void Set_Timer0_Div8() {TCCR0 = TCCR0 & ~(1<<CS02) | (1<<CS01) & ~(1<<CS00);}
void Set_Timer0_Div64() {TCCR0 = TCCR0 & ~(1<<CS02) | (1<<CS01) | (1<<CS00);}
void Set_Timer0_Div256() {TCCR0 = TCCR0 | (1<<CS02) & ~(1<<CS01) & ~(1<<CS00);}
void Set_Timer0_Div1024() {TCCR0 = TCCR0 | (1<<CS02) & ~(1<<CS01) | (1<<CS00);}

void Set_Timer0_Interrupt() {TIMSK |= 1<<TOIE0;}
void Clear_Timer0_Interrupt() {TIMSK &= ~(1<<TOIE0);}
void Set_Timer0_Value(unsigned int value) {TCNT0 = value;}
uint8_t Get_Time0_Value() {return TCNT0;}

void Set_Timer1_NoClock() {TCCR1B = TCCR1B & ~(1<<CS12) & ~(1<<CS11) & ~(1<<CS10);}
void Set_Timer1_NoPrescale() {TCCR1B = TCCR1B & ~(1<<CS12) & ~(1<<CS11) | (1<<CS10);}
void Set_Timer1_Div8() {TCCR1B = TCCR1B & ~(1<<CS12) | (1<<CS11) & ~(1<<CS10);}
void Set_Timer1_Div64() {TCCR1B = TCCR1B & ~(1<<CS12) | (1<<CS11) | (1<<CS10);}
void Set_Timer1_Div256() {TCCR1B = TCCR1B | (1<<CS12) & ~(1<<CS11) & ~(1<<CS10);}
void Set_Timer1_Div1024() {TCCR1B = TCCR1B | (1<<CS12) & ~(1<<CS11) | (1<<CS10);}

void Set_Timer1A_FastPWMSetTop() {TCCR1A = TCCR1A | (1<<COM1A1) & ~(1<<COM1A0) | (1<<WGM11) & ~(1<<WGM10); TCCR1B = TCCR1B | (1<<WGM12) | (1<<WGM13);}

void Set_Timer1A_Compare(uint8_t compare) {OCR1A = compare;}

void Set_Timer1A_Top(uint16_t top) {ICR1 = top;}

#endif /* PINSREGS_H_ */