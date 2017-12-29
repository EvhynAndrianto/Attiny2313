#include <avr/io.h>

void Delay(void);

int main(void)
{
	// LEDs are on pins PB0
	DDRB |= (1 << PB0);  // set as output pin
	
	while(1)
	{
		PORTB &= ~(1 << PB0); // turn led on

		
		Delay();

		
		PORTB |=  (1 << PB0); // turn led off

		Delay();

	}
}

void Delay(void)
{
	volatile unsigned int del = 40000;
	
	while(del--);
}