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
    This function allows the robot to avoid objects by turning the robot away from the object to the right by 90 degrees and then moving forward until the side sensors declare that the object has been cleared. (I wrote this whole section 30 minutes ago and my computer deleted all the text. I swear it looked better then...).
    
    `waypointSearch`
    This makes the robot turn 45 degrees, stops, and sends data to the Pi to update the robot's orientation.
    
    ### How it works
    The Tiva retains all the autonomous function in a switch/case code block. When the Tiva is initialized, it immediately runs code to await commands from the Pi. The Tiva will not perform any actions until a serial command is recieved.
    
    The Tiva expects an array of at least three distinct serial commands. These include:
    - An Initialization Command (0xAA)
    - A Function Command (some number ranging from 0x00 to 0x30)
    - A termination command (0x85)

If the intialization command is recieved, the Tiva will then match the second element of the array to the list of functions in the switch/case block. It is significant to note that any parameters that the function would need to run must be specified in subsequent elements of the communication array. Once the termination flag has been recieved, the Tiva will perform the given behavior. Once the behavior has been completed, the Tiva will compile a communication array to update the Pi on the task. This array will include:
    The Tiva expects an array of at least three distinct serial commands. These include:
    - An Initialization Command (0xAA)
    - Task Update (Task_Completed or Task_Failed)
    - A termination command (0x85)
    
Once the packet has been fully sent, the Tiva will enter a standby mode and wait for additional commands from the Pi. All behavior is commanded by the Pi and is carried out by the Tiva. When the Pi determines that the end goal has been met, the Pi will issue a command to terminate the program.

### Challenges
There were several major challenges with the current iteration of code. I will covers those in this section and close with a discussion of concepts I would like to include in the next iteration.

`Object Avoidence` 
This behavior was very limited. Having the robot only turn right was a great shortcomming that  would have negatively impacted efficiency and may have prevented the robot from reaching the end all together. I ultimately chose to impliment this behavior because the robot has great difficulties in determining which direction to turn when both front IR sensors experienced and object. When an object was encountered, the robot ended up cycling left and right around the object without actually moving away from the object.
If I were to do this section again, I would impliment some kind of filtering method to more precisely describe the IR sensor input and establish a priority of which sensor should react at any one time.

`UART Communication`
We had beef. For some reason the code that controlled serial communication from the Tiva to the Pi suddenly broke down. We did get the communication array compiled in the Tiva but it WOULD NOT SEND. I added a "break;" in the for loop and it actually worked even though there was no *while* loop in play. It was very strange and it took us critical hours to eventually revert back to the previous iteration of code, which I don't think was significantly different. I wish we had more time to troubleshoot that, or at least modify the old switch/case function menu.

### Special Feature
The features I included in this project was a PID controller to adjust the speed of the wheels to ensure the robot was moving in a straight line. This file is included in the Robot Library fuction library under [timer.c](Robot_Library/timer.c), and [timer.h](Robot_Library/timer.h). This was written as an interrupt that would adjust the speed of each wheel every 3 seconds. A file showing the coded equations is included in the Final Competition folder under [PID_Idea](finalCompetition/PID_Idea.pdf). 

It worked by calculating a sum of the proportional, integral, and derivative components. This modifier was then added (or subtracted) to the speed of one wheel to minimize the error between wheel speeds. This error was calcualted using the quadrature encoder to determine how much more one wheel had traveled with respect to the other. 

However! During implimenation of this feature, the wheels would only speed up. Eventually, I had one wheel going 100% of the duty cycle while the other remained unchained. I wasn't sure if the error was with the quadrature encoder or the function code. Since that test, I have rewritten the code such that only one wheel can be changed and the change can be negative or positive. I think any issue with the quadrature encoder could have been minimized if only one wheen was altered. 

Unfortunately, I didn't have time to test the code nor begin altering the constants for the P.I. and D. This is something I would have liked to do with more time.

### Last Comments
One thing I would have really liked to try, was adding more sophisticated code to my robot behavioral functions. In lecture,we learned so many algorithms that handle the exact problems I encountered with my super simple functions. Problems with range data coming in from the IR sensors. Creating an effective feedback system with the quadrature encoder, plotting and planning the distance the robot has already traveled. These are all topics that have solutions in their more complex code. The simple functions were supposed to be a foundation to explore more complex code, not the main attraction. I wish I had more time to go beyond the most simple designs.

This class was awesome! My partner was great and the course content was riveting. Maybe I should have switched majors. ;) 

Have a good day!

-Uri

## Robot Decision Controls
