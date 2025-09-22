/**
  Pinball
  @author Dustin Kirkpatrick
  @version v1.0
  @since 2025-09-19
*/


/**
  coolDown
  Used to track cooldowns
  @param initialTime A pointer to the timer for the desired module
  @param duration The length in Milliseconds that the operation will wait before operating again
  @return True if a timer was created or a previous timer has finished
*/
bool coolDown(long* initialTime, long duration);

//Flags flagRegister 0b-0000-0000-0000-0000
// 0

// 1

// 2

// 3

// 4

// 5

// 6

// 7

// 8

// 9

// 10

// 11

// 12

// 13

// 14

// 15
  //Regarding the accuracy of the EEPROM (Don't use)
  #define FLAG_CHECK_EEPROM (flagRegister>>15) % 2
  #define FLAG_SET_EEPROM flagRegister |= (0x1 << 15)    
  #define FLAG_RESET_EEPROM flagRegister &= ~(0x1 << 15)  