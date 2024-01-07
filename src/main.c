#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "bluetooth/bt.h"
#include "time/timeInterrupt.h"
#pragma "display/oledModule.h"

// State controle
enum States {
	AutonomousState = 0,
	FollowerState = 1,
	BluetoothState = 2
};
int currentState = 2;
bool directionForwBack = true; // Forward is true. Backward is false
int directionTurn = 0; // 0 straight 1 left 2 right
int state = 0;
int speed = 0;
bool debug = false;

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
	//bluetooth variables
	unsigned char data = "";
	unsigned char ch   = "";
	// Display Setup
	initIOModule();
	// Time setup
	millis_init();
	// Module Setup
	initMotorModule(false);
	
	//bluetooth setup
	UART_Setup();
/*	UART_TxChar(ch);*/

	DDRD |= ~(1<<DDD2);	// Button mode switch
	PORTD |= (1<<PORTD2); // Pull-up resistor for button

	sei();	// Allow the interrupt
	DDRB |= (1<<DDB5);

  while(1){
		currentmillis = millis();
		currentDebounce = millis();
		drawDisplay(currentState, speed, directionForwBack, directionTurn);


		data = USART_Receive();//in current state of code it is unclear if this works, they way bluetooth is set up works in other projects but for an unknown reason not here
		
		
		// just for testing
	//	steerLeftSimple(200);
		
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
