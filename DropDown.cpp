/**
  DropDown Class
  @author Dustin Kirkpatrick
  @version v0.01-alpha
  @since 2025-09-24
*/

#include <Arduino.h>
#include <Servo.h>
#include "DropDown.h"

// 0x00 -> 0000 0000

// 0x01 /1 true, /0 false
#define FLAG_DD_LOCKED ((flag>>1)%2 == 1) //I might not use this. It depends...
// 0x02 /1 true, /0 false
#define FLAG_DD_OPEN ((flag>>1)%2 == 1)

DropDown::DropDown(uint8_t servoPin, uint8_t switchPin){
  dropTarget.attach(servoPin);
  pinMode(switchPin, INPUT);
  enable();
}
void DropDown::calibrate(){
  int angle = 0;
  do{
    dropTarget.write(angle);
    delay(100);
    angle++;
  } while(!digitalRead(switchPin));
}
uint8_t DropDown::poll(){
  if(digitalRead(switchPin)){
    if(!FLAG_DD_OPEN){
      raise();
      return 2; //Target is hit and pops back up
    }
    return 1; //Target was hit and is now open
  }
  return 0; //Target was not hit, or is locked
}
void DropDown::raise(){
  dropTarget.write(targetHeight);
  dropTarget.write(0);
}
void DropDown::drop(){
  if(!FLAG_DD_LOCKED){
    dropTarget.write(0);
  }
}

void DropDown::enable(){
  flag |= 0x02;
  drop();
}
void DropDown::disable(){
  flag &= ~(0x02);
}
void DropDown::lock(){
  flag |= 0x01;
  raise();
}
void DropDown::unlock(){
  flag &= ~(0x01);
  drop();
}