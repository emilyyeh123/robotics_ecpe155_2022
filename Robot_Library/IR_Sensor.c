/*
 * IR_Sensor.c
 *
 *  Created on: Mar 13, 2022
 *      Author: Uri
 *      The purpose of this program is to receive distance data from a single IR Sensor
 */


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/adc.h"

#include "Motor_Control.h"
#include "PWM.h"
#include "quadEncoder.h"

uint32_t dist1;


void initIRSensor(){
    // initialize count variables
    dist1 = 0;

    // Enable ADC Module 0 and GPIO Port D
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}

    GPIO_PORTD[GPIO_AFSEL] = PIN_3;
    ADC0[ADCSSMUX0] |= 4;


    // Register an interrupt handler for the ADC Interrupt
    ADCIntRegister(ADC0_BASE, 0, IRHandler);

    // Set pins to receive input from IR Sensor
    GPIOADCTriggerEnable(GPIO_PORTD_BASE, GPIO_PIN_3);


    // Configure the trigger sources to zero sample sequencer, external pin input, and highest priority sampling
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_EXTERNAL, 0);

    // Enable sample sequence
    ADCSequenceEnable(ADC0_BASE, 0);

    // Enable the sample sequence Interrupt
    ADCIntEnable(ADC0_BASE, 0);


}

void IRHandler(){
    // Retrieve data from IR Sensor and store in dist1 variable
    ADCSequenceDataGet(ADC0_BASE, 0, &dist1);

    // Convert voltage signal to distance

    // Establish distance thresholds to make the robot respond to objects


    // Clear data from IR sensor
    ADCIntClear(ADC0_BASE, 0);


}




