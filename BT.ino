#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
int ledpin=13;

void setup()
{
  mySerial.begin(9600);
  pinMode(ledpin,OUTPUT);
}

void loop()
{
int input;
  
  if (mySerial.available())
  {
    input = mySerial.read();
    Serial.println("DATA RECEIVED:");
    switch(input)
     {
        case '0':
              Serial.println("mode ++");
              break;
        case '1':
              Serial.println("left");
              break;
        case '2':
              Serial.println("forward");
              break;
        case '3':
              Serial.println("right");
              break;
        case '4':
              Serial.println("reverse");
              break;
        case '5':
              Serial.println("reset movement");
              break;
    }
  }
}
