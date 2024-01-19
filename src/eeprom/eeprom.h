#ifndef EEPROM_H
#define EEPROM_H

#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define eepromSize 1023

enum{
	eepromOk,
	eepromWriteFail,
	eepromInvalidAddress
};

uint8_t eepromRead(uint16_t uiAddress, int *data);
uint8_t eepromWrite(uint16_t uiAddress, int ucData);
uint8_t eepromUpdate(uint16_t uiAddress, int ucData);

// Time
void initTimeModule();
void updateCarTime(unsigned long currentMillis);
void writeToEepromMemory(int address, int value);
void saveCarTime();
int getHours();
int getMinutes();
int getSeconds();

#endif