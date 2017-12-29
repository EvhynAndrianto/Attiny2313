#include <avr/io.h>


int main(void)
{
	// output pin
	DDRB |= (1 << PB0);		//LED
	
	// input pin
	DDRB &= ~(1 << PB1);	//switch
	PORTB |= (1 << PB1);	//enable pull-up resistor
	
	while(1)
	{
		if (PINB & (1 << PB1)){		// is switch open?
			
			PORTB |= (1 << PB0);	// switch is open, switch LED off
		}
		else{
			PORTB &= ~(1 << PB0);	// switch is closed, switch LED on
		}
		
	}
}
