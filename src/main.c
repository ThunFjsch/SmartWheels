#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "bluetooth/bt.h"
#include "time/timeInterrupt.h"
#pragma "display/oledModule.h"
#include "eeprom/eeprom.h"
#include "batteryState/batteryState.h"

// State control
enum States {
	AutonomousState = 0,
	FollowerState = 1,
	BluetoothState = 2
};
int currentState = 2;
int voltages = 1;
bool directionForwBack = true; // Forward is true. Backward is false
int directionTurn = 0; // 0 straight 1 left 2 right
int state = 0;
int speed = 0;
bool debug = false;
char data;

// initial time values
uint32_t previousmillis = 0;
uint32_t currentmillis = 0;
uint32_t interval = 100;

// Button debounce
uint32_t previousDebounce = 0;
uint32_t currentDebounce = 0;
uint32_t debounceInterval = 400;


int main(void)
{
	initUART();
	// Display Setup
	initIOModule();
	batteryADCInit();
	
	// Time setup
	millis_init();
	// Motor Module Setup
	initMotorModule(false);
	
	DDRD |= ~(1<<DDD2);	// Button mode switch
	PORTD |= (1<<PORTD2); // Pull-up resistor for button


	sei();	// Allow the interrupt

	DDRB |= (1<<DDB5);

  while(1){
    // time
    currentmillis = millis();
		currentDebounce = millis();
    // display
    updateCarTime(currentmillis);
		batteryADC();
		saveCarTime();
		drawDisplay(currentState, speed, directionForwBack, directionTurn);

		switch(currentState){
			case States.AutonomousState:
				// add code
				break;
			case States.FollowerState:
				// add code
				break;
			case States.BluetoothState:
				data = receiveChar();
				processControllerInput(data);
				break;		
		}

		//State change selection via button
		if(!(PIND & (1<<PIND2)) && (currentDebounce - previousDebounce) >= debounceInterval){
			previousDebounce = currentDebounce;
			currentState++;
			if(currentState == 3){
				currentState = 0;
			}
		}
	}
}
