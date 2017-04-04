#include "DriveWheels.h"
#include "HSensor.h"
#include "SwivelArm.h"
#include <EEPROM.h>
#include <Wire.h>
#include "I2CEncoder.h"
#include "UltrasonicSensor.h"


Servo servo_RightMotor;
Servo servo_LeftMotor;
Servo servo_ArmMotor;

I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;


//Port pin constants
const int hSensorPin = A1;
const int ultraWallInPin = 2;
const int ultraWallOutPin = 3;
const int ultraFrontInPin = 4;
const int ultraFrontOutPin = 5;
const int leftMotorPin = 8;
const int rightMotorPin = 9;
const int armMotorPin = 10;
const int gripperMotorPin = 11;
const int linActMotorPin = 12;
const int tipActMotorPin = 13;


//EEPROM
const int rightOffAddL = 12;
const int rightOffAddH = 13;
const int leftOffAddL = 14;
const int leftOffAddH = 15;


const int defaultDriveSpeed = 300;
const int defaultDriveOversteer = 50;
<<<<<<< HEAD
//const int disFromWall = 1070;
const int disFromWall=1200;
=======
const int disFromWall = 1070;
>>>>>>> origin/master

DriveWheels wheels(servo_LeftMotor, servo_RightMotor, encoder_LeftMotor, encoder_RightMotor, defaultDriveSpeed);
HSensor hallSense;
UltrasonicSensor ultraWallSense(ultraWallInPin, ultraWallOutPin), ultraFrontSense(ultraFrontInPin, ultraFrontOutPin);
SwivelArm arm(servo_ArmMotor);

bool isMotorNotSet = true;
int driveStage = 0;
int ultraSideDif = 0;
int ultraTolerance =300;
int numDivisions = 10;
long sensorCheckInterval = 100, motorCheckInterval = 2000;

int tempContainer = 0;


bool overWall = false, wallClose = false, isStraight = true, yes = true, no = false;
long right1, left1, right2, left2, rightOff, leftOff;
long timeUltra1, timeUltra2, timeMotor1, timeMotor2;




void setup() {
  Wire.begin();
  Serial.begin(2400);

  pinMode(rightMotorPin, OUTPUT);
  servo_RightMotor.attach(rightMotorPin);
  pinMode(leftMotorPin, OUTPUT);
  servo_LeftMotor.attach(leftMotorPin);
  pinMode(armMotorPin, OUTPUT);
  servo_ArmMotor.attach(armMotorPin);

  encoder_LeftMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_LeftMotor.setReversed(false);  // adjust for positive count when moving forward
  encoder_RightMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_RightMotor.setReversed(true);  // adjust for positive count when moving forward

  pinMode(hSensorPin, INPUT);

}


void loop() {
<<<<<<< HEAD
  if (ultraFrontSense.valueReturned()  < 200) {
    wallClose = true;
=======
  wheels.driveFwd();
}
 /* if (ultraFrontSense.valueReturned()  < 200){
    wallClose=true;
>>>>>>> origin/master
  }



  //  if (hallSense.cubeSearch()) {
  if ((yes)) {
    wheels.turn(350,345);
    timeUltra1=millis();
    timeMotor1=millis();
  } else {
    timeUltra2 = millis();
    timeMotor2 = millis();

    //Ultrasonic sensor readings based on difference from desired distance
    if (timeUltra2 - timeUltra1 >= sensorCheckInterval) {
      tempContainer = ultraWallSense.valueReturned();
      if (tempContainer) {
        if (tempContainer < ultraTolerance) {
          overWall = true;
          timeUltra1 = millis();

          if (driveStage == 3) {
            isStraight = true;
            driveStage = 0;
     
          }

        } else {
          overWall = false;
          if (isStraight) {
            wheels.noDrive();
            timeMotor1 = millis();
            isStraight = false;
          }
        }
      }
    }

<<<<<<< HEAD

    //Driving Control
    if (overWall && isStraight) {
      if (driveStage != 1) {
        wheels.turn(220,230);
        driveStage = 1;
=======
    if (abs(ultraSideDif) <=ultraTolerance){
      if (isMotorNotSet && driveStage!=1){
        wheels.driveFwd();
      }
    } else if (ultraSideDif<0){
            if (isMotorNotSet && driveStage!=2){
<<<<<<< HEAD
        wheels.turn(150,250);
      }
    } else if (ultraSideDif>0){
                  if (isMotorNotSet && driveStage!=3){
        wheels.turn(250,150);
=======
        wheels.turn(200,250);
      }
    } else if (ultraSideDif>0){
                  if (isMotorNotSet && driveStage!=3){
        wheels.turn(250,200);
>>>>>>> origin/master
>>>>>>> origin/master
      }

    } else if (!isStraight) {
      //      if (driveStage <2){
      //       arm.goToNeg();
      //      }
      //      if ((timeMotor2-timeMotor1 >= motorCheckInterval) && driveStage<2){
      //        timeMotor2=millis();
      //        timeMotor1=millis();
      //        driveStage=2;
      //      }
      //      if ((timeMotor2-timeMotor1 >= motorCheckInterval) && driveStage==2){
      //        if (overWall){
      //          arm.goToZero();
      //          wheels.turn(-300,-150);
      //        } else {
      //          arm.goToZero();
      //          wheels.turn(-150,-300);
      //        }
      //        driveStage=3;
      //      }


      wheels.turn(-180,-200);
      driveStage=3;
    }
  }

<<<<<<< HEAD
  //
  //    currentTime = millis();
  //
  //    if (currentTime - previousTime <= sensorCheckInterval) {
  //      arr1[counter] = ultraLFSense.valueReturned();
  //      arr2[counter] = ultraLBSense.valueReturned();
  //      counter++;
  //
  //    }
  //
  //    if (currentTime - previousTime <= sensorDisInterval) {
  //      float temp;
  //      int i, j;
  //      // the following two loops sort the array x in ascending order
  //      for (i = 0; i < numDivisions - 1; i++) {
  //        for (j = i + 1; j < numDivisions; j++) {
  //          if (arr1[j] < arr1[i]) {
  //            // swap elements
  //            temp = arr1[i];
  //            arr1[i] = arr1[j];
  //            arr1[j] = temp;
  //          }
  //        }
  //      }
  //
  //      if (numDivisions % 2 == 0) {
  //        // if there is an even number of elements, return mean of the two elements in the middle
  //        ultraLFDif= ((arr1[numDivisions / 2] + arr1[numDivisions / 2 - 1]) / 2.0);
  //      } else {
  //        // else return the element in the middle
  //        ultraLFDif= arr1[numDivisions / 2];
  //      }
  //
  //      float temp;
  //      int i, j;
  //      // the following two loops sort the array x in ascending order
  //      for (i = 0; i < numDivisions - 1; i++) {
  //        for (j = i + 1; j < numDivisions; j++) {
  //          if (arr2[j] < arr2[i]) {
  //            // swap elements
  //            temp = arr2[i];
  //            arr2[i] = arr2[j];
  //            arr2[j] = temp;
  //          }
  //        }
  //      }
  //
  //      if (numDivisions % 2 == 0) {
  //        // if there is an even number of elements, return mean of the two elements in the middle
  //        ultraLBDif= ((arr2[numDivisions / 2] + arr2[numDivisions / 2 - 1]) / 2.0);
  //      } else {
  //        // else return the element in the middle
  //        ultraLBDif= arr2[numDivisions / 2];
  //      }
  //
  //      counter=0;
  //
  //    }

  //    currentTime = millis();
  //
  //    if (currentTime - previousTime <= sensorCheckInterval) {
  //      ultraLFCount += ultraLFSense.valueReturned();
  //      ultraLFCount += ultraLBSense.valueReturned();
  //    }

}
=======
}*/8
>>>>>>> origin/master
