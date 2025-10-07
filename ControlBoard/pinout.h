/**
  Pin Out definitions for Arduino board
  @author Dustin Kirkpatrick
  @version v0.01-alpha
  @since 2025-09-20

  Customize these to your board, refer to your manufacture's pin guide for PWM and interupt capable pins

  Current Configuration is for Arduino Mega2560

  //Comm Pins
    0(RX), 1(TX),	--> Audio/ DMD controller

    17(RX2), 16(TX2)	15(RX3), 14(TX3)

    19(RX1), 18(TX1) ALSO INTERUPTS, DO NOT USE FOR SERIAL

  // PWM
    4-13
    44-46

    2,3 ALSO INTERUPT DO NOT USE FOR PWM
  
  // Interupt Pins 
    2,3,  18,19,20,21
  
  //Analog 
  54(A0) - 69(A15)

  Known issues:
    Audio pins are interfering with PWM functionallity. I believe this is due to an internal timer interupt conflict between 
    the PWM function and the Serial Comm used by the DFPlayerMini library. 
*/

//#### Communication ####
//Here for refrence, the Serial class defaults to these
#define PIN_FX_RX 0
#define PIN_FX_TX 1

//####  Inputs  ####

//Polled Sensors

#define PIN_HALL_LAUNCHER 69  //analog

//Interupt, 2, 3, 18, 19, 20, 21
#define PIN_CATAPULT_TRIGGER 21   
#define PIN_ROLLOVER_LEFT_LANE 18
#define PIN_SIDEBUTTON 20
#define PIN_ROLLOVER_DRAIN 19

#define PIN_MUX_TRIGGER 2

//Interupt Expansion Using Encoder

#define PIN_ENCODER_ADR_1 30  // Polled in interupt handler
#define PIN_ENCODER_ADR_2 31  // ^
#define PIN_ENCODER_ADR_4 32  // ^


//Polled Inputs 
#define PIN_POLL_DDTARGET 22  //On Pin(PULL-UP) -> switch -> GND  //TODO replace 22
#define PIN_FRONTBUTTON   53    // Polled Value

//#### Outputs ####


//24V Mosfet Chip  PWM 44-46
#define PIN_LAUNCHER  41 
#define PIN_POPBUMPER 42
#define PIN_SLING     43
#define PIN_FLIPPER   44  //NEEDS PWM

//Needs PWM
#define PIN_SERVO_DDTARGET 3    //TODO determine better PWM pins
#define PIN_SERVO_LOAD 4        //TODO determine better PWM pins


//LED Multiplexer
#define MUX_ADDR_1
#define MUX_ADDR_2
#define MUX_ADDR_4
#define MUX_ADDR_8