/**
  DropDown Target Class
  @author Dustin Kirkpatrick
  @version v0.01-alpha
  @since 2025-09-24
*/

#include <Arduino.h>
#include <Servo.h>
#include "DropDown.h"
#include "CoolDown.h"

/*
* Variables in memory 
* Servo dropTarget;
* uint8_t targetHeight;
* uint8_t switchPin;
* uint8_t flag;
* unsigned long timer;
*/
#define MODE_DD_BUMP      0
#define MODE_DD_QUALIFIED 1
#define MODE_DD_LOCK      2
#define MODE_DD_SKILL     3

#define MIN_HEIGHT 0 //Adjust this to reduce wear on the servo, no noise should be heard and balls should roll over easy

// 0x00 -> 0000 ****

// 0x01 /1 true, /0 false
#define FLAG_DD_DIRECTION ((flag>>1)%2 == 1)
// 0x02 /1 true, /0 false
// #define FLAG_DD_

// 0x02 /1 true, /0 false
#define FLAG_DD_CALIBRATED ((flag>>2)%2 == 1)

#define FLAG_DD_ACTING ((flag>>3)%2 == 1)

//This takes up bit 4 and 5 00** 0000
#define FLAG_DD_MODE  (flag>>4)%4

DropDown::DropDown(){

}

DropDown::setUp(uint8_t servoPin, uint8_t switchPin){
  this->switchPin = switchPin;
  this->flag = 0x00;
  this->servoPin = servoPin;
  dropTarget.attach(servoPin);
  pinMode(switchPin, INPUT_PULLUP);
  dropTarget.write(MIN_HEIGHT);
  delay(1000);
}

void DropDown::calibrate(){
  if(FLAG_DD_CALIBRATED) { return; } //No need to recalibrate
  if(digitalRead(switchPin) == HIGH){
    uint8_t angle = 0;
    do{
      dropTarget.write(angle);
      delay(10);
      angle++;
    } while(digitalRead(switchPin) == HIGH);
    this->targetHeight = angle;
    this->flag |= (0x01 << 2);
    drop();
    delay(100);
  }
    // If calibration does not succeed, it will try again after the target is next commanded to rise
}
uint8_t DropDown::poll(unsigned long time){
  currentTime = time;

  if(FLAG_DD_ACTING && FLAG_DD_MODE != MODE_DD_SKILL){
    if(coolDownComplete(currentTime, &timer, 200)){ //3 nested ifs is a curse, but I don't want to initiate the timer unless it is acting
      if(FLAG_DD_MODE == MODE_DD_LOCK){
      dropTarget.write(targetHeight - 8);
      } else {
      dropTarget.write(MIN_HEIGHT);
    }
    flag &= ~(0x01<<3); //Clears action
    }
  }

  switch(FLAG_DD_MODE){
    case MODE_DD_BUMP:  //Pops back up instantly
      if(digitalRead(switchPin) == HIGH){
        raise();
        return 2;
      }
      break;
    case MODE_DD_QUALIFIED: //Stays down
      if(digitalRead(switchPin) == HIGH){
        return 1;
      }
      break;
    case MODE_DD_LOCK:  //Stays up, holds ball
      if(digitalRead(switchPin) == HIGH){
        raise();
        return 3;
      }
      break;
    case MODE_DD_SKILL: //Moves up and down as a moving target, CAN NOT DETECT HITS!
      animate();
      break;
  }
  return 0;
}


void DropDown::setMode(uint8_t mode){
  flag &= ~((0x30)); //Clears flag register
  flag &= ~(0x01<<3);//Clears current Action, always clear action when switching modes
  switch(mode){
    case MODE_DD_BUMP:  //Pops back up instantly
      flag |= 0x00;
      raise();
      drop();
      break;
    case MODE_DD_QUALIFIED: //Stays down
      flag |= 0x10;
      break;
    case MODE_DD_LOCK:  //Stays up
      flag |= 0x20;
      raise();
      drop();
      break;
    case MODE_DD_SKILL: //Moves up and down as a moving target, CAN NOT DETECT HITS! 
      flag |= 0x30;
      break;
  }
}

void DropDown::animate(){
  if(coolDownComplete(currentTime, &timer, 1320)){
    
    uint8_t height = (FLAG_DD_DIRECTION == 1)? MIN_HEIGHT: (targetHeight - 25);
    dropTarget.write(height);
    flag ^= 0x01<<1;
  }
}

void DropDown::attach(){
  dropTarget.attach(servoPin);
}
void DropDown::detach(){
  dropTarget.detach();
}

void DropDown::raise(){
  if(!FLAG_DD_CALIBRATED){
    calibrate();
  } else {
    dropTarget.write(targetHeight);
    flag |= (0x01<<3);
  }
}

void DropDown::drop(){
  if(FLAG_DD_MODE != MODE_DD_LOCK){
    dropTarget.write(MIN_HEIGHT);
  } else {
    dropTarget.write(targetHeight - 8);
  }
}