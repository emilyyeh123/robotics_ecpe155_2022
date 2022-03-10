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



void initBumpSensorInterrupt(){
    // set up PB6 for left wheel bumper
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}

    // Register the port-level interrupt handler. This handler is the first level interrupt handler for all the pin interrupts
    GPIOIntRegister(GPIO_PORTB_BASE, bumpSensorInterruptHandler);

    // Set Input pins to read sensor data
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_6);

    // Set pins for input signal from sensor
    // enter interrupt handler upon hitting the first rising edge
    // if done correctly, bounce will be skipped over and will not be a concern
    GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_RISING_EDGE);

    // Enable the Interrupts
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_6);
}

void bumpSensorInterruptHandler(){
    // clear interrupt
    GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_6);

    // If the bump sensor receives a signal
    if(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_6) == GPIO_PIN_6){
        // turn on LED
        displayRedLED();
        motorStop();
    }
}

