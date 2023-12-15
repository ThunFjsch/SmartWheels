/*
 * GccApplication5.c
 *
 * Created: 15/12/2023 20:25:58
 * Author : omar.salem
 */ 

// irsensor.h

#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <avr/io.h>

#define LEFT_IR_PIN PD6
#define RIGHT_IR_PIN PD7

extern const int threshold;
extern uint8_t leftIRState;
extern uint8_t rightIRState;

void initIRModule(uint8_t leftPin, uint8_t rightPin);
uint16_t adc_read(uint8_t adc_channel);
void updatedIRDetection();

#endif 


