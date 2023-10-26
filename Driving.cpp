#include "SonarModule.h"
#include "IRModule.h"
#include "MotorModule.h"

#define hardStop 10
#define rangeMin 18
#define rangeMax 24
#define speedChange 40
#define speedChangePerInterval 5

enum turnDirections {
  forward,
  left, 
  right
};

int directionTurnDriving = forward;
int drivingSpeed = 0;
int previousSpeed;

void turnLeft(int leftMotorSpeed){
    steerLeftSimple(leftMotorSpeed);
    directionTurnDriving = left;
}

void turnRight(int rightMotorSpeed){
    steerRightSimple(rightMotorSpeed);
    directionTurnDriving = right;
}

void forwardDrive(int speed){
    drivingSpeed = speed;
    setAllMotorSpeed(speed);
}

// TODO: make speed change proportional to the 
void correctRangeChange(int speed){
    if(toFarOrTooClose(rangeMin, rangeMax)){
        forwardDrive(speed - speedChange);
    } else{
        forwardDrive(speed + speedChange);
    }
    directionTurnDriving = forward;  // TODO: Check if there is a edge case of switching the turn indication in taking turns
}

void collisionAvoidanceSpeedControl(int speed){
    if(isSomethingFront(rangeMin)){
        forwardDrive(speed - speedChange);
    }
    else if(isSomethingFront(hardStop)){
        stopMotors();
    }
    else if(previousSpeed == speed){
        forwardDrive(speed + speedChange);
    }
    else{
        forwardDrive(speed);
    }
}

int getDrivingDirection(){
    return directionTurnDriving;
}

int getDrivingSpeed(){
    return drivingSpeed;
}

void lineSteeringBehaviour(int speed){
    if(GetFrontIR() && !GetLeftIR() && !GetRightIR()){
        setAllMotorSpeed(speed);
    }
    else if(GetFrontIR() && GetLeftIR() && GetRightIR()){
        setAllMotorSpeed(speed);
    }
    else if(GetFrontIR() && GetLeftIR() && !GetRightIR()){
        complexSteering(speed + speedChange, speed);
    }
    else if(GetFrontIR() && !GetLeftIR() && GetRightIR()){
        complexSteering(speed, speed + speedChange);
    }
    else if(!GetFrontIR() && GetLeftIR() && !GetRightIR()){
        turnLeft(speed);
    }
    else if(!GetFrontIR() && !GetLeftIR() && GetRightIR()){
        turnRight(speed);
    }
}

void isOnLine(){
    if(GetFrontIR() || GetLeftIR() || GetRightIR()){
        return true;
    } else {
        return false;
    }
}