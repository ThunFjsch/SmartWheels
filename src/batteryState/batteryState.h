#ifndef batteryState_H
#define batteryState_H
#include <avr/io.h>

extern int voltage;

void batteryADCInit();
uint16_t batteryADCRead(uint8_t channel);
void batteryADC();

#endif