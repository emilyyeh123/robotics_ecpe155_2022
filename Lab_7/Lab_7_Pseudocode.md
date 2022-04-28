# Lab 7
Design an approach to high-level, obstacle avoidance. This should take a destination as input and drive to that destination while avoiding any obstacles in its path. Once the robot reaches the destination, it should stop moving and wait for a new coordinate (so we should be able to repeat the process). Document your design through words and/or pictures. Your documentation should be complete such that I could take it and implement your design without asking you any questions.

## Pseudocode
This high-level object avoidence function will be added to the Tiva Motor Control source code in the Robot Library folder [Motor_Control.c](Robot_Library/Motor_Control.c) and [Motor_Control.h](Robot_Library/Motor_Control.h).

The robot will be given coordinates by the user. The initial pose will be assigned as {0,0,0} as described in Lab_6. The robot will orient itself towards the final destination and begin moving forwards, towards the destination. The bump and IR sensors will constantly be running for incoming obstacles. The object avoidence will be toggled on or off by the Raspberry Pi when the bump or IR sensors detect an object in it's path and pass the data to the Raspberry Pi, interrupting its current trajectory. The object avoidence function is anticipated to be as follows.

- Object Avoidence Pseudocode - Raspberry Pi has toggled object avoidence on
``` 
Do {determine which sensor has picked up an object}

while(1)
if(an IR sensor reads an object to the left right or behind){
  - back up a specified distance
  - rotate slightly away from obstacle to within a threshold sensor range
  - move forward and update location and range
  - continue rotating towards or away from the obstacle to keep it a specified distance
      - Compute the distance to the final pose
  if(the direction of the final pose is not obstructed) {
    - Re-orient the robot towards the final pose
    - Disable object avoidence and move forward towards the final pose
  }
}
```
There exists functions for simple object avoidence that move the robot backward a specified amount of ticks and then moves forward at a static rate. These functions will likely be included in the more sophisticated object avoidence function to orient the robot next to the object to be chased. It is proedicted that the challenges will be in controlling small robot motions, which call multiple simple motor functions, in an effective manner to navigate around the perimeter of an object while also updating its position.

It is proposed that a new function be created to mitigate this challenge.
- Fine motion object tracking psudeocode

```
while(1)

  getsensordata();
  
  if(sensordata > threshold & object is in the direction of final pose) {
   - move the robot towards the object surface (for this long) 
   - update robot orientation
  }
  
    if(sensordata < threshold & object is in the direction of final pose) {
   - move the robot away the object surface (for this long)
   - update robot orientation
  }
  
    if(sensordata == threshold & object is in the direction of final pose) {
   - keep moving forward (for this long)
   - update robot orientation
  }
  
    if(object is not in the direction of final pose) {
   - send signal to stop object avoidence to Pi and start navigating to final pose
   - update robot orientation
  }
  
  update position based on duration and orentation pass variables back to global navigation function.
  
```

This function will likely not be written into an interrupt because the timers needed to update position or the interrupts to resent the quadrature encoder-based counters will have difficulties as they are also interrupts. 

The global navigation function will also need to be updated to zero out the initial position once the destination has been reached and to call for more user input.

A potential challenge may be how to represent an error. If a wheel deviates from experimental expectations for a moment or something in the code breaks, how do we indicate an error has occured and how can we mitigate its effect on the system.



