//#include <DriveWheels.h>
#include <HSensor.h>
#include <Servo.h>
#include <UltrasonicSensor.h>
Servo servo_GripMotor;
HSensor hallSensor(1); 
UltrasonicSensor Ultrasonic(2,3);
void setup() {
  Serial.begin(2400);
  pinMode(8, OUTPUT);
  servo_GripMotor.attach(8);
  
 }

void loop() {
	unsigned long val = Ultrasonic.valueReturned();
  bool grabbed = false;
  if (hallSensor.cubeSearch() == true) {
    servo_GripMotor.write(90); 
    grabbed= true;
    
  }
  if (grabbed == false) {
   
 servo_GripMotor.write(70);}
}
