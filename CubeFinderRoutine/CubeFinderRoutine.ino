#include "DriveWheels.h"
#include "HSensor.h"
#include <EEPROM.h>
#include <Wire.h>
#include "I2CEncoder.h"

Servo servo_RightMotor;
Servo servo_LeftMotor;

I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;

//Port pin constants
const int hSensorPin = A1;
const int rightMotorPin = 8;
const int leftMotorPin = 9;

void setup() {
  Wire.begin();
  Serial.begin(9600);

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
  // put your main code here, to run repeatedly:

}
