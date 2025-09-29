#include <Arduino.h>
/**
    Used to track cooldowns
    @param initialTime A pointer to the timer for the desired module
    @param duration The length in Milliseconds that the operation will wait before operating again
    @return True if a timer was created or a previous timer has finished
  */
  bool coolDownComplete(unsigned long currentTime, unsigned long * initialTime, long duration){
    if(*initialTime == NULL){  //Initializes the timer on first operation 
      *initialTime = currentTime; 
      return true;
    } 
    if(((currentTime - (*initialTime)) > duration)){
      *initialTime = currentTime; 
      return true;
    }
    return false;
  }
 