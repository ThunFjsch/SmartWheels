#ifndef BT_H_
#define BT_H_

bool direction_;
bool leftDirection_;
bool rightDirection_;

void initUART();
void sendChar(char c);
char receiveChar();
void turnOnLED();
void turnOffLED();
void processControllerInput(char data);
#endif /* BT_H_ */