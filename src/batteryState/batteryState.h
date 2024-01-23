#ifndef batteryState_H
#define batteryState_H
#include <avr/io.h>

extern int mappedVoltage;

void batteryADCInit();
uint16_t batteryADCRead(uint8_t channel);
int map(float x, float in_min, float in_max, int out_min, int out_max);
void batteryADC();

#endif