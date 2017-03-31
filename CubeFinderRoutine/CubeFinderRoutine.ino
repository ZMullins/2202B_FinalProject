#include "DriveWheels.h"
#include "HSensor.h"
#include <EEPROM.h>
#include <Wire.h>
#include "I2CEncoder.h"
#include "UltrasonicSensor.h"

Servo servo_RightMotor;
Servo servo_LeftMotor;

I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;


//Port pin constants
const int hSensorPin = A1;
const int ultraLFInPin = 2;
const int ultraLFOutPin = 3;
const int ultraLBInPin = 4;
const int ultraLBOutPin = 5;
const int leftMotorPin = 8;
const int rightMotorPin = 9;


//EEPROM
const int rightOffAddL=12;
const int rightOffAddH=13;
const int leftOffAddL=14;
const int leftOffAddH=15;


const int defaultDriveSpeed = 300;
const int defaultDriveOversteer = 50;
const int disFromWall = 800;

DriveWheels wheels(servo_LeftMotor, servo_RightMotor, encoder_LeftMotor, encoder_RightMotor, defaultDriveSpeed);
HSensor hallSense;
UltrasonicSensor ultraLFSense(ultraLFInPin, ultraLFOutPin), ultraLBSense(ultraLBInPin, ultraLBOutPin);


bool isMotorNotSet = true;
int driveStage = 0;
int ultraLFDif = 0, ultraLBDif = 0;


int temp, temp1;
bool yes=false, no=true;
long right1, left1, right2, left2, rightOff, leftOff;
unsigned long time1, time2;


void setup() {
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

  pinMode(hSensorPin, INPUT);
}


void loop() {
  //  if (hallSense.cubeSearch()) {
  if ((1)) {

    time2=millis();
    if (time2-time1 >= 5000){
      yes=true;
    }

    if (no) {
      right2 = wheels.encoder_RightMotor->getRawPosition();
      left2 = wheels.encoder_LeftMotor->getRawPosition();
      wheels.driveFwd();
      time1=millis();
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


  } else {
    ultraLFDif = disFromWall - ultraLFSense.valueReturned();
    ultraLBDif = disFromWall - ultraLBSense.valueReturned();

    if (abs(ultraLFDif) < 120)
      ultraLFDif = 0;
    if (abs(ultraLBDif) < 120)
      ultraLBDif = 0;

    if (ultraLFDif == 0 && ultraLBDif == 0) {
      if (isMotorNotSet && driveStage != 1) {
        wheels.driveFwd();
        isMotorNotSet = false;
        driveStage = 1;
        Serial.println("here1");
      }
    } else if (ultraLFDif != 0) {
      if (ultraLFDif < 0) {
        if (isMotorNotSet && driveStage != 2) {
          wheels.turn(-200, -300);
          isMotorNotSet = false;
          driveStage = 2;
          Serial.println("here2");
        }
      } else if (ultraLFDif > 0) {
        if (isMotorNotSet && driveStage != 2) {
          wheels.turn(-300, -200);
          isMotorNotSet = false;
          driveStage = 2;
          Serial.println("here3");
        }
      }
    } else if (ultraLBDif != 0) {
      if (ultraLBDif < 0) {
        if (isMotorNotSet && driveStage != 3) {
          wheels.turn(0, 200);
          isMotorNotSet = false;
          driveStage = 3;
          Serial.println("here4");
        }
      } else if (ultraLBDif > 0) {
        if (isMotorNotSet && driveStage != 3) {
          wheels.turn(0, -200);
          isMotorNotSet = false;
          driveStage = 3;
          Serial.println("here5");
        }
      }
    }
  }

}
