#ifndef __LEDControlModes
#define __LEDControlModes
#include <Arduino.h>
#include <FastLED.h>

#define  LED_OFF        0 //Self explanatory
#define  LED_STEADY     1 //STAYS ON
#define  LED_BLINK      2 //BLINKS
#define  LED_FADE       3 //FLASH ON FADES OUT 
#define  LED_PULSE      4 //FADES IN AND OUT
#define  LED_FLOW       5 //MULTI LED FUNCTION SCANS ACROSS THE LEDS IN A LINE
#define  LED_ALTERNATE  6 //ALTERNATE THE PRIMARY AND SECONDARY COLOURS


//Used to group LEDs for specific tasks and associated values
  class LEDModule{
    private:
    //Used for singling out the modules led from the array
    uint8_t indexStart; //First index of module inside the CRGB array
    uint8_t indexEnd;   //Last index of module inside CRGB array

    //Used for time based calculations for different LED modes.
    uint16_t timer;     //Last call to the coolDown function
    uint16_t interval;  //Time to complete one cycle
    uint8_t onTimePrecent; //Determines the precentage of the cylce for the led to be on

    //Colours associated with this LED
    unsigned long currentRGB; //The current colour of the LED

    unsigned long primaryRGB; //This shouldn't change
    unsigned long secondaryRGB; //This shouldn't change
    uint8_t currentMode;
    public: 
    /**
    * Constructor
    */
    LEDModule(uint8_t indexStart, uint8_t numberOfLights, unsigned long primaryRGB, uint16_t interval);
    LEDModule(uint8_t indexStart, uint8_t numberOfLights, unsigned long primaryRGB);
    /**
     * Sets the Mode of the LED, currently supported modes:
     * @param newMode OFF, STEADY, BLINK, FADE, PULSE, FLOW, ALTERNATE
     */
    void setMode(uint8_t newMode);
    /**
     * Sets the current colour, doesn't overwrite the primary colours. 
     */
    void setColour(unsigned long newColour);
    /**
    * Does upkeep on the module, needs to be run before the data flush of FastLED.show();
    */
    void updateModule(CRGB Leds);

    /**
     * Does the math to determine flow state
     * 
     * impulse at t*(n-1)/n where the impulse cycles through each led and t is the time interval of the speed of the row
     * n = indexEnd - indexStart
     * t = time of impulse
     * 
     * A better example may be to check the shortTime against timer where the cool down is (n-1)/n*interval
     * 
     */
    void flowHandler(unsigned long time);
    /**
     * 
     */
    void adjustBrightness(uint8_t index, uint8_t brightness);
  };


#endif