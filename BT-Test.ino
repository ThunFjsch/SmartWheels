#include <SoftwareSerial.h>             // library for bluetooth chip
SoftwareSerial mySerial(0,1);           // initializing digital pin 0 & 1 ( 0 = TXD / Transmittor),(1 = RXD / Receiver )
int ledpin=13;
void setup()
{
mySerial.begin(9600);                   // Selecting the baud rate ( standard for BT chip is 9600 )
Serial.begin(9600);
pinMode(ledpin,OUTPUT);
}
void loop()
{
int i;                                  // int i is the user input from the bluetooth chip
 
if (mySerial.available())
{
  switch(i){
                                        // case 0-2 changes the driving modes
    case 0: Manual();
            break;
    case 1: autonomous();
            break;
    case 2: slave();
            break;
                                        // case 3-6 is basic movement ( it's possible to add the blinker function in with left & right but we need to discuss )
    case 3: Forward();
            break;
    case 4: Reverse();
            break;
    case 5: Right();
            break;
    case 6: Left();
            break;

 
      
  }


  /*                                        // test part of the software (easy for setup when it stops working for some reason)
i=mySerial.read();
Serial.println("DATA RECEIVED:");
Serial.print(i);
if(i=='1')
{
digitalWrite(ledpin,1);
Serial.println("led on");

}
if(i=='0')
{
digitalWrite(ledpin,0);
Serial.println("led off");
}*/
}
}
