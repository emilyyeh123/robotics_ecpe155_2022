

/**
 * Lab 3 main.c
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"

#include "PWM.h"
#include "Motor_Control.h"
#include "interrupt.h"

int main(){
    initQEInterrupt();
    initMotor(800);

    motorForward(200, 200);
    SysCtlDelay(10000000);

    motorBackward(600, 600);
    SysCtlDelay(10000000);

    motorStop();
    SysCtlDelay(10000000);

    while(1){}
}
