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


// Set up PDO, PD3, PD2 for the ADC according to the Tiva Data Sheet
// AIN 7, 4, 5, 0, 11

// Peripheral base addresses.

#define GPIO_PORTB              ((volatile uint32_t *)0x40005000)
#define GPIO_PORTE              ((volatile uint32_t *)0x40024000)
#define GPIO_PORTD              ((volatile uint32_t *)0x40007000)
#define ADC0                    ((volatile uint32_t *)0x40038000)

// Peripheral register offsets and special fields
enum {
#define   PIN_0              (1 << 0)      // pin 0
#define   PIN_3              (1 << 3)      // pin 3
#define   PIN_2              (1 << 2)      // pin 2
#define   PIN_5              (1 << 5)      // pin 7
  GPIO_AFSEL  =   (0x420 >> 2),
  ADCSSMUX0   =   (0x040 >> 2),
};



uint32_t dist0, dist1, dist2, dist3;

void initIRSensor(){
    // initialize count variables
    dist0 = 0;
    dist1 = 0;
    dist2 = 0;
    dist3 = 0;

    // Enable ADC Module 0, GPIO Port D, E, and B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}


    GPIOPinTypeADC(GPIO_PORTB_BASE, (GPIO_PIN_5));
    GPIOPinTypeADC(GPIO_PORTD_BASE, (GPIO_PIN_7 | GPIO_PIN_3 | GPIO_PIN_2));
    GPIOPinTypeADC(GPIO_PORTE_BASE, (GPIO_PIN_3));


    // enable alternate function
    GPIO_PORTD[GPIO_AFSEL] = (GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_7);
    GPIO_PORTE[GPIO_AFSEL] = (PIN_3);
    GPIO_PORTB[GPIO_AFSEL] = (PIN_5);

    // Set the pins for each mux
    // bc each mux is 4 bits, shift by 4 for each extra mux

    ADC0[ADCSSMUX0] |= (7 << 0);
    ADC0[ADCSSMUX0] |= (4 << 4);
    ADC0[ADCSSMUX0] |= (5 << 8);
    ADC0[ADCSSMUX0] |= (0 << 12);
    ADC0[ADCSSMUX0] |= (11 << 16);


    // each pin requires a separate sequence number
    ADCSequenceDisable(ADC0_BASE, 0);
    ADCSequenceDisable(ADC0_BASE, 1);
    ADCSequenceDisable(ADC0_BASE, 2);
    ADCSequenceDisable(ADC0_BASE, 3);
    ADCSequenceDisable(ADC0_BASE, 4);

    // Configures the trigger source and priority of a sample sequence.
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 1);
    ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 2);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 3);
    ADCSequenceConfigure(ADC0_BASE, 4, ADC_TRIGGER_PROCESSOR, 4);


    // Configure a step of the sample sequencer.
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH7 | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH4 | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH5 | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_END);
    ADCSequenceStepConfigure(ADC0_BASE, 4, 0, ADC_CTL_CH11 | ADC_CTL_END);

    // Enable sample sequence
    ADCSequenceEnable(ADC0_BASE, 0);
    ADCSequenceEnable(ADC0_BASE, 1);
    ADCSequenceEnable(ADC0_BASE, 2);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCSequenceEnable(ADC0_BASE, 4);

}
// Side Left Sensor
uint32_t getSensorData0(){
    ADCProcessorTrigger(ADC0_BASE, 0);
    SysCtlDelay(10000000/64);
    ADCSequenceDataGet(ADC0_BASE, 0, &dist0);
    return dist0;
}

// side right sensor
uint32_t getSensorData1(){
    ADCProcessorTrigger(ADC0_BASE, 1);
    SysCtlDelay(10000000/64);
    ADCSequenceDataGet(ADC0_BASE, 1, &dist1);
    return dist1;
}
// Front Right Sensor
uint32_t getSensorData2(){
    ADCProcessorTrigger(ADC0_BASE, 2);
    SysCtlDelay(10000000/64);
    ADCSequenceDataGet(ADC0_BASE, 2, &dist2);
    return dist2;
}
 // front Left sensor
uint32_t getSensorData3(){
    ADCProcessorTrigger(ADC0_BASE, 3);
    SysCtlDelay(10000000/64);
    ADCSequenceDataGet(ADC0_BASE, 3, &dist3);
    return dist3;
}


