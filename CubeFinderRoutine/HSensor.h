class HSensor {
public:
    HSensor(const int &pinOut);
    
public:
    const int hSensorVal=A1;
    int defaultSensorVal=517;
    
public:
    //Hall Effect Sensor Functions
    int cubeDist();
    bool cubeDistWithin(int distance);
    void hSensorCallibrationVal();
    bool cubeSearch();
};

int HSensor::cubeDist(){
    return analogRead(hSensorVal);
}

bool HSensor::cubeDistWithin(int distance){
    if (cubeDist()>=distance){
        return true;
    }
    return false;
}

void HSensor::hSensorCallibrationVal() {
    //Once arm has pivoted out of the way of the possible cube locations
    
    int temp=0;
    while (!(cubeDistWithin(temp))){
        temp++;
    }
    //normalized value is now set
    defaultSensorVal=temp;
}


bool HSensor::cubeSearch(){
    int temp = analogRead(hSensorVal)- defaultSensorVal;
    temp=abs(temp);
    
    if (temp > 1){
        return true;
    }
    return false;
}










