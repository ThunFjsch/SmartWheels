#include <avr/io.h>
#include <util/delay.h>
#define LeftPinBitMask 0b0001
#define RightPinBitMask 0b0010


// Threshold for IR sensor readings
const int threshold = 500;

// Variables to store IR sensor states
uint8_t leftIRState = 0;
uint8_t rightIRState = 0;

void initIRModule() {
	// Set IR sensor pins as inputs
	DDRC &= ~(1 << DDC1); // PD2
	DDRC &= ~(1 << DDC2); // PD3
}

uint16_t adcRead(uint8_t adc_channel) {
	// Select ADC channel
	ADMUX = (1 << REFS0) | adc_channel;
	// Start conversion
	ADCSRA |= (1 << ADSC);
	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));
	// Return the ADC result
	return ADC;
}

void updatedIRDetection() {
	// Read analog values from IR sensors
	int leftSensorValue = adcRead(LeftPinBitMask);
	int rightSensorValue = adcRead(RightPinBitMask);

	// Set digital IR states based on the threshold
	leftIRState = (leftSensorValue > threshold) ? 1 : 0;
	rightIRState = (rightSensorValue > threshold) ? 1 : 0;
}

uint8_t getRightIR(){
	return rightIRState;
}

uint8_t getLeftIR(){
	return leftIRState;
}

