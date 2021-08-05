/*
 * Interrrupts.c
 *
 * Created: 7/25/2021 2:45:21 PM
 * Author : ferez
 */ 

//If F_CPU not defined
#ifndef F_CPU
//Because ATMEGA128 runs at 16MHz , UL - Unsigned Long
#define F_CPU 16000000UL
#endif

#define PORT_LED0	PORTC
#define PIN_LED0	PINC0
#define PORT_LED1	PORTC
#define PIN_LED1	PINC1
#define SWITCH_K0    !(PIND & (1<<PIND0))
#define SWITCH_K1    !(PIND & (1<<PIND1))
// !(PIND & (1 << PIND0) == (1 << PIND0))

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);



/*Interrupt Service Routine for INT0*/
ISR(INT1_vect)
{

		pinReset(&PORT_LED0, PIN_LED0);
		pinReset(&PORT_LED1, PIN_LED1);

}

ISR(INT0_vect)
{

		pinSet(&PORT_LED0, PIN_LED0);
		pinSet(&PORT_LED1, PIN_LED1);

}


int main()
{	
   	DDRC = 0xFF;
   	PORTC = 0;
	DDRD &= ~(1 << PIND1) | ~(1 << PIND0); //Pins for input (both pins to 0)
    PORTD |= (1 << PIND1) | (1 << PIND0); //Pull-up resistors
		
    EIMSK |= (1 << INT1) | (1 << INT0); //Allow ext interrupts
	EICRA |= (1 << ISC01) | (1 << ISC11); //External interrupt configuration register

 	sei(); //Allow global interrupts
	while (1) continue;
}


void pinSet(volatile uint8_t *port, uint8_t pin){
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin){
	*port &=  ~(1 << pin);
}


