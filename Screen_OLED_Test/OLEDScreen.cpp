#include "OLEDScreen.h"
#define button1 6
#define button2 5
#define buttonUp 4
#define buttonDown 3
// U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8 (U8X8_PIN_NONE); //pin used A4 (SDA) and A5 (SCL)
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);// [page buffer, size = 128 B]

// Button/switch integers
int stateBattery = 0;
int stateHighlight = 0;
int oldHighlight = 0;
int oldBattery = 0;

// Array of all digit bitmaps for convinience
const int bitmap_allArray_Digit = 10;
const unsigned char* bitmap_allArray[10] = {
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
int address = 0;

unsigned long lastSaveTime = 0; // Variable to store the last time data was saved
const unsigned long saveInterval = 1000; // Save data every 1 seconds (in milliseconds)

int readInt(int address) {
  return word(EEPROM.read(address), EEPROM.read(address + 1));
}

const int MODE_SHOW_TIME = 0;
const int MODE_SET_SECONDS = 3;
const int MODE_SET_MINUTES = 2;
const int MODE_SET_HOURS = 1;


// Char array for the time being showed on the display
char timeString[9];

// Variables to store the time
unsigned long currentMillis = 0;

// Int is enough to store the elapsed time
int elapsedTimeUpdateMillis = 0;
unsigned long previousTimeUpdateMillis = 0;
float percentageOfSecondElapsed = 0;

int currentMode = MODE_SHOW_TIME;

void initIOModule() {
  u8g2.setColorIndex(1);
  u8g2.setFont(u8g2_font_freedoomr10_tu);
  u8g2.begin(); // begin u8g2 library
  u8g2.setBitmapMode(1);
  pinMode(A0, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  Serial.begin(9600);

  // Start at the saved time values
  int savedHours = readInt(address);
  hours = savedHours;
  int savedMinutes = readInt(address + 2);
  minutes = savedMinutes;
  int savedSeconds = readInt(address + 4);
  seconds = savedSeconds;
}


void showTime() {
    // Time
    currentMillis = millis();
    checkTime();
    if (currentMode == MODE_SHOW_TIME) {
        increaseSeconds();
    } else {
        previousTimeUpdateMillis = currentMillis;
    }
}

void checkTime() {
    // Check if a minutes has been elapsed
    if (seconds > 59) {
        seconds = 0;
        minutes++;
    }
    // Check if an hour has been elapsed
    if (minutes > 59) {
        minutes = 0;
        hours++;
    }
    // Check if a day has been elapsed
    if (hours > 12) {
        hours = 1;
    }
}

void increaseSeconds() {
    elapsedTimeUpdateMillis = currentMillis - previousTimeUpdateMillis;
    // Check if 1000ms, 1 second, has been elapsed
    if (elapsedTimeUpdateMillis > 1000) {
      seconds++;
      // It might be possible that more than 1000ms has been elapsed e.g. 1200ms
      // Then there are already 200ms elapsed of the next second. We need to
      // substract these on the "last time". So the next second will be updated 200ms earlier.
      // This reduces the amount of time drift.
      previousTimeUpdateMillis = currentMillis - (elapsedTimeUpdateMillis - 1000);
    }
}

void writeInt(int address, int value) {
  EEPROM.write(address, highByte(value));
  EEPROM.write(address + 1, lowByte(value));
}

void timeSave() {
    unsigned long currentTime = millis();
  if (currentTime - lastSaveTime >= saveInterval) {
    int savedHours = readInt(address);
    int savedMinutes = readInt(address + 2);
    int savedSeconds = readInt(address + 4);
    /* printing for debugging
    Serial.print("Saved Usage Time: ");
    Serial.print(savedHours);
    Serial.print(" hours, ");
    Serial.print(savedMinutes);
    Serial.print(" minutes, ");
    Serial.print(savedSeconds);
    Serial.println(" seconds");*/
    if (hours > savedHours || minutes > savedMinutes || seconds > savedSeconds) {
      // Update the usage time in EEPROM
      writeInt(address, hours);
      writeInt(address + 2, minutes);
      writeInt(address + 4, seconds);
      Serial.println("System time updated in EEPROM");
    }
     lastSaveTime = currentTime;
  }
}

void modeHighlight() {
    if (digitalRead(button1) == LOW) { // Temporary button switching
      Serial.print("switch\n");
      delay(100);
      stateHighlight = oldHighlight + 1;
      delay(100);
    }

    switch (stateHighlight) { // switching modes with highlighting
      case 1:
        u8g2.drawXBMP( 0,  35,  21, 29, highlight_bits);
        oldHighlight = stateHighlight;
        break;
      case 2:
        u8g2.drawXBMP( 21,  35,  21, 29, highlight_bits);
        oldHighlight = stateHighlight;
        break;
      case 3:
        u8g2.drawXBMP( 43,  35,  21, 29, highlight_bits);
        oldHighlight = 0;
        break;
      default:
        u8g2.drawXBMP( 0,  35,  21, 29, highlight_bits);
        oldHighlight = stateHighlight + 1;
        break;
    }
}

void batteryStatus() {
  if (digitalRead(button2) == LOW) { // Temporary button switching battery
    Serial.print("switch\n");
    delay(100);
    stateBattery = oldBattery + 1;
    delay(100);
  }

  switch (stateBattery) { // switching battery percentages
    case 1:
      u8g2.drawXBMP( 17,  9,  6, 12, status_battery_bits);
      oldBattery = stateBattery;
      break;
    case 2:
      u8g2.drawXBMP( 17,  9,  6, 12, status_battery_bits);
      u8g2.drawXBMP( 23,  9,  6, 12, status_battery_bits);
      oldBattery = stateBattery;
      break;
    case 3:
      u8g2.drawXBMP( 17,  9,  6, 12, status_battery_bits);
      u8g2.drawXBMP( 23,  9,  6, 12, status_battery_bits);
      u8g2.drawXBMP( 29,  9,  6, 12, status_battery_bits);
      oldBattery = stateBattery;
      break;
    case 4:
      u8g2.drawXBMP( 17,  9,  6, 12, status_battery_bits);
      u8g2.drawXBMP( 23,  9,  6, 12, status_battery_bits);
      u8g2.drawXBMP( 29,  9,  6, 12, status_battery_bits);
      u8g2.drawXBMP( 35,  9,  6, 12, status_battery_bits);
      oldBattery = 0;
      break;
    default:
      u8g2.drawXBMP( 17,  9,  6, 12, status_battery_bits);
      oldBattery = stateBattery + 1;
      break;
  }
}

void arrowUp() {
  // Arrow Up Higlight
  if (digitalRead(buttonUp) == LOW) {
    u8g2.drawXBMP( 74, 47, 12, 13, arrow_up_highlight_bits);
  }
}

void arrowDown() {
  // Arrow Down Highlight
  if (digitalRead(buttonDown) == LOW) {
    u8g2.drawXBMP( 108, 46, 12, 13, arrow_down_highlight_bits);
  }
}

void elements() {
    speed = map(analogRead(A0), 0, 1023, 0, 100); // Converting analog readings from 0-1023 to 0-100
    itoa(speed, speed_string, 10); //integer converted into char with the 10 decimal value
    speed_string_lenght = strlen(speed_string); // Computes the length of the string str up to

    int savedHours = readInt(address);
    int savedMinutes = readInt(address + 2);
    int savedSeconds = readInt(address + 4);

    u8g2.firstPage();
    do {
        for (int i = 0; i < speed_string_lenght; i++) {
            u8g2.drawXBMP((97 - speed_string_lenght * 8) + 18*i, 15, 16, 28, bitmap_allArray[speed_string[i] - 48]);
            /* drawing speed_string, subtracting the decimal value of 48 (char value of 0)
      x coordinate is calculated so that it stays centered (center value - number of digits * (half the pixels of individual digits) ) + width of the character (+2 for spacing)*i
      */
        }
        modeHighlight();
        batteryStatus();
        arrowUp();
        arrowDown();
        // Drawing Time
        if (currentMode != MODE_SHOW_TIME) {
            u8g2.drawTriangle((currentMode - 1) * 43 + 5, 0, currentMode * 43 - 5, 0, (currentMode - 1) * 43 + 21, 5);
        }
        sprintf_P(timeString, PSTR("%2d:%02d:%02d"), savedHours, savedMinutes, savedSeconds);
        // Draw the timeString
        u8g2.drawStr(73, 12, timeString);

        // Drawing the other non-animated elements
        u8g2.drawXBMP( 23,  51,  18, 11, AT_bits);
        u8g2.drawXBMP( 23,  37,  16, 12, AT_icon_bits);
        u8g2.drawXBMP( 14,  6,  36, 18, battery_bits);
        u8g2.drawXBMP( 89,  45,  15, 6, KMH_bits);
        u8g2.drawXBMP( 2,  51,  16, 11, RC_bits);
        u8g2.drawXBMP( 2,  38,  16, 21, RC_Icon_bits);
        u8g2.drawXBMP( 45,  51,  18, 11, SM_bits);
        u8g2.drawXBMP( 45,  37,  17, 13, SM_Icon_bits);
        u8g2.drawXBMP( 106, 45, 16, 16, arrow_down_bits);
        u8g2.drawXBMP( 72, 45, 16, 16, arrow_up_bits);

    } while (u8g2.nextPage()  );

}

