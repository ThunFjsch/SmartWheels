#ifndef timeModule_H
#define  timeModule_H
#include <Arduino.h>
#include <EEPROM.h>

/* =============================== Time System ================================= */
int readInt(int address);
void initTimeModule();
void updateCarTime(unsigned long currentMillis);
void writeToEepromMemory(int address, int value);
void saveCarTime();
int getHours();
int getMinutes();
int getSeconds();
#endif