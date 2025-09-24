/**
  Pin Out definitions for Arduino board
  @author Dustin Kirkpatrick
  @version v0.01-alpha
  @since 2025-09-20

  Customize these to your board, refer to your manufacture's pin guide for PWM and interupt capable pins

  Current Configuration is for Arduino Mega2560
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

//Player control
#define PIN_SIDEBUTTON        //Needs interupt
#define PIN_FRONTBUTTON

//Interupt Expansion Using Encoder
#define PIN_ENCODER_TRIGGER   //Needs interupt
#define PIN_ENCODER_ADR_1
#define PIN_ENCODER_ADR_2
#define PIN_ENCODER_ADR_4

//Polled Inputs //TODO replace 22
#define PIN_POLL_DDTARGET 22 


//#### Outputs ####

//24V Mosfet Chip
#define PIN_SLING
#define PIN_FLIPPER
#define PIN_LAUNCHER
#define PIN_POPBUMPER

//Needs PWM
#define PIN_SERVO_DDTARGET 3
#define PIN_SERVO_LOAD 4


//LED Multiplexer
#define MUX_ADDR_1
#define MUX_ADDR_2
#define MUX_ADDR_4
#define MUX_ADDR_8