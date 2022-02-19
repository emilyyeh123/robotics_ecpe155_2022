/*
 * PWM.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
 */

#ifndef PWM_H_
#define PWM_H_

void PWM_init(int period);
void PWM_setPW(uint8_t PWL, uint8_t PWR);

#endif /* PWM_H_ */
