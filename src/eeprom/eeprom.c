/*	ATMEGA328P, it has 1Kbyte of data EEPROM memory.
 *	It is organized in a separate data space, in which single bytes can be read and written.
 *	100,000 erase/write cycle.
 *	Can access from I/O space.
 *	Don't let it drop below 2.7v when writing so to now corrupt the data.
 *
 *	EEPROM address register: EEARH (high) and EEARL (low)
 *	0-1023 bytes = 10 bit address
 *	EEDR = Data register
 *	EECR = control register
 *	EEMPE = master write enable
 *	EEPE = write enable
 *	EERE = read enable
 */

#include "eeprom.h"
#include "../time/timeInterrupt.h"


enum addresses {
	Hours = 95,
	Minutes = 96,
	Seconds = 97
};

// Variables to store the time
int hours = 0;
int minutes = 0;
int seconds = 0;

// Int is enough to store the elapsed time
int elapsedTimeUpdateMillis = 0;
unsigned long previousTimeUpdateMillis = 0;
float percentageOfSecondElapsed = 0;

uint32_t lastSaveTime = 0;
uint16_t saveInterval = 45000;


uint8_t eepromRead(uint16_t uiAddress, int *data){
	if(uiAddress > eepromSize){ // if our address is out of scope, it will return an invalid error
		return eepromInvalidAddress;
	}
	// Wait for completion of previous write
	while(EECR & (1<<EEPE));
	// Load our address that we want to read, 2 8-bit registers (which makes 16 bit wide address)
	EEARH = (uiAddress & 0xFF00) >> 8; // filter out the upper half of the address
	EEARL = (uiAddress & 0x00FF);
	// Start eeprom read by writing EERE 
	EECR |= (1<<EERE);
	// Return data from Data Register 
	*data = EEDR;
	return eepromOk;
}

uint8_t eepromWrite(uint16_t uiAddress, int ucData){
	if(uiAddress > eepromSize){ // if our address is out of scope, it will return an invalid error
		return eepromInvalidAddress;
	}
	// Wait for completion of previous write 
	while(EECR & (1<<EEPE));
	// Set up address and Data Registers 
	EEARH = (uiAddress & 0xFF00) >> 8; // write to high address, filter out the upper half of the address (highByte)
	EEARL = (uiAddress & 0x00FF); // write to low address 
	EEDR = ucData;
	// Write logical one to EEMPE (enable master write)
	EECR |= (1<<EEMPE);
	// Start eeprom write by setting EEPE 
	EECR |= (1<<EEPE);
	return eepromOk;
}

uint8_t eepromUpdate(uint16_t uiAddress, int ucData){
	uint8_t error = eepromOk;
	if(uiAddress > eepromSize){ // if our address is out of scope, it will return an invalid error
		return eepromInvalidAddress;
	}
	uint8_t value = 0;
	
	// reducing the write cycle to the EEPROM by checking
	error = eepromRead(uiAddress, &value);
	if (error != eepromOk){
		return error;
	}
	if (value == ucData){
		return eepromOk;
	}
	
	error = eepromWrite(uiAddress, ucData);
	if (error != eepromOk){
		return error;
	}
	
	// Checking if the data actually wrote to the EEPROM
	error = eepromRead(uiAddress, &value);
	if (error != eepromOk){
		return error;
	}
	if (value != ucData){
		return eepromWriteFail;
	}
	return eepromOk;
}

void initTimeModule(){
	hours = eepromRead(Hours, &hours);
	minutes = eepromRead(Minutes, &minutes);
	seconds = eepromRead(Seconds, &seconds);
}

void updateCarTime(unsigned long currentMillis){
	elapsedTimeUpdateMillis = currentMillis - previousTimeUpdateMillis;
	// Check if a minutes has been elapsed
	if(seconds > 59){
		seconds = 0;
		minutes++;
	}
	// Check if an hour has been elapsed
	if(minutes > 59){
		minutes = 0;
		hours++;
	}
	// Check if a day has been elapsed
	if(hours > 12){
		hours = 1;
	}
	// increment seconds every 1000ms
	if(elapsedTimeUpdateMillis > 1000){
		seconds++;
		// It might be possible that more than 1000ms has been elapsed e.g. 1200ms
		// Then there are already 200ms elapsed of the next second. We need to
		// subtract these on the "last time". So the next second will be updated 200ms earlier.
		// This reduces the amount of time drift.
		previousTimeUpdateMillis = currentMillis - (elapsedTimeUpdateMillis - 1000);
	}
}

void saveCarTime(){
	unsigned long currentTime = millis();
	if(currentTime - lastSaveTime >= saveInterval){
		// Read the current stored time from EEPROM
		int storedHours, storedMinutes, storedSeconds;
		eepromRead(Hours, &storedHours);
		eepromRead(Minutes, &storedMinutes);
		eepromRead(Seconds, &storedSeconds);
		
		// Check if the current time is different from the stored time
		if(hours != storedHours || minutes != storedMinutes || seconds != storedSeconds){
			// Update the stored time in EEPROM
			eepromWrite(Hours, hours);
			eepromWrite(Minutes, minutes);
			eepromWrite(Seconds, seconds);
		}
		lastSaveTime = currentTime;
	}
}


int getHours() {
	return hours;
}

int getMinutes() {
	return minutes;
}

int getSeconds() {
	return seconds;
}