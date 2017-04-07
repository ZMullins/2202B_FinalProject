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
int motorspeed = 320;
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
Servo servo_RightMotor;
Servo servo_LeftMotor;
Servo servo_ArmMotor;
Servo servo_Gripper;
Servo servo_tipActMotor;
Servo servo_linActMotor;
I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;
DriveWheels wheels(servo_LeftMotor, servo_RightMotor, encoder_LeftMotor, encoder_RightMotor, 290);
HSensor hallSense(hSensorPin);
Gripper grip(servo_Gripper);
UltrasonicSensor Ultrasonic(12, 13);
SwivelArm arm(servo_ArmMotor);
<<<<<<< Updated upstream
OpticalSensor Optical(0); 
IRSensor IR(3,5,6,7);
=======
OpticalSensor Optical(0);
IRSensor IR(2, 5, 6, 7);


bool zachHatesThis = true, cubePassed = false;
long time1, time2, filterTime1, filterTime2;
long cubeInterval = 600, successCount = 0, passThroughCount = 0;

>>>>>>> Stashed changes
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
 // pinMode(gripMotorPin, OUTPUT);
  pinMode(tipActMotorPin, OUTPUT);
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
  if (caseA == 0) {
    time2 = millis();


    if (successCount == 5 && passThroughCount != 5) {
      successCount = 0;
      passThroughCount = 0;
    } else if (successCount == 5) {
      cubePassed = true;
      Serial.println("found Cube");


      wheels.noDrive();
      time1 = millis();
      zachHatesThis = true;
    }


    passThroughCount++;


    //    if (cubePassed) {
    ////
    ////      while (time2 - time1 <= cubeInterval) {
    ////        wheels.drive(-200);
    ////      }
    //      wheels.noDrive();
    //
    //      if (hallSense.cubeSearch()) {
    //        grip.closeGripper();
    //      } else {
    //        cubePassed = false;
    //      }
    //
    //    }
    //  } else if (hallSense.cubeSearch()) {


    int temp = hallSense.cubeDist();
    
    if (hallSense.cubeSearch()) {
      Serial.println(temp);
      successCount++;
      
    } else {
        if (zachHatesThis) {
          wheels.drive(300);
          grip.openGripper();
          zachHatesThis = false;
        }  
      }
    }
    //   wheels.turn(400, 400);
    //         if (analogRead(switchPin) == HIGH){
    //        grip.closeGripper();
    //
    //        caseA = 2;
    //        }
    //   if (Ultrasonic.valueReturned() < 300 && Ultrasonic.valueReturned()!= 0) {
    //       countA++;
    //      }
    //      if (countA > 10) {
    //        caseA = 1;
    //      }

<<<<<<< Updated upstream
  }*/
 caseA = 0;
  if (caseA== -4) {
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
    arm.goToDeg(0);
    time2 = millis();
     servo_tipActMotor.writeMicroseconds(1200);
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
        delay(3000);
        caseA = 1;
      }
    }
  if (cubePassed == true) {
    wheels.drive(-motorspeed);
    cubePassedTwo = true;
    cubePassed = false;
    delay(300);
    wheels.drive(motorspeed);
  }

    passThroughCount++;

    int temp = hallSense.cubeDist();
    
    if (hallSense.cubeSearch()) {
      Serial.println(temp);
      successCount++;
      
    } else{
        if (zachHatesThis) {
          wheels.drive(motorspeed);
          grip.openGripper();
          zachHatesThis = false;
        }  
      }
    }
    if (caseA == 1) {
      
      arm.goToDeg(400);
      delay(1050);
      grip.openGripper();
      delay(2000);
      caseA=2;
      delay(5000);
      arm.goToDeg(0);
    }
 if (caseA == 2) {
  
  
currentTime = millis();
    bool statusv = IR.AE();
    while (!(Serial.available() >0)) {
      Serial.println("Ihetre");
      if (motorOn == false) {
        motorOn = true;
        
        motorOnTwo = false;
      wheels.turn(-motorspeed, motorspeed);}
      if ((currentTime - previousTime) > 20000) {
        wheels.turn(250,250);
        previousTime = millis();
        while(((currentTime-previousTime)<3000 )) {
          wheels.turn(250,250);
        }
        }
      }
  while (Serial.available() > 0) {
    if (IR.checkLetters(statusv)) {
    
  Serial.println("Reading");

if (motorOnTwo == false) {
  motorOn = false;
  motorOnTwo = true;
      wheels.drive(250);
    }
   
    }
  }
   if (analogRead(switchPin == HIGH)) {
      caseA = 3;
      }
  }
  delay(10);
  if (caseA == 3) {

    servo_linActMotor.attach(linActMotorPin);
servo_RightMotor.detach();
servo_LeftMotor.detach();
//wheels.turn(-1300,-1300);
     servo_tipActMotor.attach(tipActMotorPin);
       servo_tipActMotor.writeMicroseconds(1200);
delay(1800);
servo_tipActMotor.writeMicroseconds(1500);   
servo_linActMotor.writeMicroseconds(1800);
delay (1200);
servo_linActMotor.writeMicroseconds(1200);
delay(1200);
servo_linActMotor.detach();
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
=======
    if (caseA == 1) {
      //Swing arm to find cube on corner
    }

    if (caseA == 2) {
      bool statusv = IR.AE();
      while (!(Serial.available() > 0)) {
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
  }
>>>>>>> Stashed changes







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
