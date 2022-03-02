/*
 * Motor_Control.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_


struct ICR{
    uint8_t x;
    uint8_t y;
    uint8_t theta;
};

void initMotor(uint16_t period);
void motorForward(uint16_t PWLeft, uint16_t PWRight);
void motorBackward(uint16_t PWLeft, uint16_t PWRight);
void motorStop();

//void ICRPosition(){}


#endif /* MOTOR_CONTROL_H_ */
