#include <Servo.h>
#include <EEPROM.h>
#include <arduino.h>

class SwivelArm {
  public:
    SwivelArm(Servo& armObject) {
      servo_ArmMotor = &armObject;
    }

  public:
    Servo* servo_ArmMotor;

    const int adjustDeg=10;
    const int zeroPos = adjustDeg;
    const int negPos = 0;
    const int posPos = adjustDeg*2;;
   
    unsigned int slidePos=180;
    byte b_LowByte;
    byte b_HighByte;

    unsigned long currentMillis;
    unsigned long previousMillis;

  public:
    //Arm moving functions11
    void goToZero();
    void goToNeg();
    void goToPos();
    void goToSlide();
    void goToDeg(int degree);
    void armRefresh();


};









