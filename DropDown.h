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
      uint8_t switchPin;
      bool flag;
      void popUp();
      void raise();
      void drop();
    public:
      /**
      Constructor for DropDown target, calling this constructor will calibrate
      the device
      @param servoPin The PWM pin for the servo motor
      @param switchPin The polled pin for determining if the target is down
      @return DropDown target
      */
      DropDown(uint8_t servoPin, uint8_t switchPin);
      
      /**
        Sets the gate to open, allowing the gate to remain closed. This is used for trapping the ball
        ie: qualify ball lock
      */
      void enable();
      /**
        This turns the target into a simple target, not allowing the ball to get past
        ie: ball lock not available
      */
      void disable();
      /**
        lock is used to prevent the gate from opening, this is used when a ball is trapped
        ie: Force Gate Shut
      */
      void lock();
      /**
        Removes the lock
      */
      void unlock();
      /**
        Used in setup to establish nessicary bounds of the servo for desired output
      */
      void calibrate();
      /**
        Used within the game loop to check if a ball has been captured. 
        DOES NOT NEED AN INTERUPT!
        @return 0 if not hit or locked, 1 if hit and open, 2 if hit and closed
      */
      uint8_t poll();
  }; 
