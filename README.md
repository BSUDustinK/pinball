# Arduino Pinball Machine

A base framework for quickly protyping game loops and external modules for a home made pinball machine. 

## Description (Physical)
The pinball machine is a 2'x1'x1/2" whitewood board with a sinlge flipper and a catapult near the bottom. The catapult is a false wall across from the flipper with a solenoid to bounce the ball away. The flipper is a bat like paddle that can be engaged and smacks the ball away. 

I have chosen this set up due to the narrow width of the pinball machine, this allows me to keep all the targets and shots withing a wider field and focus on the flow of the ball and the paths it can take back to the flipper. 

I have also added a drop down target in the form of a ball trap to allow for a multiball game mode. Upon qualifying the ball lock, you will be able to trap a ball behind the target, than knock it back down to release the ball starting a fast paced game mode. 

I plan to add three targets that rise out from the play field. 

I also plan to add a bumper like target to the playfield. This will be a solenoid powered bumper that will kick the ball chaotically away. Atop this bumper, I intend to create a small animitronic model who will shake and bounce with the bumper. 

## Description (Circuits)
There are many circuits being used to create several effects across the pinball machine. One of my goals was to make the circuits modular, and where possible, make them self managing. This is especially noticable with the LED effects. 

#### Roll Over Sensors

These are linear Hall effect sensors with a magnet affixed at a distance from the hall effect sensor, giving the sensor a magnetic field to pick up. As the ferous pinball gets near, the magnetic field shifts in response. The sensor signal voltage is sent to a comparator with a tuned potentiometer for adjusting the specific sensitivity of each sensor. These sensors than have another circuit that is optional. It allows the circuit to be connected to an LED flash circuit causing a light to flash as the ball rolls over the sensor without needing input from the CPU. 

#### Flash circuit

This is a simple LED flash circuit that causes an initial burst of light, but dims slowly. This uses an RC circuit with a transistor to allow for a more linear dimming of the LED.

#### LED Status Bar

This is used to display the charge during the Nightsoul game mode. It is a LED bar guage display connected to a decoder. Sending a signal to the decoder will let me cycle through 16 modes, 0...10 are off to fully on, while 11 and on are various patterns flashing or paterns that I have built circuits for. 

#### Expaded Interupt Signal using Priority Encoder
This is a SN74LS148N Encoder Chip which is wired to take the sensors on the playfield that require an interupt but are not critical. It sends data back to the controller over a three bit bus. THIS NEEDS TO BE HANDLED AT THE TIME OF CAPTURE. Extending the impulses from the sensors is not an option due to the chip overwriting lower priotity inputs. I have considered latching data as it comes in than having a counter clear the latches as the controller reads each interupt. I may continue to work on that design. 


## Description (Program)
While programming my goal was to make the base very versatile and reusable. 
My main principles I followed while designing the code was:
- Linear time complexity for all actions while the game is active
- Build with expansion in mind, with this I tried to keep methods simple and self contained.
- Expandability, to be able to add more and more onto the system as a need arises without having to make large edits to the code base


## Outcome
This project is mostly a combination of experiements and implimenting what I have been learning in my Computer Systems Engineering coursework as well as my own interests in the field. The goal is to apply what I am learning to a fun and physically responsive system. 

I do have plans to take what I learn from this project and expand it to a full sized pinball machine. 

### What this project has taught me
- I have become vary familiar with the C and C++ language reading from Applications Programming in ANSI C. [^1]
- I have familiarized myself with AutoCAD for the purpose of designing the solenoid harnass, flipper mechanism, and catapult. 
- I have learned about hardware interupts, and have set out to find unique ways to expand the Arduino's limited interupt pins. I accomplished this with a priority encoder for less critical interupts.
- I have spent a good deal of time researching and readiong technical documentation regarding integrated circuits, circuit modules, and how to communicate via serial data. 

## TODOs
- [] Complete base hardware tasks 
- [] Program Interupt Handler for encoder, drain, and flipper button
- [] Program Ball Launch, flipper, drop target, and catapult controls


#### Reference list entry:
[^1]: Johnsonbaugh, R., & Kalin, M. (1996). Applications programming in ANSI C (3rd ed.). Pearson. 