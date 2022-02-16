/*
 * Lab_2.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Uri
 *
 *      The purpose of this lab is to create a PWM signal from the Tiva Launchpad and demonstrate the
 *      robot's ability to move forward and backward.
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



int main()
{
    // Perform a PWM display on Pin Connector J3.3
    // View with an Oscilloscope
    //PWM_Function(800, 200);

    //SysCtlDelay(1000000);

   // PWM_Function(0, 0);

   // SysCtlDelay(10000);


    motorForward(800, 100, 800, 100);
    SysCtlDelay(100000);

    motorStop();
    SysCtlDelay(100000);

    motorBackward(800, 100, 800, 100);
    SysCtlDelay(100000);

    motorStop();
    SysCtlDelay(100000);


}
