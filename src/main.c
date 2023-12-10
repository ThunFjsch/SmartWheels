#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "time/timeInterrupt.h"
#include "motors/MotorModule.h"

/* Pin Definitions*/
// TODO: change arduino GPIO to register location
// OLED module
#define serialDataOLED A4  // these aren't used in the codebase but are the default pins for the OLED library
#define serialClockOLED A5 // These pins are utilized in line 4 in the OLEDScreen.cpp

// Bluetooth module
#define txdBT 13
#define rxdBT 12

// Smaller things
#define indicatorRight A2
#define indicatorLeft A1
#define buzzer A3
#define modeSwitchButton A3
#define batteryRead 1

//Sonar module
#define trigPin 7
#define echoPinRight 6
#define echoPinCenter 5
#define echoPinLeft 4

// IR module
#define outOneIR 3
#define outTwoIR 2

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
	initMotorModule(true);
	// Time setup
	millis_init();
	sei();	// Allow the interrupt
	
	DDRB |= (1<<DDB5);
	DDRD |= (1<<DDD7);
	
	DDRD |= ~(1<<DDD2);	// Button mode switch
	
	
	
  /* Replace with your application code */
  while(1){
		currentmillis = millis();
		currentDebounce = millis();
		
		if((currentmillis - previousmillis) >= interval){
			previousmillis = currentmillis;
			//PORTB ^= (1<<DDB5);
		}
		
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
