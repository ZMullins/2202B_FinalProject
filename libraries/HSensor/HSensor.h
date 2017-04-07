#include <arduino.h>

class HSensor {
public:
    HSensor(int pin){
        hallSensorPin=pin;
    }
public:
    int hallSensorPin;
    int defaultSensorVal=523;
	int count = 0;
	int tol = 10;
    
public:
    //Hall Effect Sensor Functions
    int cubeReading();
    bool isCubeReadingWithin(int distance);
    void hallSensorCallibration();
    bool searchForCube();
	void changeTolerance(int newTol);
};










