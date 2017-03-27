//#include <DriveWheels.h>
#include <HSensor.h>
#include <Servo.h>
Servo servo_GripMotor;
HSensor hallSensor(1);
void setup() {
  Serial.begin(2400);
  pinMode(8, OUTPUT);
  servo_GripMotor.attach(8);
  
 }

void loop() {
  bool grabbed = false;
  if (hallSensor.cubeSearch() == true) {
    servo_GripMotor.write(90); 
    grabbed= true;
    
  }
  if (grabbed == false) {
   
 servo_GripMotor.write(70);}
}
