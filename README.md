# bishop_ecpe155_2022
This is the shared repository for team Bishop (named after a character from the movie Aliens) for the Spring 2022 ECPE 155 Robotics Class. The team includes Emily Yeh and Uri Grunder.

## Lab 3
In lab 3, we created a [pin planner](pin_planner.xlsx) to keep track of the pins we are using on the microcontroller.

## Lab 2
In Lab 2, we created the Robot_Library peripheral. This library contains:
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

[main.c](Lab_2/main.c) in [Lab_2](Lab_2) uses the aforementioned files to initialize the motor and move the system. It's currently set up to move forward slowly, backward quickly, then stop.

## Lab 1
Lab 1 was completed separately by both members. [Uris_Lab1](Uris_Lab1) contains Uri's code for lab 1 and [emily_lab1](emily_lab1) contains Emily's code for lab 1.
