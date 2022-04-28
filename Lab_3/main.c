/**
 * Lab 3 main.c
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"

#include "PWM.h"
#include "Motor_Control.h"
#include "quadEncoder.h"



int main(){
    initQEInterrupt();
    initMotor(800);
    revCountRight = 0;
    revCountLeft = 0;

    motorRightTurn90();
    motorStop();
    SysCtlDelay(5000000);

    while(1){
/*
        motorCorrection();
        SysCtlDelay(500);

        motorRect(50, 20);

        motorAvoidLeftBump();
        motorAvoidRightBump();
*/
    }

}
