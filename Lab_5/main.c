

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
#include "driverlib/adc.h"

#include "PWM.h"
#include "Motor_Control.h"
#include "LED.h"
#include "quadEncoder.h"
#include "bumpSensor.h"
#include "IR_Sensor.h"



int main(){
    initIRSensor();

    while(1){
        uint32_t sensor0 = getSensorData0();
        uint32_t sensor1 = getSensorData1();
        uint32_t sensor2 = getSensorData2();
    }
}

