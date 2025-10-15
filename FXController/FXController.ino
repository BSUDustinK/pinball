/**
  This is the assisting board for the Pinball Machine. This is the controller for heavy SPI and blocking communication. 

  These functions were moved out of the main board due to interferences with PWM functionallity.

  Objects managed by this device: 
    - Dot Matrix Display / Animations
    - SFX and Music Audio output 
    - SD card interfacing for Animation Frames 
  Inputs:
    SPI Comm from Master Controller
    Data In from SD cards

*/  
  
  
  #include <SoftwareSerial.h>

  #include <DFPlayerMini.h> 
  DFPlayerMini soundFX;
  DFPlayerMini music;

  #include <FastLED.h>
  #include "LEDModule.h"
  #define NUM_LEDS 49  //This needs to be adjusted to the number of leds on the line
  CRGB leds[NUM_LEDS]; //bit data shoved down the LED control line
  //Contains the values for the LED module for use with the various modes

  //ledModule LEDmodules[20]; 

  //Definitions for readability
  #define AUDIO_SFX 0
  #define AUDIO_MUSIC 1

  /**
    Current setup is for Arduino Nano, customize to your needs
  */
  //Pin Out
  #define PIN_MUSIC_RX 10
  #define PIN_MUSIC_TX 11
  #define PIN_MUSIC_BUSY 12

  #define PIN_SE_RX 7
  #define PIN_SE_TX 8
  #define PIN_SE_BUSY 9

  //PINOUT Audio Module {+, -, PIN_MUSIC_RX, PIN_MUSIC_TX, PIN_MUSIC_BUSY, ____, PIN_SE_RX, PIN_SE_TX, PIN_SE_BUSY}
    const uint8_t LED_DATA_PIN = 4;


  //Settings: (TODO: TESTING, Change before deployment)
    const uint8_t MAX_VOLUME = 4;


  //Timers
    unsigned long currentTime;

    uint16_t currentShortTime;

  void setup(){
    Serial.begin(115200); 
    while(!Serial){}

    FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NUM_LEDS); 
    
    Serial.println("\n\n###\t\tBEGIN FX\t\t###");
    music.init(NULL, PIN_MUSIC_TX, PIN_MUSIC_RX);
    soundFX.init(NULL, PIN_SE_TX, PIN_SE_RX);
    Serial.println("\n\n###\t\tfinished set up\t\t###");
    delay(50);
    music.setVolume(MAX_VOLUME - 2);
    delay(50);
    soundFX.setVolume(MAX_VOLUME);

  }

  void testLoop(){
    LEDModule module(0,49,0x06F0FF,300);
    module.setMode(LED_FLOW);

    while(true){

      //unsigned long R , G, B;
      //R=0;
      //G=0;
      //B=255;
      //leds[0] = 0x00FF08;
      //for(uint8_t i = 1; i<50; i++){
      //  //leds[i==1?49:i-1] = 0x000000;
      //  //leds[i] = 0x0FFF4F;
      //  //leds[i==49?1:i+1] = 0xFF0F0F;
      //  leds[i] = i%2==1?0x0FFF4F:0xFF0F0F;
      //}
      //delay(300);
      //FastLED.show();
      //for(uint8_t i = 1; i<50; i++){
      //  //leds[i==1?49:i-1] = 0x000000;
      //  //leds[i] = 0x0FFF4F;
      //  //leds[i==49?1:i+1] = 0xFF0F0F;
      //  leds[i] = i%2==0?0x0FFF4F:0xFF0F0F;
      //}
      ////delay(300);
      module.updateModule(leds);
      FastLED.show();
    }
  }
   
  void loop(){

    testLoop();


    //Process Command
    if(Serial.available() > 0){
      String command = Serial.readStringUntil('\n');  

      command.trim();
      if(command.charAt(command.length()-1) != ';'){
        command = command + ";";
      }

      uint8_t length = command.length();
      uint8_t tokens[length] ;
      
      String action = parseCommand(command, 0);
      int pointer = action.length()+1; 
      int i = 0;

      while(command.charAt(pointer -1) != ';'){
        String token = parseCommand(command, pointer);
        pointer += token.length()+1; 
        tokens[i] = token.toInt();
        i++;
      }
      if(action.equals("score")){

        //TODO impliment Score Keeping

      } else if(action.equals("audio")){
        
        playAudio(tokens[0], tokens[1]); 

      } else if(action.equals("animate")){

        //TODO impliment DMD

      }
    }
    //TODO updateDMD();
  }  

  String parseCommand(String command, int pointer){
    String token = "";
    uint8_t i = pointer;
    do{
      if(command.charAt(i) != ','){
        token = token + command.charAt(i);
        i++;
      }
    } while(command.charAt(i) != ',' && command.charAt(i) != ';' && i < command.length());
    return token;
  }
//--------------------------------------------------------------
//      LED Commands
//--------------------------------------------------------------
  //Define LED Behavior: These need to be placed in your calling device for ease of use


  void setLED(uint8_t targetLED, uint8_t mode, uint16_t interval){ //Interval must be less than 60 seconds
    
  }

  void updateLED(){

    FastLED.show(); // Update all of the LEDs by quickly pushing 24 * NUM_LEDS at a rate of 400 KHz 
  }

//--------------------------------------------------------------
//      Dot Matrix Display
//--------------------------------------------------------------
  void updateDMD(){
    //TODO finish implimentation
  }

//--------------------------------------------------------------
//      Audio 
//--------------------------------------------------------------
  /**
    Plays Audio
    @param type AUDIO_SFX or AUDIO_MUSIC (0 or 1, acts as chip select) 
    @param audioFile The defined macro of the audiofile
  */

  long playAudio(uint8_t type, uint8_t audioFile){
    switch(type){
      case AUDIO_SFX:
        soundFX.playFile(audioFile);
        break;
      case AUDIO_MUSIC:
        music.playFile(audioFile);
        break;
    } 
  }

  