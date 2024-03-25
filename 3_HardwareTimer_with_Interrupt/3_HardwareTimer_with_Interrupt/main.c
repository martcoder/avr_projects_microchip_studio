/*
 * main.c
 *
 * Created: 3/25/2024 3:05:51 PM
 *  Author: liqui
 */ 

#include <xc.h>
#include <avr/interrupt.h>

#define F_CPU 1000000

int main(void)
{
	DDRB = 0x01; // sets direction of pin0 to be an output....
	PORTB &= 0xFE; // set the pin0 to LOW... becuase 0xFE is a mask of 0b11111110 which will only set the LSB to 0...
	
	TCCR0A = 0x02; // put a 1 in bit position 1, which sets Mode 2 aka in the WGM01 bit which activates CTC Timer Mode. 
	TCCR0B = 0x05; //0b0000 0101 put a 101 in bit positions 2,1,0 in order to scale clock by 1024... e.g. from 1Mhz to 977Hz. 
	OCR0A = 249; // count up 250 (0->249) clock periods before timer resets. As clock is 977Hz, each clock T is 1/977 = 1msec. Therefore timer counts for 250msec which should be human visible for a toggling LED...
	TIMSK |= 0x10; // 0b00010000 this mask is used to set bit position 4 to HIGH, corresponding with OCIE0A which is Counter Match A
	sei(); // enable interrupt. 
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

ISR(TIM0_COMPA_vect){
	
	PORTB ^= 1; // toggle the bit at 1st position in PORTB, which will switch the LED on and OFF using the hardware timer this time :)
	TCNT0 = 0; // reset timer
}