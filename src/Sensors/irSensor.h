#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <avr/io.h>
void initIRModule(uint8_t leftPin, uint8_t rightPin);
uint16_t adc_read(uint8_t adc_channel);
void updatedIRDetection();

#endif 

