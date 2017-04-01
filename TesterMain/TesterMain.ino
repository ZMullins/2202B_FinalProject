//#include <DriveWheels.h>
#include <HSensor.h>
#include <OpticalSensor.h>
#include <Servo.h>
#include <UltrasonicSensor.h>
#include <IRSensor.h>
Servo servo_GripMotor;
HSensor hallSensor(1); 
UltrasonicSensor Ultrasonic(2,3);
OpticalSensor Optical(0); 
IRSensor IR(10,5,6,7);
void setup() {
  Serial.begin(2400);
    pinMode(10, INPUT);
  pinMode(8, OUTPUT);
  servo_GripMotor.attach(8);
 }

void loop() {
  bool statusv = IR.AE();
  if (Serial.available() > 0) {
    Serial.println("ll");
    if (IR.checkLetters(statusv)) {
      Serial.println("Great Success!");
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
}
