#include "batteryState.h"

float voltage;
int mappedVoltage;

void batteryADCInit(){
	ADMUX |= (1 << REFS0); //AVCC
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescaler, enable ADC
}

uint16_t batteryADCRead(uint8_t channel) {
	// Select ADC channel
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	// Start ADC conversion
	ADCSRA |= (1 << ADSC);
	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));
	// Return the 10-bit ADC result
	return ADC;
}

int map(float x, float in_min, float in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void batteryADC() {
	float batteryValue = batteryADCRead(3);
	voltage = (batteryValue * 5)/1024; // V = (adcReading * Vref)/(10 bit)
	
	// Define the minimum and maximum voltage values
    float minVoltage = 3.0;  // Replace with your actual minimum voltage
    float maxVoltage = 4.9;  // Replace with your actual maximum voltage

    // Map the voltage to the range 0 to 100
    int mappedValue = map(voltage, minVoltage, maxVoltage, 0, 100);
	mappedVoltage = mappedValue;
}