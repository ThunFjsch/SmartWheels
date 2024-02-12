#include <avr/io.h>
#include <util/delay.h>
#include "irSensor.h"
#define LINE_DETECTED 1
#define LINE_NOT_DETECTED 0
#define LEFT_IR_SENSOR 1
#define RIGHT_IR_SENSOR 2

// Safety pin init function to set the pins to be input
void initIrPins(void){
	PORTC |= (1<<PORTC1) | (1<<PORTC2);
}

// Function to read IR sensor data
int irSensorRead(int sensor_select){ // sensor_select parameter is used to select IR sensor to read from
	// branching to read the corresponding sensor based on the function's input value
	if (sensor_select == LEFT_IR_SENSOR){
		readSensor(PINC1);
	}
	else if (sensor_select == RIGHT_IR_SENSOR){
		readSensor(PINC2);
	}
}

int readSensor(int sensor){
	if (PINC & (1<<sensor)){
		direction_ = true;
        setMotorDirection(direction_);
		setAllMotorSpeed(200);
	}
	else{
		leftDirection_ = false;
		rightDirection_ = true;
		zeroDegreeLeft(200);
	}
}

