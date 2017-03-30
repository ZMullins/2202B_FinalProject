#ifndef IRSensor_h
#define IRSensor_h
#include "Arduino.h"
class IRSensor {
public:
	IRSensor(int pin = 2);
	int valueReturned();
	//Create variable to track what letters are being looked for
	//Create function to toggle which letters are being looked for
	//Check if its finding these letters
private:
	int _pin;
};
#endif
