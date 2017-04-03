
#include "SwivelArm.h"

//Arm Set Functions

void SwivelArm::goToZero() {
              
    servo_armMotor->write(zeroPos);
}

void SwivelArm::goToNeg() {
    
    servo_armMotor->write(negPos);
}

void SwivelArm::goToPos() {
    
    servo_armMotor->write(posPos);
}

void SwivelArm::goToSlide() {
    
    servo_armMotor->write(slidePos);
}

void SwivelArm::stopHere(){
    int temp =servo_armMotor->read()
    servo_armMotor->write(temp);
}

void SwivelArm::armRefresh(){
    servo_armMotor->refresh();
}


