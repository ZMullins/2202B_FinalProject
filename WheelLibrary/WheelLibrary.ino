#include <Servo.h>
#include <EEPROM.h>
#include <Wire.h>
#include "I2CEncoder.h"


Servo servo_RightMotor;
Servo servo_LeftMotor;
I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;


boolean bt_Motors_Enabled = true;

//Change as per pinout
const int ci_Right_Motor = 8;
const int ci_Left_Motor = 9;
const int ci_I2C_SDA = A4;         // I2C data = white
const int ci_I2C_SCL = A5;         // I2C clock = yellow

//EEPROM address assignment (change as per full list)
const int ci_Left_Motor_Offset_Address_L = 12;
const int ci_Left_Motor_Offset_Address_H = 13;
const int ci_Right_Motor_Offset_Address_L = 14;
const int ci_Right_Motor_Offset_Address_H = 15;

//Default Values
const int ci_Left_Motor_Stop = 0;    
const int ci_Right_Motor_Stop = 0;
unsigned int ui_Motors_Speed = 300; 

unsigned long currentMillis;
unsigned long previousMillis;



void setup() {
  Wire.begin();       //Needed for encoder
  Serial.begin(2400);
  
  
  pinMode(ci_Right_Motor, OUTPUT);
  servo_RightMotor.attach(ci_Right_Motor);
  pinMode(ci_Left_Motor, OUTPUT);
  servo_LeftMotor.attach(ci_Left_Motor);


  // set up encoders. Must be initialized in order that they are chained together,
  //CHECK WHCIH MOTOR IS FORWARD AND WHICH IS BACK
  encoder_LeftMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_LeftMotor.setReversed(false);  // adjust for positive count when moving forward
  encoder_RightMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_RightMotor.setReversed(true);  // adjust for positive count when moving forward

  //EEPROM reading saved values
  b_LowByte = EEPROM.read(ci_Left_Motor_Offset_Address_L);
  b_HighByte = EEPROM.read(ci_Left_Motor_Offset_Address_H);
  ui_Left_Motor_Offset = word(b_HighByte, b_LowByte);
  b_LowByte = EEPROM.read(ci_Right_Motor_Offset_Address_L);
  b_HighByte = EEPROM.read(ci_Right_Motor_Offset_Address_H);
  ui_Right_Motor_Offset = word(b_HighByte, b_LowByte);
}

void loop() {
  // put your main code here, to run repeatedly
}



//Forward-Backward Functions

//default forward drive
void driveFwd(){
  servo_LeftMotor.writeMicroseconds(1500+ui_Motors_Speed);
  servo_RightMotor.writeMicroseconds(1500+ui_Motors_Speed);
}

//default backward drive
void driveBkwd(){
  servo_LeftMotor.writeMicroseconds(1500-ui_Motors_Speed);
  servo_RightMotor.writeMicroseconds(1500-ui_Motors_Speed);
}

//drive with new speed
void drive(int new_Motors_Speed){
  servo_LeftMotor.writeMicroseconds(1500+new_Motors_Speed);
  servo_RightMotor.writeMicroseconds(1500+new_Motors_Speed);
}

//drive with new speed for certain time
void drive(int new_Motors_Speed, unsigned long timeMicroseconds){
  currentMillis = millis();
  previousMillis = millis();
  
  while (currentMillis - previousMillis <= timeMicroseconds) {
  servo_LeftMotor.writeMicroseconds(1500+new_Motors_Speed);
  servo_RightMotor.writeMicroseconds(1500+new_Motors_Speed);
  currentMillis = millis();
  } 
}

//stop wheel motors
void stop(){
  servo_LeftMotor.writeMicroseconds(1500+ci_Left_Motor_Stop);
  servo_RightMotor.writeMicroseconds(1500+ci_Right_Motor_Stop);
}

void turn(int left_Motor_Speed, int right_Motor_Speed){
  servo_LeftMotor.writeMicroseconds(1500+left_Motor_Speed);
  servo_RightMotor.writeMicroseconds(1500+right_Motor_Speed);
}


  
