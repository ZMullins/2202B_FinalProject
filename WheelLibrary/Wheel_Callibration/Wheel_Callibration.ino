\#include "DriveWheels.h"
#include <EEPROM.h>
#include <Wire.h>
#include "I2CEncoder.h"


Servo servo_RightMotor;
Servo servo_LeftMotor;

I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;

const int leftMotorPin = 8;
const int rightMotorPin = 9;


//EEPROM
const int rightOffAddL=12;
const int rightOffAddH=13;
const int leftOffAddL=14;
const int leftOffAddH=15;

DriveWheels wheels(servo_LeftMotor, servo_RightMotor, encoder_LeftMotor, encoder_RightMotor, defaultDriveSpeed);

int temp, temp1;
bool yes=false, no=true;
long right1, left1, right2, left2, rightOff, leftOff;
unsigned long time1, time2;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(2400);

  pinMode(rightMotorPin, OUTPUT);
  servo_RightMotor.attach(rightMotorPin);
  pinMode(leftMotorPin, OUTPUT);
  servo_LeftMotor.attach(leftMotorPin);

  encoder_LeftMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_LeftMotor.setReversed(false);  // adjust for positive count when moving forward
  encoder_RightMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_RightMotor.setReversed(true);  // adjust for positive count when moving forward

}

void loop() {
  // put your main code here, to run repeatedly:
  time2 = millis();
  if (time2 - time1 >= 5000) {
    yes = true;
  }

  if (no) {
    right2 = wheels.encoder_RightMotor->getRawPosition();
    left2 = wheels.encoder_LeftMotor->getRawPosition();
    wheels.driveFwd();
    time1 = millis();
  } else if (yes) {
    wheels.noDrive();
    right2 = wheels.encoder_RightMotor->getRawPosition();
    left2 = wheels.encoder_LeftMotor->getRawPosition();
    if ( left2 > right2 )
    {
      // May have to update this if different calibration time is used
      rightOff = 0;
      leftOff = (right2 - left2) / 4;
    }
    else
    {
      // May have to update this if different calibration time is used
      rightOff = (right2 - left2) / 4;
      leftOff = 0;
    }

    EEPROM.write(rightOffAddL, lowByte(rightOff));
    EEPROM.write(rightOffAddH, highByte(rightOff));
    EEPROM.write(leftOffAddL, lowByte(leftOff));
    EEPROM.write(leftOffAddH, highByte(leftOff));
  }

}
