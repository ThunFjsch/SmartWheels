/*
 * GccApplication6.c
 *
 * Created: 15/12/2023 20:44:00
 * Author : omar.salem
 */ 

// main.c

#include "irsensor.h"
#include <util/delay.h>

int main(void) {
	initIRModule(LEFT_IR_PIN, RIGHT_IR_PIN);

	while (1) {
		// Update IR sensor readings
		updatedIRDetection();

		// Check sensor readings
		uint8_t leftSensor = leftIRState;
		uint8_t rightSensor = rightIRState;

		_delay_ms(50);
	}

	return 0;
}


