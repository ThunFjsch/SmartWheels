#ifndef IRModule_H
#define IRModule_H
#include <Arduino.h>

void initIRModule(bool _IRFront, bool _IRLeft, bool _IRRight);
void updatedIRDetection();
bool GetFrontIR();
bool GetLeftIR();
bool GetRightIR();
void TestingIRDetectionAccuracy();
void IRDebug();

#endif