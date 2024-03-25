/*
 * main.c
 *
 * Created: 3/25/2024 6:47:14 PM
 *  Author: liqui
 */ 

#include <xc.h>
#include <avr/interrupt.h>

#define F_CPU 1000000

#include <util/delay.h>

void timer_init(){
	TCCR0A = 0x02; // put a 1 in bit position 1, which sets Mode 2 aka in the WGM01 bit which activates CTC Timer Mode.
	// DONT PRESCALE, JUST USE SYSTEM CLOCK SPEED //TCCR0B = 0x05; //0b0000 0101 put a 101 in bit positions 2,1,0 in order to scale clock by 1024... e.g. from 1Mhz to 977Hz.
	//... NB TCCR0B will need at least the 0th position bit setting in order for TIMER to start, but this is done here in send_to_uart function. 
	OCR0A = 249; //103; // count up 104 (0->103) clock periods in order to achieve baud rate of 9600 Hz (as 1M / 9600 = 104). 
	TIMSK |= 0x10; // 0b00010000 this mask is used to set bit position 4 to HIGH, which is for OCIE0A as we want Timer Compare Match A
	sei(); // enable interrupt.
}

volatile uint16_t uartData = 0; 


void send_to_uart(char c){
	
	uartData = c << 1; // shift char to left in order to put a 0 in the 0th bit position, indicating a UART start BIT 
	uartData |= 1 << 9; // write a 1 into the 9th position to indicate a UART stop BIT. 
	// Now start the timer that is used to achieve the baud rate of 9600
	TCCR0B = 1 << 0; // simply a 1 in 0th bit position will activate timer with no scaling. 
}

int main(void)
{
	DDRB = 0x01; // sets direction of pin0 to be an output....
	PORTB |= 1 << PB0; // start the pin0 at HIGH becuase UART signals that data needs sending with a HIGH to LOW transition, therefore need HIGH to begin with
	timer_init();
	
	while(1)
	{
		send_to_uart('Z');
		_delay_ms(1000);
	}
}

ISR(TIM0_COMPA_vect){
	
	if(uartData & 0x01){ // if LSB of uartData is a 1, set the output pin to 1 to match it, thereby sending that value as output
		PORTB |= 1 << PB0;
	}
	else{ // if LSB of uartData is a 0, also set the output pin to this value, but this time the value is a 0
		PORTB &= ~(1 << PB0);
	}
	
	uartData = uartData >> 1; // shift all the values along so the LSB drops off the end... ready for processing the next BIT...
	
	if(uartData == 0){ // if uartData has all been processed and shifted off the end into oblivion, then it is done. 
		
		TCNT0 = 0; // reset the counter
		TCCR0B = 0; // stops the timer, as no longer need to achieve  baud rate as the data has now finished being sent. 
	}
}