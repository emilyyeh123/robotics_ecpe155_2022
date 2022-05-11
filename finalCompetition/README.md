# Final Competition Documentation

## Project Overview
The purpose of this project was to create an autonomous robot that could navigate a maze from a start to an end location. The robot would accomplish this using a Tiva TM4C123GH6PMI microcontroller to drive robot behavior. The available behaviors are toggled using a Raspberry Pi, Version 3.

## Robot Bahavioral Controls
There are several behaviors coded into the robot that can be controlled manually such as forward motion, turning, and returning IR range data.

Alternatively, the robot retains autonomous functions. These functons allow the robot to move forward, detect objects, and aid the Raspberry Pi image processing function to locate waypoints. Both autonomous and commanded motion are called by the [Trans_Reciever.c](Robot_Library/Trans_Reciever.c) and [Robot_Library/Trans_Reciever.h](Trans_Reciever.h) files located in the Robot_Library function library. These functions are described below:

  - Autonomous Function Descriptions:
    `AutoForward()`
    This function sets both wheel speeds at a static value to propel the robot forward. If the robot travels 0.5 meters, it will autonoatically stop and pass distance and angle data to the Raspberry Pi. Alternatively this function constantly checks the IR sensor data. If an object is detected in front of the robot, the robot will automatically stop and send distance and angle data to the Pi. In both cases, the robot remains in a stopped position and awaits further commands from the Raspberry Pi.
    
    `objectAvoid()`


## Robot Decision Controls
