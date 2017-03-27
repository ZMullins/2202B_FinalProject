#include "Arduino.h"
#include "HSensor.h"
HSensor::HSensor(int Hpin) {
	// put your setup code here, to run once:
	_pin = Hpin;
	pinMode(Hpin, INPUT);
}

bool HSensor::cubeDistWithin(int distance) {
	if (cubeDist() >= distance) {
		return true;
	}
	return false;
}

int HSensor::cubeDist() {
	return analogRead(_pin);
}


void HSensor::hSensorCallibrationVal() {
	//Once arm has pivoted out of the way of the possible cube locations

	int temp = 0;
	while (!(cubeDistWithin(temp))) {
		temp++;
	}
	//normalized value is now set
	defaultSensorVal = temp;
	Serial.println(_pin);
}


bool HSensor::cubeSearch() {
	int temp = analogRead(_pin) - defaultSensorVal;
	temp = abs(temp);

	if (temp > 2) {
		return true;
	}
	return false;
}
