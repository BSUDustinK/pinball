#include "LEDModule.h"



/**

*/
LEDModule::LEDModule(uint8_t indexStart, uint8_t numberOfLights, unsigned long primaryRGB, uint16_t interval){
  this->indexStart = indexStart;
  this->indexEnd = indexStart + (numberOfLights-1);
  this->primaryRGB = primaryRGB;
  this->interval = interval;
}
LEDModule::LEDModule(uint8_t indexStart, uint8_t numberOfLights, unsigned long primaryRGB) : LEDModule(indexStart, numberOfLights,primaryRGB,0){
}
/**
 * Sets the Mode of the LED, currently supported modes:
 * @param newMode OFF, STEADY, BLINK, FADE, PULSE, FLOW, ALTERNATE
 */
void LEDModule::setMode(uint8_t newMode){
  this->currentMode = newMode;
}
/**
 * Sets the current colour, doesn't overwrite the primary colours. 
 */
void LEDModule::setColour(unsigned long newColour){
  this->primaryRGB = newColour; //Remove after testing
  this->currentRGB = newColour; 
}
/**
* Does upkeep on the module, needs to be run before the data flush of FastLED.show();
*
* Modes OFF, STEADY, BLINK, FADE, PULSE, FLOW, ALTERNATE
*/
void LEDModule::updateModule(CRGB Leds){
  switch(this->currentMode){
    case LED_OFF:
      for(uint8_t i=indexStart;i<indexEnd;i++){
        Leds[i] = 0x000000;
      }
      break;
    case LED_STEADY:
      for(uint8_t i=indexStart;i<indexEnd;i++){
        Leds[i] = primaryRGB;
      }
      break;
    case LED_BLINK:

      break;
    case LED_FADE:

      break;
    case LED_PULSE:

      break;
    case LED_FLOW:

      break;
    case LED_ALTERNATE:

      break;
  }
}
/**
 * Does the math to determine flow state
 * 
 * impulse at t*(n-1)/n where the impulse cycles through each led and t is the time interval of the speed of the row
 * n = indexEnd - indexStart
 * t = time of impulse
 * 
 * A better example may be to check the shortTime against timer where the cool down is (n-1)/n*interval
  //complete better explenation
  k = a * (n-1)/n; //This is the time shift. It divides the system by the number of LEDs and distributes them across the active time period
  i*k gives us the specific LEDs time shift. 
  z(t) = (t%a)/a; this creates a sawtooth pattern with slope 1/a. Range 0 to 1, for x = 0 to a
  Desired outcome
  when time <= a
  f(t) = 255 * z(t-i*k); where i is the current LED in the group, ie 0, 1, 2, ..., n (NOT THE FULL ARRAY JUST THE MODULE)
  else 0
 * 
 */
void LEDModule::flowHandler(unsigned long time){
  uint16_t timeOn = this->interval * this->onTimePrecent; //Gets the precentage of time the led is meant to be on.
  uint8_t n = this->indexEnd - this->indexStart;
  uint16_t a = this->interval * ((double)this->onTimePrecent*.01); //determines the length of the thing
  for(uint8_t i = 0; i<n; i++){
    uint8_t brightness =((uint16_t)((time-((double)i)*a*(n-1)/n)) % this->interval <= a )? 255 * (( ((uint16_t)(time - ((double)i)*a*(n-1)/n)) % a ) / a) : 0; 
    this->adjustBrightness(i, brightness);
  }
}
/**
 * 
 */
void LEDModule::adjustBrightness(uint8_t index, uint8_t brightness){

}