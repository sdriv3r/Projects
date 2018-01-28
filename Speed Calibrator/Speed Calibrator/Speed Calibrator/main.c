/*
* Speed Calibrator.c
*
* Created: 3/7/2017 6:49:45 PM
* Author : Fluffy
*/

#include "PinsRegs.h"
#include <avr/interrupt.h>


#define CORRECTIONFACTOR 1.1

void SetOutputFrequency (uint_fast16_t frequency);


// Sub-Tick: Running at 8MHz and Timer Div64, 1 bit is 0.000008s
uint_fast32_t	currentTicks = 0; //488.28125 = 1 second
uint_fast32_t	prevTick = 0;
uint_fast8_t	prevSubTick = 0;

uint_fast16_t inputFrequency = 0; //Frequency, in Hz, of the input signal.


int main(void)
{
	Set_Global_Interrupt();
	Set_PD2_Input();
	Set_Int0_Rising();
	Set_Int0_Interrupt();
	Set_PB1_Output();

	Set_Timer1A_FastPWMSetTop();
	Set_Timer1_Div1024();

	Set_Timer0_Div64();
	Set_Timer0_Interrupt();

	uint_fast16_t currentFrequency = 0;
	while (1)
	{
		if (currentFrequency != inputFrequency)
		{
		currentFrequency = inputFrequency;
			SetOutputFrequency(currentFrequency);
		}
	}
}

ISR (TIMER0_OVF_vect)
{
	currentTicks++;
}

ISR (INT0_vect)
{
	uint8_t currentSubTick = TCNT0;
	inputFrequency = 125000/((currentTicks - prevTick)*256 + currentSubTick - prevSubTick);

	prevTick = currentTicks;
	prevSubTick = currentSubTick;
}

void SetOutputFrequency (uint_fast16_t frequency)
{
	uint_fast16_t top = lround(7812.5 / frequency*CORRECTIONFACTOR - 1);
	ICR1 = top;
	OCR1A = top/2;
}