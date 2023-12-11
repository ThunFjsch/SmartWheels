#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "time/timeInterrupt.h"

// State controle
enum States {
		AutonomousState = 0,
		FollowerState = 1,
		BluetoothState = 2
};
int currentState = 2;

// initial time values
uint32_t previousmillis = 0;
uint32_t currentmillis = 0;
uint32_t interval = 100;

// Button debounce
uint32_t previousDebounce = 0;
uint32_t currentDebounce = 0;
uint32_t debounceInterval = 400;

int main(void){
	// Time setup
	millis_init();
	// Module Setup
	initMotorModule(false);

	DDRD |= ~(1<<DDD2);	// Button mode switch

	sei();	// Allow the interrupt
	
  while(1){
		currentmillis = millis();
		currentDebounce = millis();
		
		steerLeftSimple(200);
		
 		//State change selection via button
		if(!(PIND & (1<<PIND2)) && (currentDebounce - previousDebounce) >= debounceInterval){
			previousDebounce = currentDebounce;
			currentState++;
			if(currentState == 3){
				currentState = 1;
			}
		}
		
	}
}
