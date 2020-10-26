#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#ifndef _BV
#define _BV(bit)				(1<<(bit))
#endif

#ifndef sbi
#define sbi(reg,bit)		reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)		reg &= ~(_BV(bit))
#endif

//-------------------------------------

int main() {

	DDRA=0x0F;
	PORTA=0xF0;

	while(1){

		sbi(PORTC,0);
		sbi(PORTC,1);

	// PIERWSZA DIODA
		if(bit_is_set(PINC, 0))
		{
			cbi(PORTA, 0);
			_delay_ms(50);
		}
		else
		{
			sbi(PORTA, 0);
			_delay_ms(50);
		}

	// DRUGA DIODA
		if(bit_is_set(PINC, 1))
		{
			cbi(PORTA, 1);
			_delay_ms(50);
		}
		else
		{
			sbi(PORTA, 1);
			_delay_ms(50);
		}

		cbi(PORTC,0);
		cbi(PORTC,1);

	}

}
