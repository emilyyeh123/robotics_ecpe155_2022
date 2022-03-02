# Outline an approach to use for robot motor control such that you can define a position and have the robot reach it



## Quadrature Encoder (QE) Explanation & Implementation
- A quadrature encoder has 2 signals (in this case, QEA and QEB).
- The total number of QE ticks in each wheel is 128
  - This number is reduced to 64 if we are counting both edges, one signal
  - This number is reduced to 32 if we are counting a single edge, one signal
  - Reducing it to single edge would make position control less precise

In [interrupt.c](Robot_Library/interrupt.c), we created a QE interrupt handler to count each tick recieved by one signal (QEA) on both rising & falling edges.



## Measuring Displacement
- The number of ticks in one revolution is 64 with both edges, one signal
- The circumference of a circle is equal to 2 * pi * r
- The radius of each wheel is 3cm, so the circumference of each wheel is about 18.85cm

This means that the system moves about 18.85cm forward/backward in 64 ticks

*In the future, we want to implement velocity & ICR to test distance & movement, but for now we will simply account for distance to reach a specific destinations.
Velocity will require the use of timers.*



## Implementing Positioning
- Set count variables to 0 in initQEInterrupt function
- Modify Interrupt Handler:
  - Instead of flashing LED at every tick, display LED every time wheel has achieved one revolution.
    - if one revolution, reset count to 0 and display led; otherwise, continue incrementing count<br>
      ```
      if count > 63
        display led
        set count to 0
      else
        count++
      ```




