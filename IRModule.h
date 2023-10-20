#ifndef IRModule_H
#define IRModule_H
#include <Arduino.h>

void initIRModule(int _IRFront, int _IRLeft, int _IRRight);
void updatedIRDetection();
bool GetFrontIR();
bool GetLeftIR();
bool GetRightIR();
void TestingIRDetectionAccuracy();
void IRDebug();

#endif