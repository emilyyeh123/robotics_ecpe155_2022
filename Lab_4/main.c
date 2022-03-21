

/**
 * main.c
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
#include "LED.h"
#include "quadEncoder.h"
#include "bumpSensor.h"



int main(){
    initBumpSensorInterrupt();
    initQEInterrupt();
    initLED();
    clearLED();
    initMotor(800);


    while(1){
        motorForward(200, 200);
        clearLED();
        SysCtlDelay(1000000);


        bumpTriggered();
/*
        motorBackward(200, 200);
        SysCtlDelay(10000000);
        clearLED();

        bumpTriggered();

        motorStop();
        SysCtlDelay(10000000/2);

        bumpTriggered();
*/
    }
}

