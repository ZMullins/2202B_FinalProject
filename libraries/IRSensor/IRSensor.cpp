#include "Arduino.h"
#include "IRSensor.h"
IRSensor::IRSensor(int pin) {
	// put your setup code here, to run once:
	_pin = pin;
	pinMode(_pin, INPUT);
}

int IRSensor::valueReturned() {
	int val = digitalRead(_pin);
	return val;
}