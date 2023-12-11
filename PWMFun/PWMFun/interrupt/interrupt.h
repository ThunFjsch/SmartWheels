#ifndef IRModule_H
#define IRModule_H

#include <avr/interrupt.h>

void millis_init(void);
ISR(TIMER0_COMPA_vect);
uint32_t millis(void);

#endif