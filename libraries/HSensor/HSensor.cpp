
#include "HSensor.h"

//Hall Effect Sensor Functions

int HSensor::cubeDist(){
    return analogRead(hSensorVal);
}

bool HSensor::cubeDistWithin(int distance){
    if (cubeDist()>=distance){
        return true;
    }
    return false;
}

void HSensor::hSensorCallibrationVal() {
    //Once arm has pivoted out of the way of the possible cube locations
    
    int temp=0;
    while (!(cubeDistWithin(temp))){
        temp++;
    }
    //normalized value is now set
    defaultSensorVal=temp;
}
void HSensor::changeTolerance(int newTol) {
	tol = newTol;
}

bool HSensor::cubeSearch(){
	
    int valer = analogRead(hSensorVal)- defaultSensorVal;
    valer=abs(valer);
    
	if (valer > tol) {

    
	/*if (count > 10) {
		count = 0;*/
		return true;
	}
    return false;
}



