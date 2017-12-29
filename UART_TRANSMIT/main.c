#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h> //to use itoa (integer ton of ASCII)


void USART_Init(unsigned int baud)
{
	/*set baud rate*/
	UBRRH = (unsigned char) (baud>>8);
	UBRRL = (unsigned char)baud;
	/*Enable transmitter*/
	UCSRB = (1<<TXEN);
	/*Set frame format: 8data, 1stop bit*/
	UCSRC = (3<<UCSZ0);
}

int Printchar(char c)
{
	while(!(UCSRA & (1<<UDRE)))
	;
	
	UDR=c;
	return 0;
}

void Printstring(char *s)
{
	while(*s)
	{
		Printchar(*s);
		s++;
	}
}


int main(void)
{
	uint8_t i=5;		//variable to send
	char s[7];
	uint16_t j=1234;
	
	//We used 8mhz x-tal but the uController divided it by 8 so fosc = 1 Mhz
	//in our setting UBRR = 12 => baudrate (bps) = 4800.
	USART_Init(12);

	
	// output pin
	DDRB |= (1 << PB0);		//LED
	
	Printchar(i+'0');		//we can easily send one number with +'0'
	Printstring("\r\n");	//newline
	
	//utoa for unsigned and itoa for signed integer
	Printstring(utoa(j,s,10));	// 10 for radix -> decimal system
	Printstring("\r\n");
	
	while(1)
	{
		
		Printstring("Hello Jager\r\n");
		_delay_ms(1000);
		
	}
}
