/*
 * sensor.c
 *
 *  Created on: Mar 2, 2022
 *      Author: emily
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

#include "LED.h"
#include "motor_control.h"
#include "bumpSensor.h"



bool rightBumperTriggered = false;
bool leftBumperTriggered = false;



void initBumpSensorInterrupt(){
    // set up PC6 & PC7 for left wheel bumper
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)){}

    // Register the port-level interrupt handler. This handler is the first level interrupt handler for all the pin interrupts
    GPIOIntRegister(GPIO_PORTC_BASE, bumpSensorInterruptHandler);

    // Set Input pins to read sensor data
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, (GPIO_PIN_6 | GPIO_PIN_7));

    // GPIOPadConfigSet: set pad configuration for pins
    // GPIO_STRENGTH_2MA: for pins configured as input ports, pad is configured as requested,
    //                    but the only real effect on the input is the configuration of the pull-up or pull-down termination
    // GPIO_PIN_TYPE_STD_WPD: specify weak pull down resistor
    GPIOPadConfigSet(GPIO_PORTC_BASE, (GPIO_PIN_6 | GPIO_PIN_7), GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

    // Set pins for input signal from sensor
    // enter interrupt handler upon hitting the first rising edge
    // if done correctly, bounce will be skipped over and will not be a concern
    GPIOIntTypeSet(GPIO_PORTC_BASE, (GPIO_PIN_6 | GPIO_PIN_7), GPIO_RISING_EDGE);

    // Enable the Interrupts
    GPIOIntEnable(GPIO_PORTC_BASE, (GPIO_PIN_6 | GPIO_PIN_7));
}

void bumpSensorInterruptHandler(){
    // clear interrupt
    GPIOIntClear(GPIO_PORTC_BASE, (GPIO_PIN_6 | GPIO_PIN_7));

    // Right Bumper
    if(GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) == GPIO_PIN_6){
        // turn on LED
        displayRedLED();
        rightBumperTriggered = true;
    }

    // Left Bumper
    if(GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7) == GPIO_PIN_7){
        // turn on LED
        displayGreenLED();
        leftBumperTriggered = true;
    }
}


bool getRightBumperTriggered(){
    return rightBumperTriggered;
}

bool getLeftBumperTriggered(){
    return leftBumperTriggered;
}

void clearBumpTriggers(){
    rightBumperTriggered = false;
    leftBumperTriggered = false;
}

void bumpTriggered(){
    // When right bumper is hit, perform motorAvoidLeftBump
    if(getRightBumperTriggered() == true){
        clearBumpTriggers();
        motorAvoidLeftBump();
    }else if(getLeftBumperTriggered() == true){
        clearBumpTriggers();
        motorAvoidRightBump();
    }
}

