#ifndef OpticalSensor_h
#define OpticalSensor_h
#include "Arduino.h"
class OpticalSensor {
public:
	OpticalSensor(int pin = 0);
	int valueReturned();
private:
	int _pin;
};
#endif

