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

  #include <DFPlayerMini.h>
  #include <SoftwareSerial.h>

  //PinOut
  const uint8_t RX = 0;
  const uint8_t TX = 1;
  //const uint8_t  = ;
  //const uint8_t  = ;
  //const uint8_t  = ;
  //const uint8_t  = ;
  //const uint8_t  = ;
  //const uint8_t  = ;
  //const uint8_t  = ;
  //const uint8_t  = ;
  //const uint8_t  = ;
  //const uint8_t  = ;
  const uint8_t SCK_OUT = 13;

  void setup(){
    Serial.begin(115200); 
    while(!Serial){}
    Serial.println("\nBegin FX Controller\n");
  }

  void loop(){
    
  }

//--------------------------------------------------------------
//      Audio    (NO CURRENT PROJECTS)
//--------------------------------------------------------------
  /**
    Plays Audio and returns the duration of the audio
    @param type AUDIO_SFX or AUDIO_MUSIC (0 or 1)
    @param audioFile The defined macro of the audiofile
    @param duration !IGNORE! included in the definition macro of the audio file
    @return duration the song will play for in ms
  */
  long playAudio(uint8_t type, uint8_t audioFile, long duration){
    switch(type){
      case AUDIO_SFX:
        soundFX.playFile(audioFile);
        break;
      case AUDIO_MUSIC:
        music.playFile(audioFile);
        break;
    }
    return duration; 
  }