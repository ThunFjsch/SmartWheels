 /*
 * bluetooth.c
 *
 * Created: 07/12/2023 13:58:59
 * Author : Geele Gert
 */ 

#include <avr/io.h>

void UART_Setup(){
	//Enable the receive and transmit in USART B
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	
	//Set the data size for communication C
	UCSR0C &= (~(1<<UMSEL00)) & (~(1<UMSEL01)) & (~(1<<UPM00)) & (~(1<<UPM01)) & (~(1<<USBS0));

	//Set the data lenght to be 8bit
	UCSR0B &= (~(1<<UCSZ02));
	UCSR0B |= (1<<UCSZ00) | (1<<UCSZ01); //8bits
	
	//Set the speed of the transmission
	UCSR0A &= (~(1<<U2X0));
	
	//Set the baud rate
	UBRR0 = 103; //9600
	
	/*					Test part   			*/
	//Set port B5&B4 (onboard led) to output
	//DDRB |= (1<<DDB5) | (1<<DDB4);
}

unsigned char USART_Receive(){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void UART_TxChar(char ch){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = ch;
}
// 
// int main(void){
// 	
// 	UART_Setup();
// 	
// 	//Make a variable that holds user input
// 	unsigned char data = "";
// 	
// 	while(1){//Endless while loop
// 	
// 		data = USART_Receive();
// 		
// 		switch(data){
// 			case 'a':
// 				PORTB |= (1<<PB5);
// 				break;
// 			case 'b':
// 				PORTB &= (~(1<<PB5));
// 				PORTB &= (~(1<<PB4));
// 				break;
// 			case 'j':
// 				PORTB |= (1<<PB4);
// 				break;
// 		}
// 	
// 	}
// }
// 
