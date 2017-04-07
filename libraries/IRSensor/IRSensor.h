#ifndef IRSensor_h
#define IRSensor_h
#include "Arduino.h"

class IRSensor {
public:
	IRSensor(int switchPin, int charOne = 5, int charTwo = 6, int charThree = 7);
	bool AE();
	char getValue();
	bool searchForPyramid(bool lookingForPyr);
	//variable to track what letters are being looked for
private:
	int _switchPin;
};
#endif
