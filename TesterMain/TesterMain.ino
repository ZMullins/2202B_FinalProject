//#include <DriveWheels.h>
#include <HSensor.h>
#include <OpticalSensor.h>
#include <Servo.h>
#include <UltrasonicSensor.h>
#include <IRSensor.h>
#include <SwivelArm.h>
#include <DriveWheels.h>
#include <Gripper.h>
#include <EEPROM.h>
#include <I2CEncoder.h>
#include <Wire.h>

int i = 0;
bool endOfCube = false;
int countA = 0;
int caseA = 0;
const int switchPin = 2;
const int hSensorPin = 1;
const int leftMotorPin = 8;
const int rightMotorPin = 9;
const int armMotorPin = 10;
const int gripMotorPin = 11;
const int linActMotorPin = 12;
const int tipActMotorPin = 13;
int currentMillis;
int previousMillis;
Servo servo_RightMotor;
Servo servo_LeftMotor;
Servo servo_ArmMotor;
Servo servo_Gripper;
I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;
DriveWheels wheels(servo_LeftMotor, servo_RightMotor, encoder_LeftMotor, encoder_RightMotor,290);
HSensor hallSense; 
Gripper grip(servo_Gripper);
UltrasonicSensor Ultrasonic(12,13);
SwivelArm arm(servo_ArmMotor);
OpticalSensor Optical(0); 
IRSensor IR(2,5,6,7);
void setup() {
  Wire.begin();
  Serial.begin(2400);
    pinMode(2, INPUT);
   pinMode(rightMotorPin, OUTPUT);
  servo_RightMotor.attach(rightMotorPin);
  pinMode(leftMotorPin, OUTPUT);
  servo_LeftMotor.attach(leftMotorPin);
  pinMode(armMotorPin, OUTPUT);
  servo_ArmMotor.attach(armMotorPin);
  pinMode(gripMotorPin, OUTPUT);
  servo_Gripper.attach(gripMotorPin);
    encoder_LeftMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_LeftMotor.setReversed(false);  // adjust for positive count when moving forward
  encoder_RightMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_RightMotor.setReversed(true); 
int val = Ultrasonic.valueReturned();
 /* while (val < 500){
    val = Ultrasonic.valueReturned();
    i+=4;
    arm.goToDeg(i);
    delay(1000);
   }*/
  
  }
 

void loop() {
  /*
  //  if(statusv == true) {
    //  Serial.println(statusv);
    //}
    while (Serial.available() > 0) {
      bool statusv = IR.AE();
    if (IR.checkLetters(statusv)){
      Serial.println("Yup");
    }
}}*/
 /*if (caseA == 0) {
   wheels.turn(400, 400);
         if (analogRead(switchPin) == HIGH){
        grip.closeGripper();

        caseA = 2;
        }
   if (Ultrasonic.valueReturned() < 300 && Ultrasonic.valueReturned()!= 0) {
       countA++;
      }
      if (countA > 10) {
        caseA = 1;
      }

  }*/
  if (caseA == 1) {
    //Swing arm to find cube on corner
  }
 // if (caseA == 2) {
    bool statusv = IR.AE();
    while (!(Serial.available() >0)) {
      wheels.turn(-200, 180);
  }
  wheels.noDrive();
  while (Serial.available() > 0) {
    if (IR.checkLetters(statusv)) {


      wheels.driveFwd();
    }
//   }
delay(500);
  }
  if (caseA == 3) {
    //Tip Pyramid
  }
  if (caseA == 4) {
    //inject cube
  }
  if (caseA == 5) {
    //set down pyramid, back up
  }
}







  /*    }
  //  if (!endOfCube) {
      if (Ultrasonic.valueReturned() < 300 && Ultrasonic.valueReturned() != 0) {
        countA++;
        Serial.println("So this is a reading");
      }
      if (countA > 10) {
        endOfCube = true;
      }
    if(hallSense.cubeSearch()){
   // wheels.noDrive();
  grip.closeGripper();
  countB++;
  //3Serial.println("Great Success!!");
  if (countB>20){
  hallSense.changeTolerance(2);}
  }
  else {
    wheels.turn(235,220);
      grip.openGripper();
  }}
  else {
    wheels.turn(-250,-200);
    
  }
  }*/
  
 /* delay(10000);
  for  (int iz = i; iz == i-30; iz-=10) {
    arm.goToDeg(iz);
    delay(700);
   }
    
  //0 = drive straight, 1 is drive to right (left wheel more powerful), 2 is drive to left
  int val = Ultrasonic.valueReturned();
  int driveStraight = 0;
  bool statusv = IR.AE();
if (val < 500) {
  driveStraight = 0;
}
else {
  count++;
  if (count > 4) {
    driveStraight = 0;
    }
   wheels.noDrive();
   wheels.driveBkwd();
   delay(300);
   for  (int iz = i; iz < i+30; iz+=10) {
    arm.goToDeg(-iz);
    delay(700);
   }
  if (val < 500) {
    driveStraight = 1;
  }
  else {
   
    driveStraight = 2;  }
  delay(700);

}
 if (driveStraight == 0) {
wheels.driveFwd();
  delay(1000);
 }
 
 else if (driveStraight == 1) {
 wheels.turn(-260, -180);
  delay(500);
 }
 else {
 
 wheels.turn(-180, -260);
  delay(500);
 }
 Serial.println(val);
 Serial.println(driveStraight);}
  /*  
  */
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
