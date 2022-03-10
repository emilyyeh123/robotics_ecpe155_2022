/*
 * Motor_Control.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_


void initMotor(uint16_t period);
void motorForward(uint16_t PWLeft, uint16_t PWRight);
void motorBackward(uint16_t PWLeft, uint16_t PWRight);
void motorRightTurn90();
void motorLeftTurn90();
void motorCorrection();
void motorRect(uint16_t x, uint16_t y);
void motorStop();
void motorBackAvoid();
void motorRightTurn45();
void motorLeftTurn45();
void motorAvoidLeftBump();
void motorAvoidRightBump();


#endif /* MOTOR_CONTROL_H_ */
