#include <Servo.h>
#include <EEPROM.h>
#include <arduino.h>

class Gripper {
  public:
    Gripper(Servo& armObject) {
      servo_GripperMotor = &armObject;
    }

  public:
    Servo* servo_GripperMotor;

    const int openPos = 60;
    const int closePos = 150	;

  public:
    //Wheel driving functions
    void openGripper();
    void closeGripper();

};









