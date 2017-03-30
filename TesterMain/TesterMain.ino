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
IRSensor IRSensor(4);
void setup() {
  Serial.begin(2400);
  pinMode(8, OUTPUT);
  servo_GripMotor.attach(8);
  
 }

void loop() {
	unsigned long val = Ultrasonic.valueReturned();
 int val2 = Optical.valueReturned();
  Serial.println(val2);
  bool grabbed = false;
  if (hallSensor.cubeSearch() == true) {
    servo_GripMotor.write(90); 
    grabbed= true;
    
  }
  if (grabbed == false) {
   
 servo_GripMotor.write(70);}
}
