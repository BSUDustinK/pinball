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

  DFPlayerMini soundFX;
  DFPlayerMini music;

  //Definitions for readability
  #define AUDIO_SFX 0
  #define AUDIO_MUSIC 1

  /**
    Current setup is for Arduino Nano, customize to your needs
  */
  //Pin Out
  #define PIN_MUSIC_RX 11
  #define PIN_MUSIC_TX 12
  #define PIN_MUSIC_BUSY 10
  #define PIN_SE_RX 8
  #define PIN_SE_TX 9
  #define PIN_SE_BUSY 7

  //Settings: (TODO: TESTING, Change before deployment)
  const uint8_t MAX_VOLUME = 3;

  void setup(){
    Serial.begin(115200); 
    while(!Serial){}
    Serial.println("\n\n###\t\tBEGIN FX\t\t###");
    music.init(PIN_MUSIC_BUSY, PIN_MUSIC_TX, PIN_MUSIC_RX);
    soundFX.init(PIN_SE_BUSY, PIN_SE_TX, PIN_SE_RX);
    music.setVolume(MAX_VOLUME*(3/4));
    soundFX.setVolume(MAX_VOLUME);
  }
   
  void loop(){
    //Process Command
    if(Serial.available() > 0){
      Serial.println("Input taken");
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
    Serial.println("Parsed the value: \""+token+"\"\n");
    return token;
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