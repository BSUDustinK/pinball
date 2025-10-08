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

*/

//#### Communication ####
//Here for refrence, the Serial class defaults to these
const uint8_t  PIN_FX_RX = 0;
const uint8_t  PIN_FX_TX = 1;

//####  Inputs  ####

//Polled Sensors
const uint8_t  PIN_HALL_LAUNCHER = 69;  //analog
const uint8_t  PIN_FRONTBUTTON   = 53;   
const uint8_t  PIN_POLL_DDTARGET = 22;

//Interupt, 2, 3, 18, 19, 20, 21
const uint8_t  PIN_CATAPULT_TRIGGER   = 21;   
const uint8_t  PIN_SIDEBUTTON         = 20;
const uint8_t  PIN_ROLLOVER_DRAIN     = 19;
const uint8_t  PIN_ROLLOVER_LEFT_LANE = 18;

const uint8_t  PIN_MUX_TRIGGER  = 2;

//Interupt Expansion Using Encoder (Polled in interupt handler)
const uint8_t  PIN_ENCODER_ADR_1 = 30;   
const uint8_t  PIN_ENCODER_ADR_2 = 31;  
const uint8_t  PIN_ENCODER_ADR_4 = 32;  

//#### Outputs ####
//24V Mosfet Chip  PWM 44-46
const uint8_t  PIN_LAUNCHER  = 41; 
const uint8_t  PIN_POPBUMPER = 42;
const uint8_t  PIN_SLING     = 43;
const uint8_t  PIN_FLIPPER   = 44;  //NEEDS PWM

//Needs PWM
const uint8_t  PIN_SERVO_DDTARGET = 3;    //TODO determine better PWM pins
const uint8_t  PIN_SERVO_LOAD = 4;        //TODO determine better PWM pins


//LED Multiplexer
//const uint8_t  MUX_ADDR_1 = NULL;
//const uint8_t  MUX_ADDR_2 = NULL;
//const uint8_t  MUX_ADDR_4 = NULL;
//const uint8_t  MUX_ADDR_8 = NULL;


