#include <avr/io.h>
#include <stdbool.h>
#include "bt.h"

// Function to initialize UART for communication with HC-06
void initUART() {
	// Set baud rate to 9600 (assuming 16 MHz clock)
	UBRR0H = (uint8_t)(0x00);
	UBRR0L = (uint8_t)(103);

	// Enable transmitter and receiver
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);

	// Set frame format: 8 data bits, no parity, 1 stop bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to send a character via UART
void sendChar(char c) {
	// Wait until the transmit buffer is empty
	while (!(UCSR0A & (1 << UDRE0))) {}

	// Put the character in the buffer, sends the character
	UDR0 = c;
}

// Function to receive a character via UART
char receiveChar() {
	// Wait until data is received
	while (!(UCSR0A & (1 << RXC0))) {}

	// Return the received character
	return UDR0;
}

void turnOnLED() {
	// Set PORTB, Pin 0 as output
	DDRB |= (1 << DDB1);

	// Turn on the LED on PORTB, Pin 0
	PORTB |= (1 << PORTB1);
}

// Function to turn off the LED on PORTB
void turnOffLED() {
	// Turn off the LED on PORTB, Pin 0
	PORTB &= ~(1 << PORTB1);
}

void processControllerInput(char data) {
    switch (data) {
        case 'F':
            // Move forward
            direction_ = true;
            setMotorDirection(direction_);
			setAllMotorSpeed(240);
			sendChar('G');
            break;
        case 'B':
            // Move backward
            direction_ = false;
            setMotorDirection(direction_);
			setAllMotorSpeed(240);
			sendChar('B');
            break;
        case 'L':
            // Turn left
			leftDirection_ = false;
			rightDirection_ = true;
			setIndividualDirection(leftDirection_, rightDirection_);
			setRightMotorSpeed(255);
			setLeftMotorSpeed(255);
			sendChar('L');
            break;
        case 'R':
            // Turn right
			leftDirection_ = true;
			rightDirection_ = false;
			setIndividualDirection(leftDirection_, rightDirection_);
			setRightMotorSpeed(255);
			setLeftMotorSpeed(255);
			sendChar('R');
            break;
        case 'S':
            // Stop
            stopMotors();
            break;
		default:
			// Handle unknown command
			// (You can add more handling here if needed)
			sendChar('F');
			break;
    }
}

