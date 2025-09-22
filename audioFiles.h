
//technically not needed but I like the way it looks
#define AUDIO_SFX 0
#define AUDIO_MUSIC 1

/**
  SDCard File Definitions for DFPlayers.
  @author Dustin Kirkpatrick

  File format in the SD card is as follows:
    SD:\mp3 {
      001Audio1
      002Audio2
      ...
      999Audio999
    }

  Definition structure is as follows: 

  #define (Name) [0 if SFX/1 if MUSIC],[Audio #],[duration in milliseconds]
    name is the macro that will be replaced by the values
    0 or 1 identifies which SD card is being called SFX or MUSIC
    Audio # corresponds to the number prefix of the audio name, more specifically its location in the directory
    Duration is the length of the song. This is what is returned when the playAudio() function is called
*/

// The reason I am choosing to use precompile operations instead of structs to store the music data
// is to help save on variable memory. 


//####  Sound Effects  ####
#define SFX_IDLE 0,1,7500
#define SFX_GAMESTART 0,2,6000

#define SFX_JACKPOT 0,3,0
#define SFX_EXTRABALL 0,4,10000
#define SFX_LASTBALL 0,5,11000
#define SFX_BALLSAVE 0,6,3000
#define SFX_LOW_LIFE 0,7,4000

#define SFX_BALLLOCK_QUALIFIED 0,8,2000
#define SFX_BALL_LOCKED 0,9,2000

#define SFX_BALL_LOCKED_ALT 0,10,5000

#define SFX_NS_QUALIFY 0,11,3000       //NS NIGHT SOUL BLESSING STATE
#define SFX_NS_BEGIN 0,12,4000
#define SFX_FG_BEGIN 0,13,3000       //FG FLAME GRANETTE STATE
#define SFX_FG_HURRY 0,14,3000
#define SFX_AIM_YUM 0,15,2000

#define SFX_AIM_RIGHTORB 0,16,2000
#define SFX_AIM_LEFTORB 0,17,2000
#define SFX_AIM_LEFTORB_ALT 0,18,2000

//####  Music and BackGround  ####

#define MUS_LAUNCH 1,1,255000      //Should fade low after Skill Shot 4:11

#define MUS_BOSSFIGHT 1,2,   //Fight mode        4:18
#define MUS_HARDFIGHT 1,3,   //Hard Fight mode   3:43
#define MUS_MULTIBALL 1,4,   //Duration:         1:35

#define MUS_IDLE_1 1,5,103000         //1:43
#define MUS_IDLE_2 1,6,79000          //1:19
#define MUS_IDLE_3 1,7,92000          //1:32
#define MUS_IDLE_4 1,8,97000          //1:37

