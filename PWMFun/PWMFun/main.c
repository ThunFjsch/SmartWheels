/*
 * PWMFun.c
 *
 * Created: 28/11/2023 13:47:59
 * Author : ThunFisch
 */ 
#define F_CPU (160000000L)

#include <avr/io.h>
#include <util/delay.h>
#include "interrupt/interrupt.h"

// initial time values
uint32_t previousmillis = 0;
uint32_t currentmillis = 0;
uint32_t interval = 100;

// GLobal variable for the ADC conversion result
volatile uint16_t val=0;

ISR(ADC_vect){
	val=ADC;
}

int main(void)
{
	DDRB = 0b00111111;
	ADMUX = (1<<REFS0);
	ADCSRA = 0b11111111;
	ADCSRB = 0;
	sei();
	
	while(1){
		if(val < 146) {PORTB = 0b00000000;}
		else if(val<293) {PORTB = 0b00000001;}
		else if(val<439){PORTB = 0b00000011;}
		else if(val<585){PORTB = 0b00000111;}
		else if(val<731){PORTB = 0b00001111;}
		else if(val<878){PORTB = 0b00011111;}
		else{PORTB = 0b00111111;}
	}
		// Time setup
		//millis_init();
		//sei();	// Allow the interrupt
	
    /*DDRB=0b00111111;
		
		TCCR1A |= (1<<WGM11);
		TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
		ICR1 = 4999;
		
		TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<COM1B0);
		
		OCR1A = 1500;
		OCR1B = 1500;
		
		uint32_t cnt = 0;
		while (1){
			_delay_ms(1);
			cnt++;
			
			if(cnt > 4999){
				OCR1A = cnt;
				OCR1B = cnt;
			}
    }*/
		
}

