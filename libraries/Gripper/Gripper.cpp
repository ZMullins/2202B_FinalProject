
#include "Gripper.h"

//Arm Set Functions

void Gripper::openGripper() {
              
    servo_GripperMotor->write(openPos);
}

void Gripper::closeGripper() {
    
    servo_GripperMotor->write(closePos);
}
