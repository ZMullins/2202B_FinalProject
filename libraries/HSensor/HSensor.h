#include<arduino.h>

class HSensor {
public:
    HSensor(){}
public:
    int hSensorVal=1;
    int defaultSensorVal=517;
    
public:
    //Hall Effect Sensor Functions
    int cubeDist();
    bool cubeDistWithin(int distance);
    void hSensorCallibrationVal();
    bool cubeSearch();
};










