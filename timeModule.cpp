#include <Arduino.h>
#include <EEPROM.h>

enum addresses {
  Hours = 0,
  Minutes = 2,
  Seconds = 4
};

// Variables to store the time
int hours = 0;
int minutes = 0;
int seconds = 0;

// Int is enough to store the elapsed time
int elapsedTimeUpdateMillis = 0;
unsigned long previousTimeUpdateMillis = 0;
float percentageOfSecondElapsed = 0;

// time function
unsigned long lastSaveTime = 0; // Variable to store the last time data was saved
const unsigned long saveInterval = 45000; // Save data every 45 seconds (in milliseconds)

int readInt(int address){
  return word(EEPROM.read(address), EEPROM.read(address + 1));
}

void initTimeModule(){
  hours = readInt(Hours);
  minutes = readInt(Minutes);
  seconds = readInt(Seconds);
}

int getCarTime(){
  int allTimeValues[2];
  allTimeValues[0] = hours;
  allTimeValues[1] = minutes;
  allTimeValues[2] = seconds;
  return allTimeValues;
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
    // substract these on the "last time". So the next second will be updated 200ms earlier.
    // This reduces the amount of time drift.
    previousTimeUpdateMillis = currentMillis - (elapsedTimeUpdateMillis - 1000);
  }
}

// Splits bit writing in to 2, with highbyte and lowbyte, effectively stores 16-bit integer across 2 EEPROM adresses.
void writeToEepromMemory(int address, int value){ 
  EEPROM.write(address, highByte(value)); // highByte(value) extracts the most significant byte of an int variable.
  EEPROM.write(address + 1, lowByte(value)); // lowByte(value) extracts the least significant byte of an int variable.
}

void saveCarTime(){
  unsigned long currentTime = millis();
  if(currentTime - lastSaveTime >= saveInterval){
    if(hours > readInt(Hours) || minutes > readInt(Minutes) || seconds > readInt(Seconds)){
      // Update the usage time in EEPROM
      writeToEepromMemory(Hours, hours);
      writeToEepromMemory(Minutes, minutes);
      writeToEepromMemory(Seconds, seconds);
      Serial.println("System time updated in EEPROM");
    }
    lastSaveTime = currentTime;
  }
}