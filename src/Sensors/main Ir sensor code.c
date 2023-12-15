/*
 * GccApplication4.c
 *
 * Created: 01/12/2023 13:20:28
 * Author : omar.salem
 */ 

#include <avr/io.h>
#include <util/delay.h>

// IR sensor pins
#define LEFT_IR_PIN PD6
#define RIGHT_IR_PIN PD7

// Threshold for IR sensor readings
const int threshold = 500;

// Variables to store IR sensor states
uint8_t leftIRState = 0;
uint8_t rightIRState = 0;

void initIRModule(uint8_t leftPin, uint8_t rightPin) {
	// Set IR sensor pins as inputs
	DDRC &= ~(1 << leftPin);
	DDRC &= ~(1 << rightPin);
}

uint16_t adc_read(uint8_t adc_channel) {
	// Select ADC channel
	ADMUX = (1 << REFS0) | adc_channel;
	// Start conversion
	ADCSRA |= (1 << ADSC);
	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC))
	;
	// Return the ADC result
	return ADC;
}

void updatedIRDetection() {
	// Read analog values from IR sensors
	int leftSensorValue = adc_read(LEFT_IR_PIN);
	int rightSensorValue = adc_read(RIGHT_IR_PIN);

	// Set digital IR states based on the threshold
	leftIRState = (leftSensorValue > threshold) ? 1 : 0;
	rightIRState = (rightSensorValue > threshold) ? 1 : 0;
}

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

