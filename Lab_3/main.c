

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
#include "driverlib/qei.h"

#include "PWM.h"
#include "Motor_Control.h"
#include "quadEncoder.h"

int main(void){
    quadEnc_init();
    motor_init(400);

    motorForward(100, 100);
    SysCtlDelay(10000000);

    uint32_t leftV = getVelocityLeft();
    uint32_t rightV = getVelocityRight();

    motorStop();
    SysCtlDelay(10000000);

    while(1){}
}
