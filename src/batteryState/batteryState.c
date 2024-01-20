#include "batteryState.h"

int voltage;

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

void batteryADC() {
	int batteryValue = batteryADCRead(3);
	voltage = (batteryValue * 5)/1023; // V = (adcReading * Vref)/(10 bit)
}