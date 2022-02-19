/*
 * Motor_Control.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

void motor_init(uint8_t period);
void motorForward(uint8_t PWLeft, uint8_t PWRight);
void motorBackward(uint8_t PWLeft, uint8_t PWRight);
void motorStop();

#endif /* MOTOR_CONTROL_H_ */
