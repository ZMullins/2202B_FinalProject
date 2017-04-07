#include <arduino.h>

class HSensor {
public:
    HSensor(){}
public:
    int hSensorVal=4;
    int defaultSensorVal=523;
	int count = 0;
	int tol = 5;
    
public:
    //Hall Effect Sensor Functions
    int cubeDist();
    bool cubeDistWithin(int distance);
    void hSensorCallibrationVal();
    bool cubeSearch();
	void changeTolerance(int newTol);
};










