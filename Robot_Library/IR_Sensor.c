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
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"


// Set up PDO, PD1, PD2 for the ADC according to the Tiva Data Sheet
// AIN 7, 6, 5

// Peripheral base addresses.
#define GPIO_PORTD              ((volatile uint32_t *)0x40007000)
#define ADC0                    ((volatile uint32_t *)0x40038000)

// Peripheral register offsets and special fields
enum {
#define   PIN_0              (1 << 0)      // pin 0
#define   PIN_1              (1 << 1)      // pin 1
#define   PIN_2              (1 << 2)      // pin 2
  GPIO_AFSEL  =   (0x420 >> 2),
  ADCSSMUX0   =   (0x040 >> 2),
};



uint32_t dist0, dist1, dist2;

void initIRSensor(){
    // initialize count variables
    dist0 = 0;
    dist1 = 0;
    dist2 = 0;

    // Enable ADC Module 0 and GPIO Port D
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}

    GPIOPinTypeADC(GPIO_PORTD_BASE, (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2));

    // enable alternate function
    GPIO_PORTD[GPIO_AFSEL] = (PIN_0 | PIN_1 | PIN_2);
    // Set the pins for each mux
    // bc each mux is 4 bits, shift by 4 for each extra mux
    ADC0[ADCSSMUX0] |= (7 << 0);
    ADC0[ADCSSMUX0] |= (6 << 4);
    ADC0[ADCSSMUX0] |= (5 << 8);

    // each pin requires a separate sequence number
    ADCSequenceDisable(ADC0_BASE, 0);
    ADCSequenceDisable(ADC0_BASE, 1);
    ADCSequenceDisable(ADC0_BASE, 2);

    // Configures the trigger source and priority of a sample sequence.
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 1);
    ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 2);

    // Configure a step of the sample sequencer.
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH7 | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH6 | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH5 | ADC_CTL_END);

    // Enable sample sequence
    ADCSequenceEnable(ADC0_BASE, 0);
    ADCSequenceEnable(ADC0_BASE, 1);
    ADCSequenceEnable(ADC0_BASE, 2);
}

uint32_t getSensorData0(){
    ADCProcessorTrigger(ADC0_BASE, 0);
    ADCSequenceDataGet(ADC0_BASE, 0, &dist0);
    return dist0;
}

uint32_t getSensorData1(){
    ADCProcessorTrigger(ADC0_BASE, 1);
    ADCSequenceDataGet(ADC0_BASE, 1, &dist1);
    return dist1;
}

uint32_t getSensorData2(){
    ADCProcessorTrigger(ADC0_BASE, 2);
    ADCSequenceDataGet(ADC0_BASE, 2, &dist2);
    return dist2;
}


