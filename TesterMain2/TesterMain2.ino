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
bool zachHatesThis = true, cubePassed = false, cubePassedTwo = false;
long time1, time2, filterTime1, filterTime2;
long cubeInterval = 600, successCount = 0, passThroughCount = 0;
int currentTime = 0;
int currentTime2 = 0;
int motorspeed = 360;
int previousTime = 0;
int i = 0;
bool firstTime = true;
bool motorOn = false;
bool motorOnTwo = false;
int countA = 0;
int caseA = 0;
const int switchPin = 2;
const int hSensorPin = A4;
const int leftMotorPin = 8;
const int rightMotorPin = 9;
const int armMotorPin = 10;
const int gripMotorPin = 11;
const int linActMotorPin = 12;
const int tipActMotorPin = 4;
int currentMillis;
int previousMillis;
int currentMillis2;
Servo servo_RightMotor;
Servo servo_LeftMotor;
Servo servo_ArmMotor;
Servo servo_Gripper;
Servo servo_tipActMotor;
Servo servo_linActMotor;
Servo servo_restrict;
I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;
DriveWheels wheels(servo_LeftMotor, servo_RightMotor, encoder_LeftMotor, encoder_RightMotor,290);
HSensor hallSense; 
Gripper grip(servo_Gripper);
UltrasonicSensor Ultrasonic(12,13);
SwivelArm restrict(servo_restrict);
SwivelArm arm(servo_ArmMotor);
OpticalSensor Optical(0); 
IRSensor IR(3,5,6,7);
void setup() {
  Wire.begin();
  Serial.begin(2400);
    pinMode(2, INPUT);
   pinMode(rightMotorPin, OUTPUT);
  servo_RightMotor.attach(rightMotorPin);
  pinMode(leftMotorPin, OUTPUT);
  servo_LeftMotor.attach(leftMotorPin);
  //pinMode(armMotorPin, OUTPUT);
  servo_ArmMotor.attach(armMotorPin);
  servo_restrict.attach(2);
 // pinMode(gripMotorPin, OUTPUT);
  pinMode(tipActMotorPin, OUTPUT);
  servo_Gripper.attach(gripMotorPin);
  
    encoder_LeftMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_LeftMotor.setReversed(false);  // adjust for positive count when moving forward
  encoder_RightMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_RightMotor.setReversed(true); 
int val = Ultrasonic.valueReturned();
arm.goToDeg(0);
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
 caseA = 0;
  if (caseA== -4) {
     restrict.goToDeg(0);
    for (int i =-360; i < 360; i+=50) {
      arm.goToDeg(i);
      delay(2000);
      Serial.println(i);
    }
  }
  if (caseA== -3) {
       servo_linActMotor.attach(linActMotorPin);
    servo_linActMotor.writeMicroseconds(1800);
    delay(1800);
    servo_linActMotor.detach();
    caseA = -2;
  }
if (caseA == -1) {
    servo_linActMotor.attach(linActMotorPin);
    servo_linActMotor.writeMicroseconds(1200);
    delay(1800);
    servo_linActMotor.detach();
    caseA = -2;
}
   if (caseA == 0) {
    if (firstTime == true) {
   servo_tipActMotor.attach(tipActMotorPin);
      servo_tipActMotor.writeMicroseconds(1800);
delay (1800);
servo_tipActMotor.writeMicroseconds(1500);
delay (5000);
servo_tipActMotor.detach();
wheels.turn(motorspeed + 50, motorspeed);
firstTime = false;
  }
    
    
    time2 = millis();
     servo_tipActMotor.writeMicroseconds(1200);
     delay(3000);
    if (successCount == 5 && passThroughCount != 5) {
      successCount = 0;
      passThroughCount = 0;
    } else if (successCount == 5) {
      cubePassed = true;
      Serial.println("found Cube");
successCount = 0;
passThroughCount = 0;
      wheels.noDrive();
      time1 = millis();
      zachHatesThis = true;
      if (cubePassedTwo == true) {
        grip.closeGripper();
        delay(2000);
        caseA = 1;
      }
    }
  if (cubePassed == true) {
    wheels.drive(-motorspeed);
    cubePassedTwo = true;
    cubePassed = false;
    delay(600);
wheels.noDrive();
  }

    passThroughCount++;

    int temp = hallSense.cubeDist();
    
    if (hallSense.cubeSearch()) {
      Serial.println(temp);
      successCount++;
      
    } else{
        if (zachHatesThis) {
          wheels.drive(motorspeed);
          if (caseA == 0) {
          grip.openGripper();}
          zachHatesThis = false;
        }  
      }
    }
    if (caseA == 1) {
      wheels.drive(motorspeed);
      delay(400);
      servo_LeftMotor.detach();
      servo_RightMotor.detach();
      arm.goToDeg(400);
      delay(1000);
      //grip.openGripper();

  servo_LeftMotor.attach(leftMotorPin);
  servo_RightMotor.attach(rightMotorPin);
      for (int i =0; i < 3; i++){
              wheels.turn(330, 300);
        delay(3000);
      wheels.drive(motorspeed);
      delay(4000);}
      caseA = 3;
    }
 if (caseA == 2) {

  
currentTime = millis();
    bool statusv = IR.AE();
    while (!(Serial.available() >0)) {
      Serial.println("Ihetre");
      if (motorOn == false) {
        motorOn = true;
        
        motorOnTwo = false;
      wheels.turn(-motorspeed-100, motorspeed-100);}
      if ((currentTime - previousTime) > 5000) {
        wheels.turn(250,250);delay(500);
        previousTime = millis();
        while(((currentTime-previousTime)<3000 )) {
          wheels.turn(250,250);
        }
        }
      }
  while (Serial.available() > 0) {
    if (IR.checkLetters(statusv)) {
    currentTime2 = 0;
  Serial.println("Reading");

if (motorOnTwo == false) {
  motorOn = false;
  motorOnTwo = true;
      wheels.drive(250);
    }
   
    }
  }
  if (currentTime - currentTime2 > 90000) {
     caseA = 3;
  }
   //if (analogRead(switchPin == HIGH)) {
    //  caseA = 3;
   //   }
      firstTime = true;
  }
  delay(10);
  if (caseA == 3) {
    if (firstTime == true) {
    restrict.goToDeg(-90);}
delay(500);
    servo_linActMotor.attach(linActMotorPin);
servo_RightMotor.detach();
servo_LeftMotor.detach();
//wheels.turn(-1300,-1300);
     servo_tipActMotor.attach(tipActMotorPin);
       servo_tipActMotor.writeMicroseconds(1200);
delay(1800);
servo_tipActMotor.writeMicroseconds(1500);   
servo_linActMotor.writeMicroseconds(1700);
delay (1200);
servo_linActMotor.writeMicroseconds(1300);
delay(1200);
servo_linActMotor.detach();
restrict.goToDeg(180);
caseA=4;}
 if (caseA == 4) {
    servo_tipActMotor.writeMicroseconds(1800);
delay(1800);
servo_tipActMotor.writeMicroseconds(1500);
  servo_tipActMotor.detach();  
 caseA=5;
  }
  if (caseA == 5) {
   wheels.turn(-motorspeed,-motorspeed);
    
}}







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
