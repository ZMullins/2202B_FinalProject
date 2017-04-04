#include <Servo.h>
#include <EEPROM.h>
#include <arduino.h>

class SwivelArm {
  public:
    SwivelArm(Servo& armObject) {
      servo_ArmMotor = &armObject;
      b_LowByte = EEPROM.read(14);
      b_HighByte = EEPROM.read(15);
      ui_Left_Motor_Offset = word(b_HighByte, b_LowByte);
      b_LowByte = EEPROM.read(12);
      b_HighByte = EEPROM.read(13);
      ui_Right_Motor_Offset = word(b_HighByte, b_LowByte);
    }

  public:
    Servo* servo_armMotor;

    const int zeroPos = 10;
    const int negPos = 0;
    unsigned int posPos = 20;
    unsigned int slidePos=180;
    byte b_LowByte;
    byte b_HighByte;

    unsigned long currentMillis;
    unsigned long previousMillis;

  public:
    //Wheel driving functions
    void goToZero();
    void goToNeg();
    void goToPos();
    void goToSlide();
    void stopHere();
    void armRefresh();


};









