#include "Arduino.h"
#include "OpticalSensor.h"
OpticalSensor::OpticalSensor(int pin) {
	// put your setup code here, to run once:
	_pin = pin;
	pinMode(_pin, INPUT);
}

int OpticalSensor::valueReturned() {
	int val = analogRead(_pin);
	return val;
}