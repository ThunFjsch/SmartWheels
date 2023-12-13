#ifndef oledModule_H
#define  oledModule_H
#include <u8g2.h>
#include <u8x8_avr.h>
#include <stdbool.h>

/* =============================== Initialize ================================= */
void initIOModule();
/* =============================== Non-animated Icons ================================= */
void drawStaticElements();
/* =============================== Animated Icons ================================= */
void modeHighlight();
int getSpeedStringLength(int speed, char speed_string[10]);
void drawSpeed(int speed);
void drawDirections(bool directionForwBack, int directionLeftRight);
void drawDisplay(int state, int speed, bool directionForwBack, int directionLeftRight);
/* =============================== Testing Functions ================================= */
void testBitmaps();
/* =============================== Bitmaps ================================= */
#define  automaticBits_width 18
#define  automaticBits_height 11
const unsigned char  automaticBits[] PROGMEM  = {
	0x1C, 0xFF, 0x01, 0x3E, 0xFF, 0x01, 0x63, 0x38, 0x00, 0x63, 0x38, 0x00,
	0x63, 0x38, 0x00, 0x7F, 0x38, 0x00, 0x7F, 0x38, 0x00, 0x7F, 0x38, 0x00,
0x63, 0x38, 0x00, 0x63, 0x38, 0x00, 0x63, 0x38, 0x00, };
#define  automaticIconBits_width 16
#define  automaticIconBits_height 12
const unsigned char automaticIconBits[] PROGMEM = {
	0x3F, 0x00, 0x48, 0x00, 0x88, 0x00, 0x48, 0x01, 0x3F, 0x01, 0x00, 0x82,
	0x00, 0x82, 0x60, 0xA2, 0x90, 0xAA, 0x97, 0xAA, 0x60, 0xA0, 0x00, 0x80,
};
#define  batteryBits_width 36
#define  batteryBits_height 18
const unsigned char  batteryBits[] PROGMEM  = {
	0xFC, 0xFF, 0xFF, 0x7F, 0x00, 0xFC, 0xFF, 0xFF, 0x7F, 0x00, 0x03, 0x00,
	0x00, 0x80, 0x03, 0x03, 0x00, 0x00, 0x80, 0x03, 0x03, 0x00, 0x00, 0x80,
	0x03, 0x03, 0x00, 0x00, 0x80, 0x03, 0x03, 0x00, 0x00, 0x80, 0x0F, 0x03,
	0x00, 0x00, 0x80, 0x0F, 0x03, 0x00, 0x00, 0x80, 0x0F, 0x03, 0x00, 0x00,
	0x80, 0x0F, 0x03, 0x00, 0x00, 0x80, 0x0F, 0x03, 0x00, 0x00, 0x80, 0x0F,
	0x03, 0x00, 0x00, 0x80, 0x03, 0x03, 0x00, 0x00, 0x80, 0x03, 0x03, 0x00,
	0x00, 0x80, 0x03, 0x03, 0x00, 0x00, 0x80, 0x03, 0xFC, 0xFF, 0xFF, 0x7F,
	0x00, 0xFC, 0xFF, 0xFF, 0x7F, 0x00, };
#define  highlightModeBits_width 21
#define  highlightModeBits_height 29
const unsigned char  highlightModeBits[] PROGMEM  = {
	0xFC, 0xFF, 0x07, 0x02, 0x00, 0x08, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10,
	0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10,
	0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10,
	0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10,
	0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10,
	0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10,
	0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x01, 0x00, 0x10, 0x02, 0x00, 0x08,
	0xFC, 0xFF, 0x07, };
#define  kmhBits_width 15
#define  kmhBits_height 6
const unsigned char  kmhBits[] PROGMEM  = {
	0x29, 0x4A, 0x65, 0x4B, 0xA3, 0x7A, 0x25, 0x4A, 0x29, 0x4A, 0x29, 0x4A,
};
#define  remoteControlModeBits_width 16
#define  remoteControlModeBits_height 11
const unsigned char remoteControlModeBits[] PROGMEM = {
	0x1F, 0x38, 0x3F, 0x7C, 0x63, 0xC6, 0x63, 0xC6, 0x3F, 0x06, 0x7F, 0x06,
	0x63, 0x06, 0x63, 0x86, 0x63, 0xC6, 0x63, 0x7C, 0x63, 0x78,
};
#define  remoteControlModeIconBits_width 16
#define  remoteControlModeIconBits_height 21
const unsigned char  remoteControlModeIconBits[] PROGMEM  = {
	0x38, 0x1C, 0xC4, 0x23, 0x02, 0x40, 0x49, 0x92, 0x15, 0xA8, 0x09, 0x90,
	0xE1, 0x87, 0x11, 0x88, 0x09, 0x90, 0x09, 0x90, 0x06, 0x60, 0x00, 0x00,
	0x00, 0x00, };
#define  slaveModeBits_width 18
#define  slaveModeBits_height 11
const unsigned char  slaveModeBits[] PROGMEM  = {
	0x7F, 0x83, 0x01, 0x7F, 0x83, 0x01, 0x03, 0xEF, 0x01, 0x03, 0xFF, 0x01,
	0x7F, 0xBB, 0x01, 0x7F, 0x93, 0x01, 0x60, 0x83, 0x01, 0x60, 0x83, 0x01,
	0x60, 0x83, 0x01, 0x7F, 0x83, 0x01, 0x7F, 0x83, 0x01, };
#define  slaveModeIconBits_width 17
#define  slaveModeIconBits_height 13
const unsigned char  slaveModeIconBits[] PROGMEM  = {
	0xF0, 0x1F, 0x00, 0x08, 0x20, 0x00, 0x04, 0x40, 0x00, 0x04, 0x40, 0x00,
	0xFE, 0xFF, 0x00, 0x22, 0x88, 0x00, 0x1D, 0x71, 0x01, 0x01, 0x00, 0x01,
	0xC1, 0x07, 0x01, 0x41, 0x04, 0x01, 0xFE, 0xFF, 0x00, 0x24, 0x48, 0x00,
0x18, 0x30, 0x00, };
#define  batteryStatusBits_width 6
#define  batteryStatusBits_height 12
const unsigned char  batteryStatusBits[] PROGMEM  = {
	0x00, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x00,
};
#define arrowDownHighlightBits_width 12
#define arrowDownHighlightBits_height 13
const unsigned char arrowDownHighlightBits[] PROGMEM = {
	0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00,
	0xF0, 0x00, 0xFF, 0x0F, 0xFE, 0x07, 0xFC, 0x03, 0xF8, 0x01, 0xF0, 0x00,
0x60, 0x00, };
#define arrowDownBits_width 16
#define arrowDownBits_height 16
const unsigned char arrowDownBits[] PROGMEM =  {
	0xE0, 0x07, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04,
	0x20, 0x04, 0x3F, 0xFC, 0x03, 0xC0, 0x06, 0x60, 0x0C, 0x30, 0x18, 0x18,
0x30, 0x0C, 0x60, 0x06, 0xC0, 0x03, 0x80, 0x01, };
#define arrowUpHighlightBits_width 12
#define arrowUpHighlightBits_height 13
const unsigned char arrowUpHighlightBits[] PROGMEM =  {
	0x60, 0x00, 0xF0, 0x00, 0xF8, 0x01, 0xFC, 0x03, 0xFE, 0x07, 0xFF, 0x0F,
	0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00,
0xF0, 0x00, };
#define arrowUpBits_width 16
#define arrowUpBits_height 16
const unsigned char arrowUpBits[] PROGMEM =  {
	0x80, 0x01, 0xC0, 0x03, 0x60, 0x06, 0x30, 0x0C, 0x18, 0x18, 0x0C, 0x30,
	0x06, 0x60, 0x03, 0xC0, 0x3F, 0xFC, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04,
	0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0xE0, 0x07, };
#define leftArrow_width 7
#define leftArrow_height 9
const unsigned char leftArrowBits[] PROGMEM = {
	0x70, 0x58, 0x4C, 0x46, 0x43, 0x46, 0x4C, 0x58, 0x70, };
#define leftArrowHighlight_width 4
#define leftArrowHighlight_height 7
const unsigned char leftArrowHighlightBits[] PROGMEM = {
	0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08, };
#define rightArrow_width 7
#define rightArrow_height 9
const unsigned char rightArrowBits[] PROGMEM = {
	0x07, 0x0D, 0x19, 0x31, 0x61, 0x31, 0x19, 0x0D, 0x07, };
#define rightArrowHighlight_width 4
#define rightArrowHighlight_height 7
const unsigned char rightArrowHighlightBits[] PROGMEM = {
	0x01, 0x03, 0x07, 0x0F, 0x07, 0x03, 0x01, };
#define  digit_0_width 16
#define  digit_0_height 28
const unsigned char  digit_0_bits[] PROGMEM  = {
	0xF0, 0xFF, 0xF8, 0xFF, 0xFC, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC,
	0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC,
	0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x3F, 0xFF, 0x1F, };
#define  digit_1_width 16
#define  digit_1_height 28
const unsigned char digit_1_bits[] PROGMEM  = {
	0x80, 0x1F, 0xC0, 0x1F, 0xE0, 0x1F, 0xF0, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F,
	0xF8, 0x1F, 0xF0, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F,
	0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F,
	0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F,
	0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, };
#define  digit_2_width 16
#define  digit_2_height 28
const unsigned char digit_2_bits[] PROGMEM  = {
	0xF0, 0x7F, 0xF8, 0xFF, 0xFC, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x3F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFE, 0x00, 0xFE, 0x00, 0xFE, 0x00, 0xFF,
	0x80, 0x7F, 0xE0, 0x3F, 0xF0, 0x1F, 0xF8, 0x0F, 0xFC, 0x03, 0xFE, 0x01,
	0xFF, 0x00, 0x7F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
#define  digit_3_width 16
#define  digit_3_height 28
const unsigned char digit_3_bits[] PROGMEM  = {
	0xF0, 0xFF, 0xF8, 0xFF, 0xFC, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFF,
	0x00, 0x7F, 0x00, 0x1F, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFC,
	0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x3F, 0xFF, 0x1F, };
#define  digit_4_width 16
#define  digit_4_height 28
const unsigned char digit_4_bits[] PROGMEM  = {
	0x00, 0x0E, 0x00, 0x1E, 0x00, 0x3F, 0x00, 0x7F, 0x80, 0xFF, 0x80, 0xFF,
	0xC0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFD, 0xF8, 0xFD,
	0xF8, 0xFC, 0xFC, 0xFC, 0x7C, 0xFC, 0x7E, 0xFC, 0x3E, 0xFC, 0x3F, 0xFC,
	0xFF, 0xFF, 0xFE, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xF8, 0xFF, 0x00, 0xFC,
	0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, };
#define  digit_5_width 16
#define  digit_5_height 28
const unsigned char digit_5_bits[] PROGMEM  = {
	0xFE, 0x3F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F,
	0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x7F, 0x00, 0xFF, 0x0F,
	0xFF, 0x1F, 0xFF, 0x3F, 0xFF, 0x7F, 0xFF, 0xFF, 0x00, 0xFE, 0x00, 0xFE,
	0x00, 0xFE, 0x1F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFE, 0xFF, 0xFF,
0xFF, 0xFF, 0xFE, 0xFF, 0xFC, 0xFF, 0xF8, 0xFF, };
#define  digit_6_width 16
#define  digit_6_height 28
const unsigned char digit_6_bits[] PROGMEM  = {
	0xF0, 0x7F, 0xF8, 0x7F, 0xFC, 0x7F, 0xFE, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F,
	0x3F, 0x7C, 0x3F, 0x7C, 0x3F, 0x7C, 0x3F, 0x00, 0x3F, 0x00, 0xFF, 0x7F,
	0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x3F, 0x7E,
	0x3F, 0x7E, 0x3F, 0x7E, 0x3F, 0x7E, 0x3F, 0x7E, 0x3F, 0x7E, 0xFF, 0x7F,
0xFF, 0x7F, 0xFF, 0x3F, 0xFF, 0x1F, 0xFF, 0x0F, };
#define  digit_7_width 16
#define  digit_7_height 28
const unsigned char digit_7_bits[] PROGMEM  = {
	0xFF, 0x0F, 0xFF, 0x1F, 0xFF, 0x3F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
	0x1F, 0xFC, 0x1F, 0x7E, 0x1F, 0x7E, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x3F,
	0x80, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0xC0, 0x0F, 0xC0, 0x0F, 0xE0, 0x0F,
	0xE0, 0x07, 0xE0, 0x07, 0xF0, 0x07, 0xF0, 0x03, 0xF0, 0x03, 0xF8, 0x01,
	0xF8, 0x01, 0xFC, 0x01, 0xFC, 0x00, 0xFC, 0x00, };
#define  digit_8_width 16
#define  digit_8_height 28
const unsigned char digit_8_bits[] PROGMEM  = {
	0xF0, 0x7F, 0xF8, 0xFF, 0xFC, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0x7C,
	0xFF, 0x3F, 0xFF, 0x1F, 0xF8, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC,
	0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0x3F, 0xFC, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x3F, 0xFF, 0x1F, };
#define  digit_9_width 16
#define  digit_9_height 28
const unsigned char digit_9_bits[] PROGMEM  = {
	0xF0, 0x7F, 0xF8, 0xFF, 0xFC, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x3F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFE, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFE,
	0x00, 0xFE, 0x1F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFE, 0xFF, 0xFF,
	0xFF, 0x7F, 0xFF, 0x3F, 0xFF, 0x1F, 0xFF, 0x0F, };
#endif