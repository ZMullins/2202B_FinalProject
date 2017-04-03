
#include "SwivelArm.h"

//Arm Set Functions

void SwivelArm::goToZero() {
              
    servo_armMotor->write(zeroPos);
}

void SwivelArm::goToNeg() {
    
    servo_ArmMotor->write(negPos);
}

void SwivelArm::goToPos() {
    
    servo_ArmMotor->write(posPos);
}

void SwivelArm::goToSlide() {
    
    servo_ArmMotor->write(slidePos);
}

void SwivelArm::stopHere(){
    int temp =servo_ArmMotor->read()
    servo_ArmMotor->write(temp);
}

void SwivelArm::armRefresh(){
    servo_ArmMotor->refresh();
}


