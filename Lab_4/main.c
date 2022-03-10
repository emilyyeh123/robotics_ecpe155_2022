

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
#include "interrupt.h"
#include "sensor.h"
#include "LED.h"



int main(){
    initQEInterrupt();
    initSensorInterrupt();
    initLED();
    initMotor(800);

    motorForward(300, 300);
    SysCtlDelay(10000000);
    clearLED();

    motorBackward(500, 500);
    SysCtlDelay(10000000);
    clearLED();

    motorStop();
    SysCtlDelay(10000000);

    while(1){}
}

