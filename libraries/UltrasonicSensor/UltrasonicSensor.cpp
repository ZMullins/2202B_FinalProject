#include "Arduino.h"
#include "UltrasonicSensor.h"
UltrasonicSensor::UltrasonicSensor(int iPin, int oPin) {
	// put your setup code here, to run once:
	_iPin = iPin;
	_oPin = oPin;
	pinMode(_iPin, OUTPUT);
	pinMode(_oPin, INPUT);
}

unsigned long UltrasonicSensor::valueReturned() {
	digitalWrite(_iPin, HIGH);
	delayMicroseconds(10);  
	digitalWrite(_iPin, LOW);
	unsigned long val = pulseIn(_oPin, HIGH, 10000);
	Serial.println(val, DEC);
	return val;
}