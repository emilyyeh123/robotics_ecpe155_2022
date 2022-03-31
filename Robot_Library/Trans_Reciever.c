/*
 * Trans_Reciever.c
 *
 *  Created on: Mar 30, 2022
 *      Author: Uri
 *      This program is a beta test to send and receive data via serial transmission
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
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
#include "driverlib/uart.h"

#include "PWM.h"
#include "Motor_Control.h"
#include "quadEncoder.h"
#include "LED.h"
#include "bumpSensor.h"
#include "Trans_Reciever.h"

void initSerial(){

    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_1);

    // Enable the UART4 and the GPIO port C module. Wait for it to initialize
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART4)) { }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) { }

    // Configure the GPIO pins to be outputs and UART pins
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, (GPIO_PIN_4 | GPIO_PIN_5));

    // Configure the UART
    UARTConfigSetExpClk(UART4_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTEnable(UART4_BASE);
    UARTFIFOEnable(UART4_BASE);
}




