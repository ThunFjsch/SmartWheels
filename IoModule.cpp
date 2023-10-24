#include "IoModule.h"

// U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8 (U8X8_PIN_NONE); //pin used A4 (SDA) and A5 (SCL)
U8G2_SSD1306_128X64_NONAME_1_HW_I2C oledDisplay(U8G2_R0);// [page buffer, size = 128 B]

enum time {
  HOURS,
  MINUTES,
  SECONDS
};

// Array of the digits used in the speedometer
#define lengthSpeedometerDigits 10
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

void initIOModule(){
  oledDisplay.setColorIndex(1);
  oledDisplay.setFont(u8g2_font_freedoomr10_tu);
  oledDisplay.begin(); // begin oledDisplay library
  oledDisplay.setBitmapMode(1);
}

void modeHighlight(int stateHighlight){
  switch (stateHighlight) { // switching modes with highlighting
    case 0:
      oledDisplay.drawXBMP( 0,  35,  21, 29, highlightModeBits);
      break;
    case 1:
      oledDisplay.drawXBMP( 21,  35,  21, 29, highlightModeBits);
      break;
    case 2:
      oledDisplay.drawXBMP( 43,  35,  21, 29, highlightModeBits);
      break;
    default:
      oledDisplay.drawXBMP( 0,  35,  21, 29, highlightModeBits);
      break;
    }
}

int getSpeedStringLength(int speed, char speed_string[10]){
  int base = 10;
  itoa(speed, speed_string, base); //integer converted into char base of 10
  return strlen(speed_string); // Computes the length of the string str up to
}

void drawSpeed(int speed){
  // drawing speed_string, subtracting the decimal value of 48 (char value of 0)
  // x coordinate is calculated so that it stays centered (center value - number of digits * (half the pixels of individual digits) ) + width of the character (+2 for spacing)*i
  char speed_string[10];
  for(int i = 0; i < getSpeedStringLength(speed, speed_string); i++) {
    oledDisplay.drawXBMP((97 - getSpeedStringLength(speed, speed_string) * 8) + 18*i, 15, 16, 28, speedometerDigits[speed_string[i] - 48]);
  }
}

void drawStaticElements(){
  oledDisplay.drawXBMP( 23,  51,  18, 11, automaticBits);
  oledDisplay.drawXBMP( 23,  37,  16, 12, automaticIconBits);
  oledDisplay.drawXBMP( 14,  6,  36, 18, batteryBits);  // TODO: change this to a dynamic way of displaying the battery state
  oledDisplay.drawXBMP( 89,  45,  15, 6, kmhBits);
  oledDisplay.drawXBMP( 2,  51,  16, 11, remoteControlModeBits);
  oledDisplay.drawXBMP( 2,  38,  16, 21, remoteControlModeIconBits);
  oledDisplay.drawXBMP( 45,  51,  18, 11, slaveModeBits);
  oledDisplay.drawXBMP( 45,  37,  17, 13, slaveModeIconBits);
  oledDisplay.drawXBMP( 106, 45, 16, 16, arrowDownBits);
  oledDisplay.drawXBMP( 72, 45, 16, 16, arrowUpBits);
  oledDisplay.drawXBMP( 89, 52, 7, 9, leftArrowBits);
  oledDisplay.drawXBMP( 97, 52, 7, 9, rightArrowBits);
}

void drawDirections(bool directionForwBack, int directionLeftRight){
  if(directionForwBack){
    oledDisplay.drawXBMP( 74, 47, 12, 13, arrowUpHighlightBits);
  }else{
    oledDisplay.drawXBMP( 108, 46, 12, 13, arrowDownHighlightBits);
  }
      
  if(directionLeftRight = 1){
    oledDisplay.drawXBMP( 91, 53, 4, 7, leftArrowHighlightBits);
  }
  else if(directionLeftRight = 2){
    oledDisplay.drawXBMP( 98, 53, 4, 7, rightArrowHighlightBits);
  }
}

void drawDisplay(int state, int speed, bool directionForwBack, int directionLeftRight, int hours, int minutes, int seconds){
  oledDisplay.firstPage();
  do {
    drawSpeed(speed);
    modeHighlight(state);
    // TODO: add the functionality to display the correct battery state
    drawDirections(directionForwBack, directionLeftRight);
    
    // Display the Time
    // Char array for the time being showed on the display
    char timeString[9];
    sprintf_P(timeString, PSTR("%2d:%02d:%02d"), hours, minutes, seconds);  
    // Draw the timeString
    oledDisplay.drawStr(73, 12, timeString);
    // Drawing the other non-animated elements
    drawStaticElements();
  }while (oledDisplay.nextPage());
}

/* ============================ Test Function ===========================*/

void testBitmaps() {
  // dummy variables
  int testingDelay = 0;
  int testingState = 0;
  int testHighlightModeState = 0;
  int testBatteryBarState = 0;
  int testArrowHighlight = 0;
  int speed = 0;

  unsigned long testPreviousMillis = 0;
  const long testInterval = 100;  // Interval in milliseconds (adjust as needed)

  oledDisplay.firstPage();
  do {
    for(int i = 0; i < getSpeedStringLength(speed); i++){
      /* drawing speed_string, subtracting the decimal value of 48 (char value of 0)
      x coordinate is calculated so that it stays centered (center value - number of digits * (half the pixels of individual digits) ) + width of the character (+2 for spacing)*i
      */
      char speed_string[10];
      oledDisplay.drawXBMP((97 - getSpeedStringLength(speed, speed_string) * 8) + 18*i, 15, 16, 28, speedometerDigits[speed_string[i] - 48]);
    }
    unsigned long testCurrentMillis = millis();  // Get the current time
    // Check if the specified testInterval has passed
    if(testCurrentMillis - testPreviousMillis >= testInterval){
      testPreviousMillis = testCurrentMillis;  // Save the current time
      // Increment testingDelay in each iteration
      testingDelay++;
      // Check if testingDelay exceeds 25
      if(testingDelay > 20){
      testingDelay = 0; // Reset testingDelay
        testHighlightModeState++;
        testBatteryBarState++;
        testArrowHighlight++;
      }
    }
    switch(testHighlightModeState){
      case 0:
        oledDisplay.drawXBMP( 0,  35,  21, 29, highlightModeBits);
        break;
      case 1:
        oledDisplay.drawXBMP( 21,  35,  21, 29, highlightModeBits);
        break;
      case 2:
        oledDisplay.drawXBMP( 43,  35,  21, 29, highlightModeBits);
        break;
      case 3:
        testHighlightModeState = 0;
        break;
    }
    switch(testBatteryBarState){
      case 0:
        oledDisplay.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
        oledDisplay.drawXBMP( 24,  9,  6, 12, batteryStatusBits);
        oledDisplay.drawXBMP( 31,  9,  6, 12, batteryStatusBits);
        oledDisplay.drawXBMP( 38,  9,  6, 12, batteryStatusBits);
        break;
      case 1:
        oledDisplay.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
        oledDisplay.drawXBMP( 24,  9,  6, 12, batteryStatusBits);
        oledDisplay.drawXBMP( 31,  9,  6, 12, batteryStatusBits);
        break;
      case 2:
        oledDisplay.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
        oledDisplay.drawXBMP( 24,  9,  6, 12, batteryStatusBits);
        break;
      case 3:
        oledDisplay.drawXBMP( 17,  9,  6, 12, batteryStatusBits);
        break;
      case 4:
        testBatteryBarState = 0;
        break;
    }
    switch(testArrowHighlight){
      case 0:
        oledDisplay.drawXBMP( 74, 47, 12, 13, arrowUpHighlightBits);
        oledDisplay.drawXBMP( 98, 53, 4, 7, rightArrowHighlightBits);
        break;
      case 1:
        oledDisplay.drawXBMP( 108, 46, 12, 13, arrowDownHighlightBits);
        oledDisplay.drawXBMP( 91, 53, 4, 7, leftArrowHighlightBits);
        break;
      case 2:
        testArrowHighlight = 0;
        break;
    }
    // Drawing the other non-animated elements
    drawStaticElements();

    speed++;
    if(speed < 254){
      speed = 0;
    }
  }while(oledDisplay.nextPage());
}