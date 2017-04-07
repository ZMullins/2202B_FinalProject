#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h
#include "Arduino.h"
class UltrasonicSensor {
public:
	UltrasonicSensor(int iPin = 2, int oPin = 3);
	unsigned long valueReturned();
private:
	int _iPin, _oPin;
};
#endif

