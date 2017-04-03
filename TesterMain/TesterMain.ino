//#include <DriveWheels.h>
#include <HSensor.h>
#include <OpticalSensor.h>
#include <Servo.h>
#include <UltrasonicSensor.h>
#include <IRSensor.h>
#include <DriveWheels.h>
#include <EEPROM.h>
#include <I2CEncoder.h>
#include <Wire.h>
const int rightMotorPin = 8;
const int leftMotorPin = 9;

Servo servo_RightMotor;
Servo servo_LeftMotor;
I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;
DriveWheels wheels(servo_LeftMotor, servo_RightMotor, encoder_LeftMotor, encoder_RightMotor,290);
//HSensor hallSensor(1); 
UltrasonicSensor Ultrasonic(2,3);
OpticalSensor Optical(0); 
IRSensor IR(10,5,6,7);
void setup() {
  Wire.begin();
  Serial.begin(2400);
    pinMode(10, INPUT);
   pinMode(rightMotorPin, OUTPUT);
  servo_RightMotor.attach(rightMotorPin);
  pinMode(leftMotorPin, OUTPUT);
  servo_LeftMotor.attach(leftMotorPin);
    encoder_LeftMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_LeftMotor.setReversed(false);  // adjust for positive count when moving forward
  encoder_RightMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_RightMotor.setReversed(true); 
 }

void loop() {
  bool statusv = IR.AE();
  int count = 0;
  while (!(Serial.available() >0)) {
    count++
    if (count < 20) {
      wheels.turn(200, -200);
      delay (100);}
     else {
      wheels.turn(-200, 200);
      delay(100);
     }
  }
  wheels.noDrive();
    if (IR.checkLetters(statusv)) {
      Serial.println("Great Success!");
      wheels.driveFwd();
      delay(500);
      wheels.noDrive();
    }
  }
  /*
	unsigned long val = Ultrasonic.valueReturned();
 int val2 = Optical.valueReturned();
  Serial.println(val2);
  bool grabbed = false;
  if (hallSensor.cubeSearch() == true) {
    servo_GripMotor.write(90); 
    grabbed= true;
    
  }
  if (grabbed == false) {
   
 servo_GripMotor.write(70);}*/
