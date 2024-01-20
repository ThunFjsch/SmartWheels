#ifndef batteryState_H
#define batteryState_H
#include <avr/io.h>

extern int mappedVoltage;

void batteryADCInit();
uint16_t batteryADCRead(uint8_t channel);
int map(int x, int in_min, int in_max, int out_min, int out_max);
void batteryADC();

#endif