#include <Servo.h>
#include <EEPROM.h>
#include <Wire.h>
#include "I2CEncoder.h"
#include "uSTimer2.h"
#include <arduino.h>

class DriveWheels {
  public:
    DriveWheels(Servo& leftObject, Servo& rightObject, I2CEncoder& leftEnc, I2CEncoder& rightEnc, unsigned int defMotorSpeed) {
      servo_LeftMotor = &leftObject;
      servo_RightMotor = &rightObject;
      encoder_LeftMotor = &leftEnc;
      encoder_RightMotor = &rightEnc;
      ui_Motors_Speed = defMotorSpeed;
      b_LowByte = EEPROM.read(14);
      b_HighByte = EEPROM.read(15);
      ui_Left_Motor_Offset = word(b_HighByte, b_LowByte);
      b_LowByte = EEPROM.read(12);
      b_HighByte = EEPROM.read(13);
      ui_Right_Motor_Offset = word(b_HighByte, b_LowByte);
    }

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
    byte b_LowByte;
    byte b_HighByte;
    const float axleLength = 9.06; //inches
    const float wheelDiameter = 4.0; //inches
    const float disPerRot = axleLength * 3.15159;
    const float radToDegree = 57.2958;

    unsigned long currentMillis;
    unsigned long previousMillis;

  public:
    //Wheel driving functions
    void driveFwd();
    void driveFwdEnc();
    void driveBkwd();
    void drive(int new_Motors_Speed);
    void driveTime(int new_Motors_Speed, unsigned long timeMicroseconds);
    void driveDist(int motorSpeed, float distInch);
    void noDrive();
    void setupOffset(unsigned int leftOffset, unsigned int rightOffset);
    void turn(int left_Motor_Speed, int right_Motor_Speed);
    void turnDeg(int motorSpeed, int degreeTurn);
    void wheelRefresh();

};









