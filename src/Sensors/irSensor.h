#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <avr/io.h>
void initIRModule();
uint16_t adc_read(uint8_t adc_channel);
void updatedIRDetection();
uint8_t getRightIR();
uint8_t getLeftIR();
#endif 

