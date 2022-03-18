# General Approach for robot motor control to reach given positions

## Reference Material
- The TivaWare Peripheral Driver Library
  - Specifically Section 14 which covers GPIO pins and interrupts
  - The Tiva C Series TM4C123G LaunchPad Evaluation Board User's Guide
    - Specically Section 2.1.4 and 2.1.5 which helped map pins from the data sheet to the board

## Without the Quadrature Encoder (QE)
- Use the PWM function to set the wheels to a certain speed.
  - By default we use a period of 800 and low duty cycles (~200)
- Use the delay command to run the wheels a certain distance.
`SysCtlDelay(user-specified variable)` <br>
- Testing will need to be done to gauge the distance travelled at specific periods and duty-cycles.
- Consider the distance to be travelled and make adjustments to the time delays.

Challenges:
- The program could be adjusted to turn and go backwards but testing will need to take place to understand how much the robot will turn under different conditions.
- The program is clumsy and allows the robot to deviate from a straight path becuase individual wheel speeds vary.

## With the Quadrature Encoder (QE)
- A quadrature encoder has 2 signals (in this case, QEA and QEB).
- The total number of QE ticks in each wheel is 128
  - This number is reduced to 64 if we are counting both edges, one signal
  - This number is reduced to 32 if we are counting a single edge, one signal
  - Reducing it to single edge would make position control less precise
- For this Lab, only one of the two QE's will be used per wheel.

In [interrupt.c](Robot_Library/interrupt.c), we created a QE interrupt handler to count each tick recieved by one signal (QEA) on both rising & falling edges.

The Plan:
- The QE can now gauge distance by counting ticks. We can use this to move forward, backward, and turn a specific amount.
- The program can also be modified to correct the trajectory of the robot by adjusting wheel speed as the gap between counted ticks passes a threshold value.

Challenges:
- The initial speed of the robot must still be set manually. 
  - It would be interesting to develop code that can adjust speed based on the linear distance to be travelled.


## Measuring Distance
- The number of ticks in one revolution is 64 with both edges, one signal
- The circumference of a circle is equal to 2 * pi * r
- The radius of each wheel is 3cm, so the circumference of each wheel is about 18.85cm

This means that the system moves about 18.85cm forward/backward in 64 ticks, However, the rate at which each wheel turns under the same period and duty-cycle varies.

*In the future, we want to implement velocity & ICR to test distance & movement, but for now we will simply account for distance to reach a specific destinations.
Velocity will require the use of timers.*



## Quadrature Encoder Pseudocode
- initialize count variables to 0 in initQEInterrupt function. This will count the number of signals recieved from the QE.
- declare global variables to track the number of ticks counted on each wheel (initialize to 0 in initQEInterrupt)
  - reset the count anytime a new motion function is called. 
- Create a GPIO Interrupt Handler:
  - This interrupt will constantly count the number of ticks being counted
    - The distance travelled for each counted tick is known, so functions can be written to drive motion by tick number
    For Example:
    -Set the speed of each wheel and input a distance to be travelled <br>
      ```
      if count for left or right wheel > distance in ticks 
        { do something
          set all counts to 0
        } else
              count++
              
      ```
    - This same kind of logic can be extended to turning the robot, moving backwards, or correcting the individual wheel speeds
      ```
      if leftCount > rightCount + 5
        { Change the speed so that the right wheel speed increases
        }
      ```
      - with this, the robot could move in a rectangle with user-specified side lengths.
 *Currently, all functions are written using ticks. However, it is a team goal for the user to specify distances and have that number converted into a number of ticks.
 
 ## Emily's Idea to Create a function that takes in specific distance and stops robot at specified distance
    ```
    moveDist(int distance) // maybe make int 16 bits?
      fullRevs = distance/18.85 // defines the amount of full revolutions to move
      excessDistance = distance % 18.85 // defines excess distance
      excessRev = excessDistance*64 / 18.85 // multiply excess distance by 64 ticks and divide by circumference to get excess revolutions

      if(totalRev == fullRevs)
        if leftCount > excessRev && rightCount > excessRev
          stopmotor
    ```



