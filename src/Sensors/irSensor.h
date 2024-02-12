#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <avr/io.h>
#include <stdbool.h>
bool direction_;
bool leftDirection_;
bool rightDirection_;

void initIrPins(void);
int irSensorRead(int sensor_select);
int readSensor(int sensorLeft, int sensorRight);

#endif 

