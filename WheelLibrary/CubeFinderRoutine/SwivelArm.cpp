
#include "SwivelArm.h"

//Arm Set Functions

void SwivelArm::goToZero() {
              
    servo_ArmMotor->write(zeroPos);
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

void SwivelArm:: goToDeg(int degree){
    degree+=adjustDeg;
    servo_ArmMotor->write(degree);
}

