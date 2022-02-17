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
#include "inc/tm4c123gh6pm.h"



int main()
{
    /*
    while (1)
    {
    // Perform a PWM display on Pin Connector J3.3
    // View with an Oscilloscope
    PWM_Function(800, 200);



    }

   // PWM_Function(0, 0);

   // SysCtlDelay(10000);

*/
    while (1)
    {

    motorForward(800, 300, 800, 300);
    SysCtlDelay(10000000);

    motorStop();
    SysCtlDelay(10000000);

    motorBackward(800, 300, 800, 300);
    SysCtlDelay(10000000);

    motorStop();
    SysCtlDelay(10000000);


    }


}
