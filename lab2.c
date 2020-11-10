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
// Pierwszy rejestr
void PWM_OC0()
{
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);
}

// Drugi rejestr
void PWM_OC2()
{
	TCCR2 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRD|=(1<<PD7);
}

// PROGRAM MAIN
int main() {
	// Wyjscia programu
	sbi(PORTA,PA0);
	sbi(PORTA,PA1);

	sbi(PORTC,PC0);
	sbi(PORTC,PC1);
	sbi(PORTC,PC2);
	sbi(PORTC,PC3);

	// Inicjacja rejestrow
	PWM_OC0();
	PWM_OC2();

	int br1=12, br2=12;

	while(1){
		// STEROWANIE PIERWSZA DIODA
		if(bit_is_clear(PINA, 1))
			goto a;

	// PIERWSZA ZOLTA DIODA
		// JASNOSC -
		if(bit_is_set(PINC, 1))
		{
			if(br2 > 4)
			{
				br2 -=3;
			}
			_delay_ms(50);
		}

		// JASNOSC +
		if(bit_is_set(PINC, 0))
		{
			if(br2 < 251)
			{
				br2 +=3;
			}
			_delay_ms(50);
		}

		a:
		// STEROWANIE DRUGA DIODA
		if(bit_is_clear(PINA, 0))
			goto b;

	// DRUGA CZERWONA DIODA
		// JASNOSC -
		if(bit_is_set(PINC, 3))
		{
			if(br1 > 4)
			{
				br1 -=3;
			}
			_delay_ms(50);
		}

		// JASNOSC +
		if(bit_is_set(PINC, 2))
		{
			if(br1 < 251)
			{
				br1 +=3;
			}
			_delay_ms(50);
		}

		b:
		OCR0 = br1;
		OCR2 = br2;
	}
}
