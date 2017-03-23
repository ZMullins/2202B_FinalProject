//Include these libraries, both are utilized for I2C encoders
#include <Wire.h>
#include "I2CEncoder.h"

//Create I2CEncoder variables for each motor
I2CEncoder encoder_RandomMotor;

//Connect 4 pin to correct pinout, check clock and data pins
const int ci_I2C_SDA = A4;         // I2C data = white
const int ci_I2C_SCL = A5;         // I2C clock = yellow

//Set up EEPROM addresses if encoder values will be utilized for position or offset recall
const int ci_Some_Motor_Offset_Address_H = 0; //add next motor with 1, then next with 2...

//Set up variables to use in the code, examples are shown to showcase different possibilities
byte b_LowByte;
byte b_HighByte;
long l_Left_Motor_Position;
long l_Right_Motor_Position;
unsigned long ui_Left_Motor_Offset;
unsigned long ui_Right_Motor_Offset;

void setup() {
  //include these for I2C Encoder to function properly
  Wire.begin();        // Wire library required for I2CEncoder library


  //set up encoders. Must be initialized in order that they are chained together,
  encoder_RandomMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_RandomMotor.setReversed(false);  // set to true if motor control needed to be switched, this will give you positive counts while turning the encoder

  //read previously stored values from EEPROM. Examples shown below to showcase possibilities
  b_LowByte = EEPROM.read(ci_Left_Motor_Offset_Address_L);
  b_HighByte = EEPROM.read(ci_Left_Motor_Offset_Address_H);
  ui_Left_Motor_Offset = word(b_HighByte, b_LowByte);
  b_LowByte = EEPROM.read(ci_Right_Motor_Offset_Address_L);
  b_HighByte = EEPROM.read(ci_Right_Motor_Offset_Address_H);
  ui_Right_Motor_Offset = word(b_HighByte, b_LowByte);





}

void loop() {
  //example uses of encoders

  //to get raw positions
  l_Left_Motor_Position = encoder_LeftMotor.getRawPosition();
  l_Right_Motor_Position = encoder_RightMotor.getRawPosition();

  //additional regular functions
  encoder_RandomMotor.getSpeed();
  encoder_RandomMotor.getPosition();
  encoder_RandomMotor.zero();

  //motor speed changing based on offset
  ui_Left_Motor_Speed = constrain(ui_Motors_Speed + ui_Left_Motor_Offset, 1600, 2100);
  ui_Right_Motor_Speed = constrain(ui_Motors_Speed + ui_Right_Motor_Offset, 1600, 2100);

  //example callibration for two wheel motors (modified from Lab 4)

  /*
    prior to set up loop:
    boolean bt_3_S_Time_Up = false;
    boolean bt_Cal_Initialized = false;
    const int ci_Motor_Calibration_Time = 5000;
  */

  //beginning if statement allows for the 3 second delay after selecting a mode to begin the switch statements.
  //This if statement is not necessary to gather and set the motor offset
  //Included to showcase the potential versatility in deployment of callibration functions
  if ((millis() - ul_3_Second_timer) > 3000)
  {
    bt_3_S_Time_Up = true;
  }

  if (bt_3_S_Time_Up)
  {
  //Enter this first loop if this is the first pass through this section of code 
  //This section showcases how to perform tasks and avoid while loops, (allowing for tasks without interrupts)
    if (!bt_Cal_Initialized)
    {
      bt_Cal_Initialized = true;
      encoder_LeftMotor.zero();
      encoder_RightMotor.zero();
      ul_Calibration_Time = millis();
      servo_LeftMotor.writeMicroseconds(ui_Motors_Speed);
      servo_RightMotor.writeMicroseconds(ui_Motors_Speed);
    }

    // enters this loop after first pass through and if time requirement has been met
    else if ((millis() - ul_Calibration_Time) > ci_Motor_Calibration_Time)
    {
      servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
      servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
      l_Left_Motor_Position = encoder_LeftMotor.getRawPosition();
      l_Right_Motor_Position = encoder_RightMotor.getRawPosition();

      if (l_Left_Motor_Position > l_Right_Motor_Position)
      {
        // Based on 5 second callibration time. I would not tamper with callibration time values.
        ui_Right_Motor_Offset = 0;
        ui_Left_Motor_Offset = (l_Left_Motor_Position - l_Right_Motor_Position) / 4;
      }
      else
      {
         // Based on 5 second callibration time. I would not tamper with callibration time values.
        ui_Right_Motor_Offset = (l_Right_Motor_Position - l_Left_Motor_Position) / 4;
        ui_Left_Motor_Offset = 0;
      }
  
  //writes all gathered values to EEPROM addresses    
#endif 
      EEPROM.write(ci_Right_Motor_Offset_Address_L, lowByte(ui_Right_Motor_Offset));
      EEPROM.write(ci_Right_Motor_Offset_Address_H, highByte(ui_Right_Motor_Offset));
      EEPROM.write(ci_Left_Motor_Offset_Address_L, lowByte(ui_Left_Motor_Offset));
      EEPROM.write(ci_Left_Motor_Offset_Address_H, highByte(ui_Left_Motor_Offset));
    }
}
