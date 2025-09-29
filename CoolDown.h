#ifndef COOLDOWN
#define COOLDOWN

/**
    Used to track cooldowns
    @param currentTime The current value of millis() This will need to be stored in your maintenence loop
    @param initialTime A pointer to the timer for the desired module
    @param duration The length in Milliseconds that the operation will wait before operating again
    @return True if a timer was created or a previous timer has finished
  */
  bool coolDownComplete(unsigned long currentTime,unsigned long * initialTime, long duration);

#endif