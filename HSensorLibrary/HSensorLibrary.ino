
const int hSensor = A1; 
int defaultSensorVal = 517;

void setup() {
  // put your setup code here, to run once:
pinMode(hSensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}


bool cubeDistWithin(int distance){
  if (cubeDist()>=distance){
    return true;
  }
  return false;
}

int cubeDist(){
  return analogRead(hSensor);
}


void hSensorCallibrationVal() {
  //Once arm has pivoted out of the way of the possible cube locations

  int temp=0;
  while (!(cubeDistWithin(temp))){
    temp++;
  }
 //normalized value is now set
  defaultSensorVal=temp;
}


bool cubeSearch(){
  int temp = analogRead(hSensor)- defaultSensorVal;
  temp=abs(temp);

  if (temp > 1){
    return true;
  }
  return false;
}


