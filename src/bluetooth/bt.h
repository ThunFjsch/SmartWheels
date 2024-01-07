/*
 * bt.h
 *
 * Created: 19/12/2023 11:02:30
 *  Author: Geele Gert
 */ 


#ifndef BT_H_
#define BT_H_

#include <avr/io.h>

/*		establish a connection		*/
void UART_Setup();
unsigned char USART_Receive();
void UART_TxChar(char ch);

/*		receiver function				*/	




#endif /* BT_H_ */