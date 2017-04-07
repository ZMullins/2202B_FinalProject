
#include "HSensor.h"

//Hall Effect Sensor Functions

int HSensor::cubeReading(){
    return analogRead(hallSensorPin);
}

bool HSensor::isCubeReadingWithin(int distance){
    if (cubeReading()>=distance){
        return true;
    }
    return false;
}

void HSensor::hallSensorCallibration() {
    //Once arm has pivoted out of the way of the possible cube locations
    
    int temp=0;
    while (!(isCubeReadingWithin(temp))){
        temp++;
    }
    //normalized value is now set
    defaultSensorVal=temp;
}
void HSensor::changeTolerance(int newTol) {
	tol = newTol;
}

bool HSensor::searchForCube(){
	
    int differenceVal = analogRead(hallSensorPin)- defaultSensorVal;
    differenceVal=abs(differenceVal);
    
	if (differanceVal > tol) {
		return true;
	}
    return false;
}



