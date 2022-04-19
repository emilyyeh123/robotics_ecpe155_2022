# bishop_ecpe155_2022
This is the shared repository for team Bishop (named after a character from the movie Aliens) for the Spring 2022 ECPE 155 Robotics Class. The team includes Emily Yeh and Uri Grunder.

## Lab 7
In Lab 7 we aimed to design a more complex object avoidence function that can help the robot navigate from a starting position to a user defined position in the global reference frame.

A function for global navigation was established during Lab 6. This navigation function takes in user defined "x" and "y" coordinates (in centimeters) and compares it with the robot's current location. The robot is then oriented towards the final position and begins to move towards it. This function is called `nav_xy` and can be found in the Robot Library Folder as: [Motor_Control.c](Robot_Library/Motor_Control.c) and [Motor_Control.h](Robot_Library/Motor_Control.h). A summary of this function can be seen in the Lab 6 section of this document.

The global navigation function currently can oreient the robot, move towards a final destination, stop once its reached the destination, and transmit a "task completion" signal to the Pi but it must be modified to take constantly take in sensor data and alter functionality if an obstacle is sensed. To accomplish this, it is proposed that a new object avoidence function be developed. The pseudocode for this function is described in Lab_7 under: [Lab_7_Psudeocode.md](Lab_7/Lab_7_Psudeocode.md). This code is still under development and has not yet been tested. However, sensor data remains to be successfully transmitted between the Tiva and the Raspberry Pi.

## Lab 6
In Lab 6 we designed a communication protocol to send and receive data between the Tiva and the Raspberry Pi. Using this protocol, we plan to control robot motion using commands passed from the Raspberry Pi to the Tiva.

### Tiva Robot Library Updates
Two new functions were created in the robot function library to define the Tiva's role in serial communication. These function are included in the Robot_Library folder: [Trans_Reciever.c](Robot_Library/Trans_Reciever.c) and [Trans_Reciever.h](Robot_Library/Trans_Reciever.h). This function has been expanded since its initial sucess. A logic analyzer was used to observe communication between the two boards. A sceenshot was included in the Lab 6 folder: [Logic Analyzer Screenshot](Lab_6/Logic%Analyzer%Screenshot.png). This image shows data recieved on the Tiva from the Raspberry Pi through channel 9 and a response recieved on the Raspberry Pi from the Tiva through channel 1. A high-level description of each function follows.

  - `initiSerial()`
     - Initize pins for serial communication by enabling the UART4 and GPIO C Modules and assigning reviever and transmitter pins.

  - `recieverMess()`
    - A green LED is enabled from the Tiva board to indicate that the system is waiting for incoming commands from the Raspberry Pi. The Tiva will hold all actions until a string array is transferred to the system. This character array is stored as a global variable `packet_rec`.
    - The LED is cleared and the saved characater array is compared against a switch/case block. The comparison will only take place if an initialization command is observed in the first element of the character array. A blue LED will be enabled if a command is successfully read.
    - The second element of the character array is compared against a list of robot function commands. If a match is successful, the Tiva will call on subsequent array elements to define relevant function parameters.
    - The Tiva will direct the robot to perform the called upon action. Once the action or set of actions is completed, the Tiva will transmit a message of completion to the Raspberry Pi.
    - If an error occurs or a sensor is triggered, the running function will stop and sensor data will be transmitted to the Raspberry Pi for further instruction. In the event that the robot is unable to complete its original task, a green LED will be turned on to indicate that the Tiva is awaiting instruction or a red LED will be turned on to indicate an error. The transmitting array is described by the 8-element character array `packet_send`.

The more complex serial control function is currently being validated. 


An Excel sheet has been created to detail the commands that can be transmitted by the Raspberry Pi to control the Tiva. This file is included in the main folder of the Respository: [Command_Data Planner.xlxs](Command_Data%Planner.xlxs). The file shows each available function as a hexadecimal value that can be transmitted as a byte within a character array with a maximum of 8 elements.

To minimize the number of parameters passed to the Tiva from the Raspberry Pi, the Motor_Control source code has been modified in the Robot Library folder under [Motor_Control.c](Robot_Library/Motor_Control.c) and [Motor_Control.h](Robot_Library/Motor_Control.h). A summary of the source code modifications are listed below.
  - `motorForward()`
    - The speed is statically defined such that the robot travels in a nearly straight, forward motion at a static speed of 13.3 cm per second. 

  - `motorBackward()`
    - The speed is statically defined such that the robot travels in a nearly straight, backward motion at a static speed of 13.3 cm per second. 

  -  `motorCorrections()`
    - This function was deleted as a static wheel speed has been adopted

  - `travelTime(uint16_t distance)`
    - This function was created to provide a time duration for robot motion to occur. A desired distance in centimeters is specified by the user and is converted into a time duration. A static velocity by a calculated time duration should yield a known distance traveled. 
    - The ability to calculate the distance traveled over an approximate time is also foundational to functions that will update the robot position at regular intervals.

  - `extern double angle`
    - This global variable refers to the angle formed between a line drawn from the robots initial position to a final position and the positive x-axis, taken as the straight line drawn forward from the midpoint of the robot.

  - `extern double pose[2]`
    - Global Variable that defines the robots initial position. When the robot is activated, this value will default to {0,0,0}. This corresponds to the robots kinematic model where {0,0,0} = {x, y, angle}. 

  - `extern double final_pose[2]`
    - Global Variable that defines the robots final position. This variable is initialized as {0, 0, 0} but will be later defined by the user. The three elements in the array refer to the kinematic model where {0, 0, 0} = {x, y, angle}.


  - `motorCheckAngle()`
    - Function that takes the difference between the x-values, element[0] of the `pose` and `final_pose` arrays. A negative value indicates that the desired destination is behind the robot.
    - In the event that the difference is negative the robot will be rotated 180 degrees. This is because angles calculated using arcTan retain a domain between postive and negative 90 degrees, so the final pose must be within that domain to adequately coordinate robot motion towards the final position. The sign of the stored value for the final pose is changed to indicate the effect of the rotation.

  - `getAngle()`
    - Function to calculate the angle of a straight line drawn from the robots initial position to the final position and the positive x-axis. The positive x-axis is taken as the line drawn from the robot's midpoint in the forward direction.
    - The calculated angle is stored as a global variable `angle `

  - `motorSelfOrient()`
    - Function that rotates the robot from its intial orientation to face its destination position.
      - Assigns the robots oreientation the value of the global variable `angle`. 
      - Converts the angle to a number of ticks that can be tracked by the quadrature encoder.
      - Based on the sign of the angle, the robot will rotate clock-wise or counterclock-wise until the desired orentation is met.
      - Angle is assumed to be in radians

  - `motorUserOrient()`
    - Function that rotates the robot from its initial orientation to face a user specified angle between positive and negative 90 degrees.
      - User input is limited to the domain of arcTan to ensure the number transmitted from the Raspberry Pi stays within the bounds of 1 byte (0 to 255)

  - `nav_xy(double x, double y)`
    - Function to navigate the robot from its initial position to a global destination defined by the user.

### Raspberry Pi 
A User Interface has been developed on the Raspberry Pi to aid in user control of basic robot motor functions. This code is included in the raspberryPi folder in the main branch of the repository as [uartComm.py](raspberryPi/uartComm.py). A high-level description of the code can be found in [raspberryPi/README.md](raspberryPi/README.md).

This user interface successfully transmits and recieves data as shown in [Logic Analyzer Screenshot](Lab_6/Logic%Analyzer%Screenshot.png). IR data is also sucessfully transmittable between the Tiva and the Raspberry Pi. However, the more complex motion control of the robot are still being validated.

## Lab 5
In Lab 5 we attached three Infrared (IR) Sensors to the robot chasis and created a program that used those sensors to avoid objects that approach the robot sides and rear. 

In the Lab_5 folder, there are two drawings that show how these sensors were connected to the robot and the general computational flow of the program which uses these sensors and the bumper. These documents can be found in the Lab_5 Folder: [Block Diagram of Obstacle Avoidance](Lab_5/Block%20Diagram%20of%20Obstacle%20Avoidance.pdf) and [Sensing System Design](Lab_5/Sensing%20System%20Design.pdf).

To successfully use the IR sensors, new functions were created. These functions are included in the Robot_Library under [IR_Sensor.h](Robot_Library/IR_Sensor.h) and [IR_Sensor.c](Robot_Library/IR_Sensor.c). They are described as follows:
  - `getSensorData0()`
    - retrieve voltage signal coming from the IR Sensor
    - Store the signal data in a variable called "dist0"

  - `getSensorData1()`
    - retrieve voltage signal coming from the IR Sensor
    - Store the signal data in a variable called "dist1"

  - `getSensorData2()`
    - retrieve voltage signal coming from the IR Sensor
    - Store the signal data in a variable called "dist2"

As shown above, three new variables (`dist0`, `dist1`, and `dist2`) were declared to store IR signal data.
The [Sensor Verification](Lab_5/sensorVerification.md) file describes how these functions were tested,
showing that the IR sensors work independent of all other robot features.

Additionally, Emily did amazing work in configuring the GPIO pins to the ADC alternate function.

## Lab 4
In Lab 4, we designed, printed and attached a bumper to the robot. Bump switches were used to signal the robot to take specified actions when a bumper was depressed.
The part and assembly drawings are included as PDF's in the Lab_4 Folder: [Bumper Assembly Drawing](Lab_4/Bumper%20Assembly%20Drawing.pdf), [Fixed Bumper Drawing](Lab_4/Fixed%20Bumper%20Drawing.pdf), [Mobile Bumper Drawing](Lab_4/Mobile%20Bumper%20Drawing.pdf).
  - The bumper switches were secured to the bumper using an double sided adhesive that was included in the course materials. The wires run through the rear of the bumper and wind through the robot chasis to a breakout board.

We also created several new functions that will control the robot's reactions to collisions with an object.  
  - These functions are included in the Robot_Library under [Motor_Control.h](Robot_Library/Motor_Control.h) and [Motor_Control.c](Robot_Library/Motor_Control.c). It     includes the following functions:
      -  `void motorAvoidLeftBump() and motorAvoidRightBump()`
        - Clear the global count variables
        - Move backwards a specified distance
        - If the left bumper is active, rotate 45 degrees to the right. If the right bumper is active, rotate 45 degrees left
        - Return to main.c  

Additionally, a new source and header file has been created to control the bump sensors. 
  - These functions are included in the Robot_Library under [BumpSensor.h](Robot_library/BumpSensor.h) and [BumpSensor.c](Robot_Library/BumpSensor.c). It includes the following functions:
    - `void initBumpSensorInterrupt()`
      - initialized bump sensor interrupt to monitor the signals from the right and left bump switch
      - The left Bump Switch is set to PC6 and the right Bump Switch is set to PC7

    - `bool bumpSensorInterruptHandler()`
      - When either of the bump sensors are triggered, light up an LED

    - `bool getRightBumperTriggered() and getLeftBumperTriggered()`
      - Read and return the value of the global variables right and left bumer triggered

    - `void clearBumpTriggers()`
      - Set all values of the bumpers to false 

    - `void bumpTriggered()`
      - If one of the bumpers are activated, call functions from Motor_Control.c to navigate away from the object

## Lab 3
In lab 3, we created a [pin planner](pin_planner.xlsx) to keep track of the pins we are using on the microcontroller.

We also created several new functions that use QE signals to drive robot motion.
  - These functions are included in the Robot_Library under [Motor_Control.h](Robot_Library/Motor_Control.h) and               [Motor_Control.c](Robot_Library/Motor_Control.c). It includes the following functions:
    - `void motorRightTurn90() and void motorLeftTurn90`
      - Resets the global count variables
      -  Sets the pins that control wheel motion such that the right wheel moves forward and the left wheel moves backward
      -  Counts the ticks to about a 90 degree rotation from current orientation
      -  Resets the counter to zero and returns to main.c
      
    - `void motorRightTurn45() and void motorLeftTurn45`
      - This function does the same thing as motorTurn90() but turns the robot about 45 degrees from current orientation. 

    - `void motorCorrection()`
      - monitors the tick counters between the wheels
      - If one of the wheels reaches 5 or more ticks that the other wheel
        - Increase the speed of the slower wheel

    - `void motorRect(uint16_t x, uint16_t y)`
      - User gives the length of the rectangle sides
      - A Side Counter local variable is set to zero
      - The robot then navigates a rectangle based on the given distances
      - Once the robot has navigated 4 sides, the robot will terminate motion

## Lab 2
[main.c](Lab_2/main.c) in [Lab_2](Lab_2) uses the aforementioned files to initialize the motor and move the system. It's currently set up to move forward slowly, backward quickly, then stop.

In Lab 2, we created the [Robot_Library](Robot_Library) peripheral. This library contains:
- [PWM.h](Robot_Library/PWM.h) and [PWM.c](Robot_Library/PWM.c) which includes the following functions:
  - `void initPWM(uint16_t period)`
    - Initializes the PWM for both wheels 
    - The left wheel is configured on M0PWM1, PB7, Generator 0
    - The right wheel is configured on M0PWM2, PB4, Generator 1
  - `void setPW(uint16_t PWL, uint16_t PWR)`
    - Sets the pulse width (aka duty cycle) of both wheels
    - The 2 parameters stand for PWL (Pulse Width Left) and PWR (Pulse Width Right)
- [Motor_Control.h](Robot_Library/Motor_Control.h) and [Motor_Control.c](Robot_Library/Motor_Control.c) which includes the following functions:
  - `initMotor(uint16_t period)`
    - Calls `initPWM` then sets up the ports/pins for IN1 and IN2 and sets standby pins to high
    - On the left wheel, IN1 and IN2 correspond to PE1 and PE2, respectively
    - On the right wheel, IN1 and IN2 correspond to PE4 and PE5, respectively
    - The standbys are connected to PA6 and PA7
  - `void motorForward(uint16_t PWLeft, uint16_t PWRight)`
    - Calls `setPW` and turns wheels forward (IN1: Low, IN2: High)
    - Set left wheel pins opposite because it mirrors the right wheel
    - Therefore, PE2 and PE4 are set to low while PE1 and PE5 are set to high
  - `void motorBackward(uint16_t PWLeft, uint16_t PWRight)`
    - Calls `setPW` and turns wheels backward (IN1: High, IN2: Low)
    - Again, set left wheel pins opposite because it mirrors the right wheel
    - Therefore, PE1 and PE5 are set to low while PE2 and PE4 are set to high 
  - `void motorStop()`
    - set all pins (IN1 and IN2) high

## Lab 1
Lab 1 was completed separately by both members. [Uris_Lab1](Uris_Lab1) contains Uri's code for lab 1 and [emily_lab1](emily_lab1) contains Emily's code for lab 1.
