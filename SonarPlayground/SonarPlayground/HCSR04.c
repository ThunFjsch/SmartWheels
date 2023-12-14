#include <avr/io.h>
#include <avr/interrupt.h>
#include "HCSR04.h"

volatile uint32_t firstReading = 0;
volatile uint32_t secondReading = 0;
volatile uint32_t dutyCycle = 0;

void HCSR04_init(){
	cli();
	// Fast pwm configuration
	DDRD |= (1<<DDD6);	// PD6 output(triggerpin)
	TCCR0A = (1<<COM0A1)|(1<<COM0A0)|(1<<WGM01)|(1<<WGM00);
	TCCR0B |= (1<<CS01);	// prescaler to 8 for timer 0
	OCR0A = 235;	// 10us trigger pulse, 118us off-time (128us repetition rate)
	
	// Input capture configuration
	// Timer 1 running in normal mode
	DDRB &= ~(1<<DDB0);	// PB0 as input
	TCCR1B = (1<<ICNC1)|(1<<ICES1)|(1<<CS11);	// noise canceling + positive edge detection for input capture and prescaler = 8
	sei();
	TIMSK1 |= (1<<ICIE1);	// enable timer1 input capture interrupt
}

uint32_t getDistance(){
	static uint32_t echoPulseMicroS;
	static uint32_t distanceCM;
	// 32768us = 65536 clock ticks for timer 1 with prescaler 8
	echoPulseMicroS = (float)dutyCycle * 32768/65536;
	distanceCM = echoPulseMicroS * 0.034/2;
	return distanceCM;
}

ISR(TIMER1_COMPA_vect){
	if((TCCR1B & (1<<ICES1)) == (1<<ICES1)){
		firstReading = ICR1;
	} else{
		secondReading = ICR1;
	}
	
	if(firstReading != 0 && secondReading != 0){
		dutyCycle = secondReading - firstReading;
		firstReading = 0;
		secondReading = 0;
	}
	
	TCCR1B ^= (1<<ICES1);	// toggle edge detection bit
	TIFR1 = (1<<ICF1);	// clear input capture flag
}