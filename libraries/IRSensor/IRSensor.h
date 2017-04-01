#ifndef IRSensor_h
#define IRSensor_h
#include "Arduino.h"

class IRSensor {
public:
	IRSensor(int switchPin = 8, int cOne = 5, int cTwo = 6, int cThree = 7);
	bool AE();
	int valueReturned();
	bool checkLetters(bool lookingAE);
	//variable to track what letters are being looked for
private:
	int _switchPin;
};
#endif
