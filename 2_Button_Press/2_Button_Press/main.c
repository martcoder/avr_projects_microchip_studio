/*
 * main.c
 *
 * Created: 3/24/2024 11:05:15 PM
 *  Author: liqui
 */ 

#include <xc.h>
#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
	
	DDRB = 0x02; // 0b00000010 so basically settting bit0 to be input (for button), and bit1 to be output (for LED)
	PORTB = 0x01; // 0b00000001 so this is setting LED to LOW initially, and pulling the button input up to HIGH initially...
	
    while(1)
    {
        //TODO:: Please write your application code 
		// basically check if button/switched has been pressed, if so PINB will be pulled to GND aka 0, and the AND op will return 0, therefore
		// ... if statement condition will be TRUE...
		if( (PINB & (1 << PINB0)) == 0 ){ //this code is so funny, 1 << PINB0 is 1 << 0, which is just 1, or 0b00000001
			//if TRUE aka BUTTON/SWITCH has been pressed
			// Switch the LED on....
			PORTB |= (1 << PB1); // this is also funny, 1 << 1 which becomes 0b00000010, basically sets bit position 1 HIGH which is the LED output pin
		}
		else{ // the button/switch has not been pressed so the LED output pin is still set HIGH. 
			//... Therefore the if condition is FALSE as 1 & 1 = 1 ... 
			//... also i want the else to have the LED flashing at a low LUX level, lol, rather than just switch if off. 
			
			// THE FOLLOWING SECTION IS COMMENTED AS THE FLASHING IS DISCERNIBLE TO THE HUMAN EYE
			// Toggle the LED output pin by XORing with a 1 at the LED output pin position... 
			/*PORTB ^= (1 << PB1); // Does XOR with 0b00000010 ... If the output pin bit is 1 then (bit1 XOR 1 = 0), if that bit is 0 then (bit0 XOR 1 = 1), therefore it toggles each time.  
			_delay_ms(50);
			*/
			
			//THE FOLLOWING CODE RESULTS IN A DIMLY LIT LED AND THE FLASHING IS NOT DISCERNIBLE!!! 
			//Here it's OFF for 9ms then ON for only 0.2ms, so should be fairly dim....
			PORTB &= ~(1 << PB1);
			_delay_ms(9);
			PORTB |= (1 << PB1);
			_delay_us(200);
		}
    }
}