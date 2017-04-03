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
const int ultraSideInPin = 2;
const int ultraSideOutPin = 3;
const int ultraFrontInPin = 4;
const int ultraFrontOutPin = 5;
const int leftMotorPin = 8;
const int rightMotorPin = 9;


//EEPROM
const int rightOffAddL = 12;
const int rightOffAddH = 13;
const int leftOffAddL = 14;
const int leftOffAddH = 15;


const int defaultDriveSpeed = 300;
const int defaultDriveOversteer = 50;
const int disFromWall = 1070;

DriveWheels wheels(servo_LeftMotor, servo_RightMotor, encoder_LeftMotor, encoder_RightMotor, defaultDriveSpeed);
HSensor hallSense;
UltrasonicSensor ultraSideSense(ultraSideInPin, ultraSideOutPin), ultraFrontSense(ultraFrontInPin, ultraFrontOutPin);


bool isMotorNotSet = true;
int driveStage = 0;
int ultraSideDif = 0, ultraLBDif = 0;
int ultraTolerance = 100;
int numDivisions = 10;
unsigned int sensorCheckInterval = 100, sensorDisInterval = sensorCheckInterval * numDivisions, currentTime, previousTime;

int tempContainer=0;


bool no = false, yes = true, wallClose = false;
long right1, left1, right2, left2, rightOff, leftOff;
unsigned long time1, time2;


int ultraSideCount;

int arr1[10], arr2[10];




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
  if (ultraFrontSense.valueReturned()  < 200){
    wallClose=true;
  }


  
  //  if (hallSense.cubeSearch()) {
  if ((0)) {


  } else {
    time2=millis();
    
    if (time2>=time1){
      tempContainer=ultraSideSense.valueReturned();
      if (tempContainer){
      ultraSideDif=disFromWall-tempContainer;
      time1=millis();
      tempContainer=0;
      }
    }

    if (abs(ultraSideDif) <=ultraTolerance){
      if (isMotorNotSet && driveStage!=1){
        wheels.driveFwd();
      }
    } else if (ultraSideDif<0){
            if (isMotorNotSet && driveStage!=2){
        wheels.turn(200,250);
      }
    } else if (ultraSideDif>0){
                  if (isMotorNotSet && driveStage!=3){
        wheels.turn(250,200);
      }
    }

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

}
