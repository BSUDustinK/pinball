/**
  Drop Down Target Class
  @author Dustin Kirkpatrick
  @version v0.01-alpha
  @since 2025-09-24
  Used to define the Drop Down Target functionality
  Create an instance of a Drop Down and use the calibrate() method inside the setup() function in your main script
*/

//Add ifndef claus
/**
* Class: DropDown
* Constructor: (int servoPin, int switchPin)
* Methods: 
*   *runCheck(); updates position of dropTarget with respect to its 
*/
/**
  Drop Down Header Decleration
  Used for a drop down target
*/
class DropDown
  {
    private:
      Servo dropTarget;
      uint8_t targetHeight;
      uint8_t switchPin, servoPin;
      uint8_t flag;
      unsigned long timer, currentTime;
      void raise();
      void drop();
      void animate();
    public:
      /**
      Constructor for DropDown target, needs to be setUp and calibrated 
      */
      DropDown();
      /**
      Constructor for DropDown target, calling this constructor will calibrate
      the device
      @param servoPin The PWM pin for the servo motor
      @param switchPin The polled pin for determining if the target is down
      @return DropDown target
      */
      setUp(uint8_t servoPin, uint8_t switchPin);

      /**
        Used in setup to establish nessicary bounds of the servo for desired output
      */
      void calibrate();


      /**
        Used to change the behaviour of the device:
          0: Imediately pops back up 
          1: Stays down
          2: Stays up
          3: Moves the target back and forth, cannot detect hits.
        Three must be called after the drop down target is hit and the state prior is 1, Must Also have been calibrated
      */
      void setMode(uint8_t mode);
      /**
        Used within the game loop to check if a ball has been captured. 
        DOES NOT NEED AN INTERUPT!
        @return 0 if not hit, 1 if hit and open, 2 if hit and closed, 3 if hit and locked
      */
      uint8_t poll(unsigned long time);
      void attach();
      void detach();
  }; 
