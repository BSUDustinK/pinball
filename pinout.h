/**
  Pin Out definitions for Arduino board
  @author Dustin Kirkpatrick
  @version v0.01-alpha
  @since 2025-09-20

  Customize these to your board, refer to your manufacture's pin guide for PWM and interupt capable pins

  Current Configuration is for Arduino Mega2560

  Known issues:
    Audio pins are interfering with PWM functionallity. I believe this is due to an internal timer interupt conflict between 
    the PWM function and the Serial Comm used by the DFPlayerMini library. 
*/

//#### Communication ####

//Music and Sound Effect
#define PIN_SE_TX 53
#define PIN_SE_RX 51
#define PIN_SE_BUSY 49

#define PIN_MUSIC_TX 52
#define PIN_MUSIC_RX 50
#define PIN_MUSIC_BUSY 48


//DMD Figure this out
#define PIN_DMD_TX 16
#define PIN_DMD_RX 17
#define PIN_DMD_CS_TOP 
#define PIN_DMD_CS_BOTTOM

//####  Inputs  ####

//Polled Sensors


//Interupt, ordered in priority required
#define PIN_INT_DRAIN
#define PIN_SIDEBUTTON
#define PIN_ENCODER_TRIGGER 11   // Needs interupt, calls mux interupt handler CHANGE LATER

//Interupt Expansion Using Encoder

#define PIN_ENCODER_ADR_1 30  // Polled in interupt handler
#define PIN_ENCODER_ADR_2 31  // ^
#define PIN_ENCODER_ADR_4 32  // ^

//Polled Inputs 
#define PIN_POLL_DDTARGET 22    //TODO replace 22
#define PIN_FRONTBUTTON   23    // Polled Value

//#### Outputs ####



//24V Mosfet Chip
#define PIN_SLING     41
#define PIN_FLIPPER     //NEEDS PWM
#define PIN_LAUNCHER  40 
#define PIN_POPBUMPER 42

//Needs PWM
#define PIN_SERVO_ENABLE 46     //TODO temporary while debugging audio comm interference with PWM function

#define PIN_SERVO_DDTARGET 3    //TODO determine better PWM pins
#define PIN_SERVO_LOAD 4        //TODO determine better PWM pins


//LED Multiplexer
#define MUX_ADDR_1
#define MUX_ADDR_2
#define MUX_ADDR_4
#define MUX_ADDR_8