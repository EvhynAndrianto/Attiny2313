#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint32_t miliseconds;

int main(void)
{
	miliseconds = 0;

	// output pin
	DDRB |= (1 << PB0);		//LED


	/*
	source:
	http://www.engblaze.com/microcontroller-tutorial-avr-and-arduino-timer-interrupts/

	Timer 0 is an 8-bit timer/counter
	since timer0 is 8 bits, it can hold a maximum value of (2^8 -1) or 255.

	In this program we're using 1Mhz clock and divide our clock source by 8.
	This gives us a timer resolution of 1/(1,000,000/8) or 0.000008 seconds.
	The timer will overflow every (255*0.000008) or 0.002048 seconds

	To use CTC and To get 0.1 s or 100 ms interval assuming we keep the 8 prescaler as before
	we can calculate as follow:
	(target time) = (timer resolution) * (#timer counts + 1)
	(#timer counts + 1) = (target time) / (timer resolution)
	(#timer counts + 1) = (0.001) / (0.000008)
	(#timer counts) = 125 - 1
	(#timer counts) = 124

	we added extra +1 because when the timer matches our desired count, it will reset itself to zero.
	This takes one clock cycle to perform.

	The timer period is:
	(124+1) * 0.000008 = 0.001 seconds
	Thus the error is  0 %

	for more precise timer with fraction problem check the following link:
	https://ucexperiment.wordpress.com/2012/03/16/examination-of-the-arduino-millis-function/

	*/

	//cli();

	OCR0A = 124;	//number to count up to 124
	TCCR0A = 0x02;	//clear timer on compare match
	TIFR |= 0x01;	//clear interrupt flag
	TIMSK = 0x01;	//TC0 compare match A interrupt enable
	TCCR0B = 0x02;	//clock source CLK/8, start timer

	sei();			//global interrupt enable

	while(1)
	{
	    //the led will flash every 1 second
	    if(miliseconds == 1000)
        {
            PORTB ^= (1<<0);
            miliseconds=0;
        }

	}
}



ISR(TIMER0_COMPA_vect)
{
    //Interrupt and increment every 1 ms.
	miliseconds++;
}
