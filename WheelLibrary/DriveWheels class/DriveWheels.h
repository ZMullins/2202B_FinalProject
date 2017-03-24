#include <Servo.h>
#include <EEPROM.h>
#include <Wire.h>
#include "I2CEncoder.h"



class DriveWheels {
public:
    DriveWheels(Servo servo_RightMotor, Servo servo_LeftMotor, I2CEncoder* encoder_RightMotor, I2CEncoder* encoder_LefttMotor);
    
public:
    Servo* servo_RightMotor;
    Servo* servo_LeftMotor;
    I2CEncoder* encoder_RightMotor;
    I2CEncoder* encoder_LeftMotor;
    
    const int ci_Left_Motor_Stop = 0;
    const int ci_Right_Motor_Stop = 0;
    unsigned int ui_Motors_Speed = 300;
    unsigned int ui_Left_Motor_Offset;
    unsigned int ui_Right_Motor_Offset;
    
    const float axleLength = 10.0; //inches
    const float wheelDiameter = 4.0; //inches
    const float disPerRot = axleLength * 3.15159;
    const float radToDegree = 57.2958;
    
    unsigned long currentMillis;
    unsigned long previousMillis;
    
public:
    //Wheel driving functions
    void driveFwd();
    void driveBkwd();
    void drive(int new_Motors_Speed);
    void driveTime(int new_Motors_Speed, unsigned long timeMicroseconds);
    void driveDist(int motorSpeed, float distInch);
    void noDrive();
    void setupOffset(unsigned int leftOffset, unsigned int rightOffset);
    void turn(int left_Motor_Speed, int right_Motor_Speed);
    void turnDeg(int motorSpeed, int degreeTurn);
    
};









