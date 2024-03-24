/*
 * main.c
 *
 * Created: 3/6/2024 12:28:16 PM
 *  Author: liqui
 */ 
#include <avr/io.h>
#include <xc.h>

#define F_CPU 1000000UL

#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << DDB1); // Set direction register to HIGH in the 0th position (starts at 0th position) in order to set as output pin
    while(1)
    {
		PORTB ^= (1 << PB1); // setting a 1 into this PINB variable will result in toggle action (see datasheet for why). 
		_delay_ms(500);
		
		/*PORTB &= ~(1 << PB1); // set PB1 to LOW... by taking inverse of setting a 1 in that position, then ANDing with that resulting mask...
		_delay_ms(500);
		
		PORTB |= (1 << PB1); // set PB1 to be HIGH
		_delay_ms(500); // wait for human seeability
		*/
		
        //TODO:: Please write your application code 
    }
}