#include <arduino.h>

class HSensor {
public:
    HSensor(){}
public:
    int hSensorVal=1;
    int defaultSensorVal=510;
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










