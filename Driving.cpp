#include "SonarModule.h"
#include "IRModule.h"
#include "MotorModule.h"

enum turnDirections = {
    forward,
    left, 
    right
}

int directionTurn = 0;

// TODO: make speed change proportional to the 
void correctRangeChange(int speed, int speedChange){
    if(toFarOrTooClose()){
        setAllMotorSpeed(speed - speedChange);
    } else{
        setAllMotorSpeed(speed + speedChange);
    }
    directionTurn = 0;  // TODO: Check if there is a edge case of switching the turn indication in taking turns
}

int getDrivingDirection(){
    return directionTurn = 0;
}

void lineSteeringBehaviour(){
    // TODO: implement the logic for the steering according to the line changes
}

void isOnLine(){
    if(GetFrontIR() || GetLeftIR() || GetRightIR()){
        return true;
    } else {
        return false;
    }
}

void turnLeft(int leftMotorSpeed){
    steerLeftSimple(speed);
    directionTurn = 1;
}

void turnRight(int rightMotorSpeed){
    steerRightSimple(speed);
    directionTurn = 2;
}

void forwardDrive(int speed){
    setAllMotorSpeed(speed);
}