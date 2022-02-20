/*
 * Lab_2.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "PWM.h"
#include "Motor_Control.h"
#include "inc/tm4c123gh6pm.h"



int main(){
    motor_init(400);

    motorForward(100, 100);
    SysCtlDelay(10000000);

    motorBackward(200, 200);
    SysCtlDelay(10000000);

    motorStop();
    SysCtlDelay(10000000);

    while (1){}
}
