

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
    initMotor(800);
    initIRSensor();

    uint32_t sensor0 = 0;
    uint32_t sensor1 = 0;
    uint32_t sensor2 = 0;

    // use to change desired distance of avoidance
    uint16_t sensorDistAvoid = 2500;

    motorForward(200,200);

    while(1){
        // left sensor
        if(sensor0 >= sensorDistAvoid){
            motorBackward(300, 200);
            SysCtlDelay(10000000/2);
            motorStop();
        }

        // right sensor
        if(sensor1 >= sensorDistAvoid){
            motorBackward(200, 300);
            SysCtlDelay(10000000/2);
            motorStop();
        }

        // back sensor
        if(sensor2 >= sensorDistAvoid){
            motorForward(400, 400);
            SysCtlDelay(10000000/2);
            motorStop();
        }

        //update sensor values
        sensor0 = getSensorData0();
        sensor1 = getSensorData1();
        sensor2 = getSensorData2();

        motorForward(200,200);
    }
}

