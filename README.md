# bishop_ecpe155_2022
This is the shared repository for team Bishop (named after a character from the movie Aliens) for the Spring 2022 ECPE 155 Robotics Class. The team includes Emily Yeh and Uri Grunder.

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
