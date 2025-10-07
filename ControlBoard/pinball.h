/**
  Pinball Script for Arduino
  @author Dustin Kirkpatrick
  @version v0.01-alpha
  @since 2025-09-20

  This project seeks to create an easily expandable pinball game system.

  The project offers: 
  - Dual audio channel control for music and soundFX to be played simultaniously
  - Encoder based expansion of  interupt pins, allowing for more interupts for on playfield targets
  - Multiplexer LED control (I may rework this in the future)
  - TODO DMD display support from an external Arduino Nano 

  To build your own games, use the 
*/


//Flags flagRegister 0x-0000-0000 - 0000-0000
//                      ^Sensors^   ^Hardware^

//Device actions
  // 0 
    #define FLAG_SOL_LAUNCH_ACTIVE (flagRegister%2==1)
  // 1
    #define FLAG_SOL_FLIPPER_ACTIVE ((flagRegister<<1)%2==1)
  // 2
    #define FLAG_SOL_CATAPULT ((flagRegister<<2)%2==1)
  // 3
    #define FLAG_SOL_POPBUMPER_ACTIVE ((flagRegister<<3)%2==1)
  // 4
    #define FLAG_SERVO_LOAD_ACTIVE ((flagRegister<<4)%2==1)
  // 5

  // 6

  // 7

//Sensor Readout
  // 8
    #define FLAG_MUX_DDTARGET ((flagRegister<<8)%2==1)
  // 9
    #define FLAG_MUX_CATAPULT ((flagRegister<<9)%2==1)
  // 10
    #define FLAG_MUX_ ((flagRegister<<10)%2==1)
  // 11
    #define FLAG_MUX_ ((flagRegister<<11)%2==1)
  // 12
    #define FLAG_MUX_LANEFRONT_L ((flagRegister<<12)%2==1)
  // 13
    #define FLAG_MUX_LANEFRONT_R ((flagRegister<<13)%2==1)
  // 14
    #define FLAG_MUX_REARLANE_L ((flagRegister<<14)%2==1)
  // 15
    #define FLAG_MUX_REARLANE_R ((flagRegister<<15)%2==1)


