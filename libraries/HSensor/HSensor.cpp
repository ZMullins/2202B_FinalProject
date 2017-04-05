
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


bool HSensor::cubeSearch(){
	
    int valer = analogRead(hSensorVal)- defaultSensorVal;
    valer=abs(valer);
    
    if (valer > 5){

    
	/*if (count > 10) {
		count = 0;*/
		return true;
	}
    return false;
	delay(50);
}



