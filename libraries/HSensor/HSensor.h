#ifndef HSensor_h
#define HSensor_h
#include "Arduino.h"
class HSensor {
public:
	HSensor(int Hpin = 1);
	bool cubeDistWithin(int distance);
	int cubeDist();
	void hSensorCallibrationVal();
	bool cubeSearch();
private:
	int defaultSensorVal = 517;
	int _pin;
};
#endif

