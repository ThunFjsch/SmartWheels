#include "OLEDScreen.h"

// U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8 (U8X8_PIN_NONE); //pin used A4 (SDA) and A5 (SCL)
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);// [page buffer, size = 128 B]

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
const unsigned long saveInterval = 1000; // Save data every 1 seconds (in milliseconds)

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
/*int button2 = 5;
int buttonUp = 4;   Debugging buttons
int buttonDown = 3;*/
int stateBattery = 0;
int stateHighlight = 0;
int oldHighlight = 0;
int oldBattery = 0;

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

bool directionIO;

int readInt(int address) {
  return word(EEPROM.read(address), EEPROM.read(address + 1));
}

void setDirection(bool newDirection) {
  directionIO = newDirection;
}

void initIOModule(int _modeSwitchButton, bool initDirection) {
  modeSwitchButton = _modeSwitchButton;
  setDirection(initDirection);
  u8g2.setColorIndex(1);
  u8g2.setFont(u8g2_font_freedoomr10_tu);
  u8g2.begin(); // begin u8g2 library
  u8g2.setBitmapMode(1);
  pinMode(modeSwitchButton, INPUT_PULLUP);
  // pinMode(A0, INPUT); Potentiometer, maybe for debug
  /* pinMode(button2, INPUT_PULLUP); // Other buttons for Debug
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP); */
  // Start at the saved time values
  hours = readInt(Hours);
  minutes = readInt(Minutes);
  seconds = readInt(Seconds);
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
  // Check if1000ms, 1 second, has been elapsed
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
    /* printing for debugging
    Serial.print("Saved Usage Time: ");
    Serial.print(savedHours);
    Serial.print(" hours, ");
    Serial.print(savedMinutes);
    Serial.print(" minutes, ");
    Serial.print(savedSeconds);
    Serial.println(" seconds");*/
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
/* 
void batteryStatus() {
  if(digitalRead(button2) == LOW) { // Temporary button switching battery
    Serial.print("switch\n");
    delay(100);
    stateBattery = oldBattery + 1;
    delay(100);
  }

  switch (stateBattery) { // switching battery percentages
    case 1:
      u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
      oldBattery = stateBattery;
      break;
    case 2:
      u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
      u8g2.drawXBMP( 23,  9,  6, 12, batteryStatusBits);
      oldBattery = stateBattery;
      break;
    case 3:
      u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
      u8g2.drawXBMP( 23,  9,  6, 12, batteryStatusBits);
      u8g2.drawXBMP( 29,  9,  6, 12, batteryStatusBits);
      oldBattery = stateBattery;
      break;
    case 4:
      u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
      u8g2.drawXBMP( 23,  9,  6, 12, batteryStatusBits);
      u8g2.drawXBMP( 29,  9,  6, 12, batteryStatusBits);
      u8g2.drawXBMP( 35,  9,  6, 12, batteryStatusBits);
      oldBattery = 0;
      break;
    default:
      u8g2.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
      oldBattery = stateBattery + 1;
      break;
  }
}
*/

void arrowUp() {
  // Arrow Up Higlight
  u8g2.drawXBMP( 74, 47, 12, 13, arrowUpHighlightBits);
}

void arrowDown() {
  // Arrow Down Highlight
  u8g2.drawXBMP( 108, 46, 12, 13, arrowDownHighlightBits);
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
      // batteryStatus();

      if(directionIO){
        arrowUp();
      }else{
        arrowDown();
      }
       
      // Display the Time
      sprintf_P(timeString, PSTR("%2d:%02d:%02d"), readInt(Hours), readInt(Minutes), readInt(Seconds));  
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
  }while (u8g2.nextPage()  );
}

