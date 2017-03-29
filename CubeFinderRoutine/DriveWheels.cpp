
#include "DriveWheels.h"

//Forward-Backward Functions

//default forward drive
void DriveWheels::driveFwd() {
    servo_LeftMotor->writeMicroseconds(1500 + ui_Motors_Speed);
    servo_RightMotor->writeMicroseconds(1500 + ui_Motors_Speed);
}

//default backward drive
void DriveWheels::driveBkwd() {
    servo_LeftMotor->writeMicroseconds(1500 - ui_Motors_Speed);
    servo_RightMotor->writeMicroseconds(1500 - ui_Motors_Speed);
}

//drive with new speed
void DriveWheels::drive(int new_Motors_Speed) {
    servo_LeftMotor->writeMicroseconds(1500 + new_Motors_Speed);
    servo_RightMotor->writeMicroseconds(1500 + new_Motors_Speed);
}

//drive with new speed for certain time
void DriveWheels::driveTime(int new_Motors_Speed, unsigned long timeMicroseconds) {
    currentMillis = millis();
    previousMillis = millis();
    
    while (currentMillis - previousMillis <= timeMicroseconds) {
        servo_LeftMotor->writeMicroseconds(1500 + new_Motors_Speed);
        servo_RightMotor->writeMicroseconds(1500 + new_Motors_Speed);
        currentMillis = millis();
    }
    noDrive();
}

//drive with new speed for a certain distance
void DriveWheels::driveDist(int motorSpeed, float distInch) {
    int rotNeeded = abs(distInch / disPerRot);
    int beginLeftCount = encoder_LeftMotor->getPosition();
    int tempLeftCount, rotNow;
    
    drive(motorSpeed);
    while (rotNow < rotNeeded) {
        tempLeftCount = encoder_LeftMotor->getPosition();
        rotNow = abs(beginLeftCount - tempLeftCount);
    }
    noDrive();
}


//Basic Control Functions

//stop wheel motors
void DriveWheels::noDrive() {
    servo_LeftMotor->writeMicroseconds(1500 + ci_Left_Motor_Stop);
    servo_RightMotor->writeMicroseconds(1500 + ci_Right_Motor_Stop);
}

//get offset values during setup
void DriveWheels::setupOffset(unsigned int leftOffset, unsigned int rightOffset) {
    ui_Left_Motor_Offset = leftOffset;
    ui_Right_Motor_Offset = rightOffset;
}


//Turning Functions

//turn as per user control
void DriveWheels::turn(int left_Motor_Speed, int right_Motor_Speed) {
    servo_LeftMotor->writeMicroseconds(1500 + left_Motor_Speed);
    servo_RightMotor->writeMicroseconds(1500 + right_Motor_Speed);
}

//turn by degrees
void DriveWheels::turnDeg(int motorSpeed, int degreeTurn){
    //positive degree is counterclockwise
    
    int currentDegree = 0, rotNeeded = (abs(degreeTurn * radToDegree * axleLength)) / disPerRot;
    
    int beginRightCount = encoder_RightMotor->getPosition();
    int beginLeftCount = encoder_LeftMotor->getPosition();
    int tempRightCount, tempLeftCount, curRot;
    
    if (degreeTurn > 0) {
        servo_LeftMotor->writeMicroseconds(1500 - motorSpeed);
        servo_RightMotor->writeMicroseconds(1500 + motorSpeed);
    }
    else if (degreeTurn < 0) {
        servo_LeftMotor->writeMicroseconds(1500 + motorSpeed);
        servo_RightMotor->writeMicroseconds(1500 - motorSpeed);
    }
    
    while (curRot <= rotNeeded) {
        tempRightCount = encoder_RightMotor->getPosition();
        tempLeftCount = encoder_LeftMotor->getPosition();
        curRot = abs(tempRightCount - beginRightCount) + abs(tempLeftCount - beginLeftCount);
    }
    noDrive();
}



