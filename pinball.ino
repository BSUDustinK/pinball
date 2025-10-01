/**
  Pinball Script for Arduino
  @author Dustin Kirkpatrick
  @version v0.01-alpha
  @since 2025-09-20

  This project seeks to create an easily expandable pinball game system.

  The project currently has: 
  - Dual audio output control for music and soundFX to be played simultaniously
  - Encoder based expansion of interupt pins, allowing for more interupts for on playfield targets 
  (fast contact switches that are likely to be miss if polled)
  - Makes use of the Arduino Mega 2560on board EEPROM to save high scored. This may be replaced with a better chip in the future

  The project is planned to have:
  - LED control, either addressed serially, or Multiplexed
  - A 20 x 80 Dot Matrix Display, I plan on using a seperate Nano to control the DMD and the animations. 
  
*/

//----------------------------------------------
// Includes
//----------------------------------------------
  //External include
  #include <EEPROM.h>
  #include <DFPlayerMini.h>
  #include <Servo.h>
  #include <SoftwareSerial.h>
  #include <string.h>

  //My includes (Make sure these files are in the same directory as this file)
  #include "CoolDown.h"
  #include "audioFiles.h"
  #include "pinout.h"
  #include "DropDown.h"

  #include "pinball.h"
//----------------------------------------------
// Variables
//----------------------------------------------

  //### Device Variables
  DFPlayerMini soundFX;
  DFPlayerMini music;
  Servo ballLoader;
  DropDown ddTarget;

  //### State Flags
  volatile uint16_t flagRegister; // Multiple flags stored in the bit 0x-0000-0000-0000-0000
  volatile uint8_t gameMode;

  //### Timers
  unsigned long currentTime;
  unsigned long musicTimer, soundFXTimer; 
  unsigned long loadTimer, launchTimer, flipperTimer, catapultTimer;

  //### Game Values
  volatile unsigned long currentScore;
  uint8_t credits;
  uint8_t ballsLeft, ballsInPlay, ballsPerGame;


  //### Custom Classes and Structs

  //This stores the top three high scores and the initials associated with them
  struct highScore{
    char initials[4];   //Needs to be 4 for String conversion exit point '\0' or something like that
    unsigned long score;
    String toString(){
      return (String)initials + " Score: " + score;
    }
  };
  highScore topScores[3];     //<< Consider expanding this 
  
//----------------------------------------------
//  Constant Config Values, replace with define's 
//----------------------------------------------
  const bool DEBUG = true;

//----------------------------------------------
//  Code Begin
//----------------------------------------------
  //Initialize pinball machine
  void setup() {
    if(DEBUG){ 
      Serial.begin(9600); 
      while(!Serial){}
      Serial.println("\n### BEGIN RUN ###\n");
    }
    //## Change these to customize your machine ##
    credits = 0;                    //Initial credits on startup
    ballsPerGame = 3;
    currentTime = millis();
    pinMode(PIN_SERVO_ENABLE, OUTPUT);
    digitalWrite(PIN_SERVO_ENABLE,HIGH);

    //### Loads High Scores   <<<<< KEEP COMMENTED UNTIL DEPLOYMENT. EEPROM HAS 100,000 read/write ops.
    //topScores[0] = EEPROM.get(0,topScores[0]);
    //topScores[1] = EEPROM.get(10,topScores[1]);
    //topScores[2] = EEPROM.get(20,topScores[2]);
    //delay(200);  

    //if(DEBUG){ Serial.println("\nFinished Loading Highscores: \n");
    //if(DEBUG){ Serial.println(topScores[0].toString());
    //if(DEBUG){ Serial.println(topScores[1].toString());
    //if(DEBUG){ Serial.println(topScores[2].toString());

    //## Hardware Setup ##
    //Set up Servos

    //COMPLETE CODE
    ballLoader.attach(PIN_SERVO_LOAD);
    ballLoader.write(60); //Set to down state, this will need to be customized for your configuration 

    ddTarget.setUp(PIN_SERVO_DDTARGET, PIN_POLL_DDTARGET); 
    ddTarget.calibrate(); //Sets up drop target
    ddTarget.setMode(3); //TODO for showing off set to 0 for actual gameplay

    if(DEBUG){ Serial.println("\nFinished Servo SetUP\n"); }


    



    /*IMPORTANT,
      ddTarget must detach before sending Serial data to sound boards. 
      I think it has something to do with the internal timer interupts but couldn't find anything 
    */
    //## Set up Audio ##
    disableServos();
    music.init(PIN_MUSIC_BUSY, PIN_MUSIC_RX, PIN_MUSIC_TX);
    soundFX.init(PIN_SE_BUSY, PIN_SE_RX, PIN_SE_TX);
    delay(200);
    music.setVolume(26);
    soundFX.setVolume(30);
    music.setVolume(2); //TODO Delete when not testing no more
    soundFX.setVolume(2); //TODO Delete when not testing no more
    if(DEBUG){ Serial.println("\nmusic\n"); }

    enableServos();

    if(DEBUG){ Serial.println("\nFinished Audio SetUP\n"); }

  }

  //Main Loop
  void loop() {


    //while(true){
    //  disableServos();
    //  delay(1000);
    //  enableServos();
    //  delay(1000);
    //}



    currentTime = millis();
    gameMode = attractMode();  //Loops until game starts
    switch(gameMode){
      case 1:
      break;
      case 2:
      break;
      default:;
    } 
    //TODO displayLastGameScore();
    //TODO readyNewGame();
  }

//--------------------------------------------------------------
//      Score Keeping Methods 
//--------------------------------------------------------------
  /**
    Resets the Highscores and updates the EEPROM to clear old high scores
  */
  void resetHighScores(){
    topScores[0] = highScore{.initials = {'K','I','N'}, .score = 180000};
    topScores[1] = highScore{.initials = {'I','F','A'}, .score = 100000};
    topScores[2] = highScore{.initials = {'A','J','W'}, .score = 80000};
    putScoresInEEPROM();
  }

  /**
    Check 's score and begins user input for recording initials
    @param gameScore Score of game to check against top 3
    @return 0: Not top score, 1: New top score, 2: second top score, 3: third top score

  */
  void registerScore(unsigned long lastGameScore){
    if(lastGameScore > topScores[2].score){
      highScore newScore = highScore{.initials = {'E','R','R'}, .score = lastGameScore};

      //TODO get input
      //for(uint8_t i; i<3;i++){
      //  newScore.initials[i] = promptForChar(uint8_t i);
      //}
      
      newScore.initials[0] = 'N'; //TODO REMOVE
      newScore.initials[1] = 'E'; //TODO REMOVE
      newScore.initials[2] = 'W'; //TODO REMOVE

      if(DEBUG){ Serial.println("\n - Adding: "+newScore.toString()+"\n"); }
      char result = updateTopScores(newScore);
      putScoresInEEPROM();

      //TODO add animation for result of placing on the high scores

    }
  }
  char updateTopScores(highScore newScore){
    for(uint8_t i=0;i<3;i++){
      if(newScore.score > topScores[i].score){
        highScore temp = topScores[i];
        topScores[i] = newScore;
        if(i<2){ updateTopScores(temp); }   //Don't run operation for last element
        return i;
      }
    }
    return 0;
  }

  /**
    Updates the EEPROM, only call when nessicary
    TODO Change when hardware needs change
  */
  void putScoresInEEPROM(){
    EEPROM.put(0, topScores[0]);
    EEPROM.put(10, topScores[1]);
    EEPROM.put(20, topScores[2]);
    if(DEBUG){ 
      Serial.println("\nEEPROM UPDATED: SCORES\nUpdated values are: ");
      Serial.println(topScores[0].toString());
      Serial.println(topScores[1].toString());
      Serial.println(topScores[2].toString()); 
    }
  }

//--------------------------------------------------------------
//      GAME LOOPS      
//  TODO: Add mainGameLoop, bossfight, multiball, nightsoul skill mode, set up mode (Req display) 
//--------------------------------------------------------------

  /**
    The Attract attention/ idle mode. 
    Play ambient audio at a reduced volume. 
    Do wave like LED patterns

    Wait for player input: Credits(Coins), Start button(Start game if enough credits), Flipper button(Cycle High Scores, game modes)

    Options, Start long press, go to options

  */
  char attractMode(){
    //Initialize Attract mode
    char selection = 0;
    uint8_t music_track = 0;
    long musicDelay = 0;
    long sfxDelay = 0;

    while(selection == 0){
      currentTime = millis();
      pollSensors();

      //Plays music
      if(!music.isBusy() && coolDownComplete(currentTime, &musicTimer, musicDelay)){
        switch(music_track){
          case 0:
            musicDelay = playAudio(MUS_IDLE_1) + 200000;
            break;
          case 1:
            musicDelay = playAudio(MUS_IDLE_2) + 200000;
            break;
          case 2:
            musicDelay = playAudio(MUS_IDLE_3) + 200000;
            break;
          case 3:
            musicDelay = playAudio(MUS_IDLE_4) + 200000;
            break;
        }

        music_track++;
        music_track %= 4;
      }

      //Plays SoundXF
      if(!soundFX.isBusy() && coolDownComplete(currentTime, &soundFXTimer, sfxDelay)){
        sfxDelay = playAudio(SFX_IDLE) ;// + 412000;
      }
    }



    return selection;
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
    disableServos();
    switch(type){
      case AUDIO_SFX:
        soundFX.playFile(audioFile);
        break;
      case AUDIO_MUSIC:
        music.playFile(audioFile);
        break;
    }
    enableServos();
    return duration; 
  }
//--------------------------------------------------------------
//      Devices      
//  TODO: Add flipper, catapult, & ball launcher
//--------------------------------------------------------------
  //-TODO Complete this
  //Ball Launch Mech
  //Loads a ball to be launched
  void loadBall(){
    ballLoader.write(168);
    while(false){
      checkHardware(); 
    }
  }
  //Updates ball launch timer
  void checkHardware(){
    //Checks Servo for Ball Launcher
    if(ballLoader.read() > 60){
      if(coolDownComplete(currentTime, &loadTimer, 300)){
        ballLoader.write(60);
      }
    }
    if(FLAG_SOL_LAUNCH_ACTIVE){
      if(coolDownComplete(currentTime, &launchTimer, 300)){
        digitalWrite(PIN_LAUNCHER, LOW);
        flagRegister &= ~(0x01);
      }
    }
  }

  void launchBall(){

  }

  //This doesn't seem to help with the weird flickering with the Audio Serial commands. 
  void disableServos(){
    //digitalWrite(PIN_SERVO_ENABLE,HIGH);
    ddTarget.detach();
    delay(150);
  }
  void enableServos(){
    delay(150);
    ddTarget.attach();
    //digitalWrite(PIN_SERVO_ENABLE,LOW);
  }
//---------------------------------------------------------------
//     Sensor readouts & interupt handlers
//---------------------------------------------------------------

  //Time Sensitive function that checks polled sensors and hardware
  void pollSensors(){
    ddTarget.poll(currentTime); //Does Check up on Drop Down Target
    checkHardware();
  }

  //Handles the encoded interupt signal
  void muxInterupt(){
    uint8_t muxReadout = 
    digitalRead(PIN_ENCODER_ADR_1) + 
    digitalRead(PIN_ENCODER_ADR_2) *2+ 
    digitalRead(PIN_ENCODER_ADR_4) *4;
    switch(muxReadout){
      case 0:
      break;
      case 1:
      break;
      case 2:
      break;
      case 3:
      break;
      case 4:
      break;
      case 5:
      break;
      case 6:
      break;
      case 7:
      break;
      default:;
    }
  }




