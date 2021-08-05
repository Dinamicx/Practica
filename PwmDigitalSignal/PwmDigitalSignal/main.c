/*
 * PwmDigitalSignal.c
 *
 * Created: 8/5/2021 1:03:20 PM
 * Author : ferez
 */ 

//If F_CPU not defined
#ifndef F_CPU
//Because ATMEGA128 runs at 16MHz , UL - Unsigned Long
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

void PWM()
{
	/*set fast PWM mode(WGM 1 1) with non-inverted output(COM 0 1) and clk(CS 0 0 1)*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB4);  //set OC0 pin as output
}


int main ()
{	
	PWM();
	while (1)
	{
		OCR0 = 127; //duty cycle 50%
	}
}

