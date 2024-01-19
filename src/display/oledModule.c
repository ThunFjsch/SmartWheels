#include "oledModule.h"
#include <string.h>
#define SSD1306_ADDR  0x78 // address select 8-bit 0x78

u8g2_t u8g2;

int voltage;

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

void batteryADCInit(){
	ADMUX |= (1 << REFS0); //AVCC
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescaler, enable ADC
}

uint16_t batteryADCRead(uint8_t channel) {
	    // Select ADC channel
	    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	    // Start ADC conversion
	    ADCSRA |= (1 << ADSC);
	    // Wait for conversion to complete
	    while (ADCSRA & (1 << ADSC));
	    // Return the 10-bit ADC result
	    return ADC;
}

void batteryADC() {
	int batteryValue = batteryADCRead(3);
	voltage = (batteryValue * 5)/1024; // V = (adcReading * Vref)/(10 bit)
}

void initIOModule(){
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_avr_hw_i2c, u8x8_avr_delay);
	u8g2_SetI2CAddress(&u8g2, SSD1306_ADDR);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFontRefHeightText(&u8g2);
	u8g2_SetFontPosTop(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_freedoomr10_tu);
	u8g2_SendBuffer(&u8g2);
}

void modeHighlight(int stateHighlight){
	switch (stateHighlight) { // switching modes with highlighting
		case 0:
		u8g2_DrawXBMP(&u8g2, 0,  35,  21, 29, highlightModeBits);
		break;
		case 1:
		u8g2_DrawXBMP(&u8g2, 21,  35,  21, 29, highlightModeBits);
		break;
		case 2:
		u8g2_DrawXBMP(&u8g2, 43,  35,  21, 29, highlightModeBits);
		break;
		default:
		u8g2_DrawXBMP(&u8g2, 0,  35,  21, 29, highlightModeBits);
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
		u8g2_DrawXBMP(&u8g2, (97 - getSpeedStringLength(speed, speed_string) * 8) + 18*i, 15, 16, 28, speedometerDigits[speed_string[i] - 48]);
	}
}



void drawStaticElements(){
	u8g2_DrawXBMP(&u8g2, 23,  51,  18, 11, automaticBits);
	u8g2_DrawXBMP(&u8g2, 23,  37,  16, 12, automaticIconBits);
	u8g2_DrawXBMP(&u8g2, 14,  6,  36, 18, batteryBits);  // TODO: change this to a dynamic way of displaying the battery state
	u8g2_DrawXBMP(&u8g2, 89,  45,  15, 6, kmhBits);
	u8g2_DrawXBMP(&u8g2, 2,  52,  16, 11, remoteControlModeBits);
	u8g2_DrawXBMP(&u8g2, 2,  38,  16, 21, remoteControlModeIconBits);
	u8g2_DrawXBMP(&u8g2, 45,  51,  18, 11, slaveModeBits);
	u8g2_DrawXBMP(&u8g2, 45,  37,  17, 13, slaveModeIconBits);
	u8g2_DrawXBMP(&u8g2, 106, 45, 16, 16, arrowDownBits);
	u8g2_DrawXBMP(&u8g2, 72, 45, 16, 16, arrowUpBits);
	u8g2_DrawXBMP(&u8g2, 89, 52, 7, 9, leftArrowBits);
	u8g2_DrawXBMP(&u8g2, 97, 52, 7, 9, rightArrowBits);
}

void drawDirections(bool directionForwBack, int directionLeftRight){
	if(directionForwBack){
		u8g2_DrawXBMP(&u8g2, 74, 47, 12, 13, arrowUpHighlightBits);
		}else{
		u8g2_DrawXBMP(&u8g2, 108, 46, 12, 13, arrowDownHighlightBits);
	}
	if((directionLeftRight = 1)){
		u8g2_DrawXBMP(&u8g2, 91, 53, 4, 7, leftArrowHighlightBits);
	}else if((directionLeftRight = 2)){
		u8g2_DrawXBMP(&u8g2, 98, 53, 4, 7, rightArrowHighlightBits);
	}
}


void drawDisplay(int state, int speed, bool directionForwBack, int directionLeftRight, int hours, int minutes, int seconds){
	u8g2_FirstPage(&u8g2);
	do {
		drawSpeed(speed);
		modeHighlight(state);
		// TODO: add the functionality to display the correct battery state
		batteryADC();
		drawDirections(directionForwBack, directionLeftRight);
		// Display the Time
		// Char array for the time being showed on the display
		char timeString[9]; 
		memset(timeString, 0, sizeof(timeString));
		// Format the time string
		snprintf(timeString, sizeof(timeString), "%2d:%02d:%02d", hours, minutes, seconds);
		// Draw the timeString using u8g2_DrawStr (adjust coordinates as needed)
		u8g2_DrawStr(&u8g2, 69, 3, timeString);
		// Drawing the other non-animated elements
		drawStaticElements();
	}while (u8g2_NextPage(&u8g2));
}





