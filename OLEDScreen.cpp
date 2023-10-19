#include "OLEDScreen.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);// [page buffer, size = 128 B] pin used A4 (SDA) and A5 (SCL)

enum addresses {
  Hours = 0,
  Minutes = 2,
  Seconds = 4
};

enum timeMode {
  MODE_SHOW_TIME = 0,
  MODE_SET_SECONDS = 3,
  MODE_SET_MINUTES = 2,
  MODE_SET_HOURS = 1
};

unsigned long lastSaveTime = 0; // Variable to store the last time data was saved
const unsigned long saveInterval = 45000; // Save data every 45 seconds (in milliseconds)

// Array of the digits used in the speedometer
const int lengthSpeedometerDigits = 10;
const unsigned char* speedometerDigits[lengthSpeedometerDigits] = {
    digit_0_bits,
    digit_1_bits,
    digit_2_bits,
    digit_3_bits,
    digit_4_bits,
    digit_5_bits,
    digit_6_bits,
    digit_7_bits,
    digit_8_bits,
    digit_9_bits
};

// Button/switch integers
int modeSwitchButton; // Mode select button
int stateHighlight = 0;
int oldHighlight = 0;

// Speed intergers
int speed = 0;
char speed_string[10];
int speed_string_lenght;

// Battery integers
int battery = 0;

// Variables to store the time
int hours = 0;
int minutes = 0;
int seconds = 0;

// Char array for the time being showed on the display
char timeString[9];

// Variables to store the time
unsigned long currentMillis = 0;

// Int is enough to store the elapsed time
int elapsedTimeUpdateMillis = 0;
unsigned long previousTimeUpdateMillis = 0;
float percentageOfSecondElapsed = 0;

// Boolean for directions
bool directionForwBack;
bool directionLeftRight;

/* ================= Debugging variables ================ */
int testingDelay = 0;
int testingState = 0;
int testHighlightModeState = 0;
int testBatteryBarState = 0;
int testArrowHighlight = 0;

unsigned long testPreviousMillis = 0;
const long testInterval = 100;  // Interval in milliseconds (adjust as needed)
/* ================= Debugging variables ================ */

int readInt(int address) {
  return word(EEPROM.read(address), EEPROM.read(address + 1));
}

void setForwBackDirection(bool newForwBackDirection) {
  directionForwBack = newForwBackDirection;
}

void setLeftRightDirection(bool newLeftRightDirection){
  directionLeftRight = newLeftRightDirection;
}

void initIOModule(int _modeSwitchButton, bool initForwBackDirection, bool initLeftRightDirection, bool debug) {
  modeSwitchButton = _modeSwitchButton;
  setForwBackDirection(initForwBackDirection);
  setLeftRightDirection(initLeftRightDirection);
  u8g2.setColorIndex(1);
  u8g2.setFont(u8g2_font_freedoomr10_tu);
  u8g2.begin(); // begin u8g2 library
  u8g2.setBitmapMode(1);
  pinMode(modeSwitchButton, INPUT_PULLUP);
  hours = readInt(Hours);
  minutes = readInt(Minutes);
  seconds = readInt(Seconds);
  if(debug = true){
    testBitmaps();
  }
}

void showTime() {
  // Time
  currentMillis = millis();
  // Check ifa minutes has been elapsed
  if(seconds > 59){
    seconds = 0;
    minutes++;
  }
  // Check ifan hour has been elapsed
  if(minutes > 59){
    minutes = 0;
    hours++;
  }
  // Check ifa day has been elapsed
  if(hours > 12){
    hours = 1;
  }
  elapsedTimeUpdateMillis = currentMillis - previousTimeUpdateMillis;
  // Check if 1000ms, 1 second, has been elapsed
  if(elapsedTimeUpdateMillis > 1000) {
    seconds++;
    // It might be possible that more than 1000ms has been elapsed e.g. 1200ms
    // Then there are already 200ms elapsed of the next second. We need to
    // substract these on the "last time". So the next second will be updated 200ms earlier.
    // This reduces the amount of time drift.
    previousTimeUpdateMillis = currentMillis - (elapsedTimeUpdateMillis - 1000);
  }
}

// Splits bit writing in to 2, with highbyte and lowbyte, effectively stores 16-bit integer across 2 EEPROM adresses.
void writeToEepromMemory(int address, int value) { 
  EEPROM.write(address, highByte(value)); // highByte(value) extracts the most significant byte of an int variable.
  EEPROM.write(address + 1, lowByte(value)); // lowByte(value) extracts the least significant byte of an int variable.
}

void timeSave() {
    unsigned long currentTime = millis();
    if(currentTime - lastSaveTime >= saveInterval) {
    Serial.print("Saved Usage Time: "); // Save time debugging
    Serial.print(readInt(Hours));
    Serial.print(" hours, ");
    Serial.print(readInt(Minutes));
    Serial.print(" minutes, ");
    Serial.print(readInt(Seconds));
    Serial.println(" seconds");
    if(hours > readInt(Hours) || minutes > readInt(Minutes) || seconds > readInt(Seconds)) {
      // Update the usage time in EEPROM
      writeToEepromMemory(Hours, hours);
      writeToEepromMemory(Minutes, minutes);
      writeToEepromMemory(Seconds, seconds);
      Serial.println("System time updated in EEPROM");
    }
    lastSaveTime = currentTime;
  }
}

int getState() {
  return stateHighlight;
}

void modeHighlight() {
    if(digitalRead(modeSwitchButton) == LOW) { // Temporary button switching
      Serial.print("switch\n");
      delay(100);
      stateHighlight = oldHighlight + 1;
      delay(100);
    }
    switch (stateHighlight) { // switching modes with highlighting
      case 1:
        u8g2.drawXBMP( 0,  35,  21, 29, highlightModeBits);
        oldHighlight = stateHighlight;
        break;
      case 2:
        u8g2.drawXBMP( 21,  35,  21, 29, highlightModeBits);
        oldHighlight = stateHighlight;
        break;
      case 3:
        u8g2.drawXBMP( 43,  35,  21, 29, highlightModeBits);
        oldHighlight = 0;
        break;
      default:
        u8g2.drawXBMP( 0,  35,  21, 29, highlightModeBits);
        oldHighlight = stateHighlight + 1;
        break;
    }
  
}

void arrowUp() {
  // Arrow Up Higlight
  u8g2.drawXBMP( 74, 47, 12, 13, arrowUpHighlightBits);
}

void arrowDown() {
  // Arrow Down Highlight
  u8g2.drawXBMP( 108, 46, 12, 13, arrowDownHighlightBits);
}

void arrowLeft() {
  // Arrow Left Highlight
  u8g2.drawXBMP( 91, 53, 4, 7, leftArrowHighlightBits);
}

void arrowRight() {
  // Arrow Right Highlight
  u8g2.drawXBMP( 98, 53, 4, 7, rightArrowHighlightBits);
}

void batteryStatus() { // read the battery voltage

}

void drawDisplayBitmaps() {
  // Potentiometer setup for testing the speedometer
  speed = map(analogRead(A0), 0, 1023, 0, 100); // Converting analog readings from 0-1023 to 0-100
  itoa(speed, speed_string, 10); //integer converted into char with the 10 decimal value
  speed_string_lenght = strlen(speed_string); // Computes the length of the string str up to
  u8g2.firstPage();
    do {
      for(int i = 0; i < speed_string_lenght; i++) {
        /* drawing speed_string, subtracting the decimal value of 48 (char value of 0)
        x coordinate is calculated so that it stays centered (center value - number of digits * (half the pixels of individual digits) ) + width of the character (+2 for spacing)*i
        */
        u8g2.drawXBMP((97 - speed_string_lenght * 8) + 18*i, 15, 16, 28, speedometerDigits[speed_string[i] - 48]);
      }
      modeHighlight();
      batteryStatus();

      if(directionForwBack){
        arrowUp();
      }else{
        arrowDown();
      }
      
      if(directionLeftRight){
        arrowLeft();
      }else{
        arrowRight();
      }

      // Display the Time
      sprintf_P(timeString, PSTR("%2d:%02d:%02d"), hours, minutes, seconds);  
      // Draw the timeString
      u8g2.drawStr(73, 12, timeString);
      // Drawing the other non-animated elements
      u8g2.drawXBMP( 23,  51,  18, 11, automaticBits);
      u8g2.drawXBMP( 23,  37,  16, 12, automaticIconBits);
      u8g2.drawXBMP( 14,  6,  36, 18, batteryBits);
      u8g2.drawXBMP( 89,  45,  15, 6, kmhBits);
      u8g2.drawXBMP( 2,  51,  16, 11, remoteControlModeBits);
      u8g2.drawXBMP( 2,  38,  16, 21, remoteControlModeIconBits);
      u8g2.drawXBMP( 45,  51,  18, 11, slaveModeBits);
      u8g2.drawXBMP( 45,  37,  17, 13, slaveModeIconBits);
      u8g2.drawXBMP( 106, 45, 16, 16, arrowDownBits);
      u8g2.drawXBMP( 72, 45, 16, 16, arrowUpBits);
      u8g2.drawXBMP( 89, 52, 7, 9, leftArrowBits);
      u8g2.drawXBMP( 97, 52, 7, 9, rightArrowBits);
  }while (u8g2.nextPage()  );
}


/* ============================ Test Function ===========================*/

void testBitmaps() {
  // put your main code here, to run repeatedly:
  speed = random(0, 100);
  itoa(speed, speed_string, 10);
  speed_string_lenght = strlen(speed_string);
    u8g2.firstPage();
    do {
      for(int i = 0; i < speed_string_lenght; i++) {
        /* drawing speed_string, subtracting the decimal value of 48 (char value of 0)
        x coordinate is calculated so that it stays centered (center value - number of digits * (half the pixels of individual digits) ) + width of the character (+2 for spacing)*i
        */
        u8g2.drawXBMP((97 - speed_string_lenght * 8) + 18*i, 15, 16, 28, speedometerDigits[speed_string[i] - 48]);
      }
      unsigned long testCurrentMillis = millis();  // Get the current time
      // Check if the specified testInterval has passed
      if (testCurrentMillis - testPreviousMillis >= testInterval) {
      testPreviousMillis = testCurrentMillis;  // Save the current time
      // Increment testingDelay in each iteration
      testingDelay++;
      // Check if testingDelay exceeds 25
      if (testingDelay > 20) {
      testingDelay = 0; // Reset testingDelay
        testHighlightModeState++;
        testBatteryBarState++;
        testArrowHighlight++;
      }
      }
      switch (testHighlightModeState) {
          case 0:
            u8g2.drawXBMP( 0,  35,  21, 29, highlightModeBits);
            break;
          case 1:
            u8g2.drawXBMP( 21,  35,  21, 29, highlightModeBits);
            break;
          case 2:
            u8g2.drawXBMP( 43,  35,  21, 29, highlightModeBits);
            break;
          case 3:
            testHighlightModeState = 0;
            break;
        }
      switch (testBatteryBarState) {
        case 0:
          u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
          u8g2.drawXBMP( 24,  9,  6, 12, batteryStatusBits);
          u8g2.drawXBMP( 31,  9,  6, 12, batteryStatusBits);
          u8g2.drawXBMP( 38,  9,  6, 12, batteryStatusBits);
          break;
        case 1:
          u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
          u8g2.drawXBMP( 24,  9,  6, 12, batteryStatusBits);
          u8g2.drawXBMP( 31,  9,  6, 12, batteryStatusBits);
          break;
        case 2:
          u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
          u8g2.drawXBMP( 24,  9,  6, 12, batteryStatusBits);
          break;
        case 3:
          u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
          break;
        case 4:
          testBatteryBarState = 0;
          break;
      }
      switch (testArrowHighlight) {
        case 0:
        u8g2.drawXBMP( 74, 47, 12, 13, arrowUpHighlightBits);
        u8g2.drawXBMP( 98, 53, 4, 7, rightArrowHighlightBits);
        break;
        case 1:
        u8g2.drawXBMP( 108, 46, 12, 13, arrowDownHighlightBits);
        u8g2.drawXBMP( 91, 53, 4, 7, leftArrowHighlightBits);
        break;
        case 2:
        testArrowHighlight = 0;
        break;
      }
      u8g2.drawXBMP( 23,  51,  18, 11, automaticBits);
      u8g2.drawXBMP( 23,  37,  16, 12, automaticIconBits);
      u8g2.drawXBMP( 14,  6,  36, 18, batteryBits);
      u8g2.drawXBMP( 89,  45,  15, 6, kmhBits);
      u8g2.drawXBMP( 2,  51,  16, 11, remoteControlModeBits);
      u8g2.drawXBMP( 2,  38,  16, 21, remoteControlModeIconBits);
      u8g2.drawXBMP( 45,  51,  18, 11, slaveModeBits);
      u8g2.drawXBMP( 45,  37,  17, 13, slaveModeIconBits);
      u8g2.drawXBMP( 106, 45, 16, 16, arrowDownBits);
      u8g2.drawXBMP( 72, 45, 16, 16, arrowUpBits);
      u8g2.drawXBMP( 89, 52, 7, 9, leftArrowBits);
      u8g2.drawXBMP( 97, 52, 7, 9, rightArrowBits);
    }while (u8g2.nextPage()  );
}