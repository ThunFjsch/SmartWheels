#include <avr/interrupt.h>

// time in ms
volatile uint32_t ms = 0;

void millis_init(void){
	ms = 0;
	
	// Configure Timer/counter 0 to generate an interrupt every millisecond
	// T_events = T_CPU * N * (TOP + 1)
	//					= 1/16 MHz * 64 * (249 +1)
	//					= 1
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS01) | (1<<CS00);
	OCR0A = 249;
	// Timer/Counter0 Output compare match a interrupt enable
	TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect){
	ms++;
}

uint32_t millis(void){
	/* ms is a 32-bit variable (uint32_t). This means that multiple accesses
	are needed to read or write the value of ms. There is a chance that
	in the middle of these multiple accesses, the ms value is written due to
	the ISR being triggered. In order to make sure the value of ms is not
	updated when reading it, disable interrupts while reading the value.*/
	cli();
	uint32_t ret = ms;
	sei();
	
	return ret;
}