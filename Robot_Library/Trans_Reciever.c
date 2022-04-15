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
#include "timer.h"



void initSerial(){

    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_1);

    // Enable the UART4 and the GPIO port C module. Wait for it to initialize
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1)) { }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) { }

    // Configure the GPIO pins to be outputs and UART pins
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

    // Configure the UART
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTEnable(UART1_BASE);
    UARTFIFOEnable(UART1_BASE);
}

void recieveMess(){
    // Indicate ready to receive
    displayGreenLED();

    // Wait until a response is received
    while(!UARTCharsAvail(UART1_BASE)) {}

    // Store the incoming data to a specified array
    for(int i = 0; i < sizeof(packet_rec); i++) {
            packet_rec[i] = UARTCharGet(UART1_BASE);
    }

    clearLED();

    // If the initialize flag is receive
    if ((packet_rec[0] == 0xAA) & (packet_rec[2] == 0xFF)) {

        switch(packet_rec[1]) {

        // When navigation command is received
        case 0x81:
            displayRedLED();

            // Ask for x variable
            packet_send[1] = 0xBB;
            for(int i = 0; i < 3; i++) {
                UARTCharPut(UART1_BASE,packet_send[i]);
            }

            // Wait until a response is received
            while(!UARTCharsAvail(UART1_BASE)) {}

            // Store the incoming data to a specified array
            for(int i = 0; i < sizeof(packet_rec); i++) {
                    packet_rec[i] = UARTCharGet(UART1_BASE);
            }

            // Convert Response to variable x
            double x = stod(packet_rec[1]);


            // Ask for y variable
            packet_send[1] = 0xCC;
            for(int i = 0; i < 3; i++) {
                UARTCharPut(UART1_BASE,packet_send[i]);
            }

            // Wait until a response is received
            while(!UARTCharsAvail(UART1_BASE)) {}

            // Store the incoming data to a specified array
            for(int i = 0; i < sizeof(packet_rec); i++) {
                    packet_rec[i] = UARTCharGet(UART1_BASE);
            }

            // Convert Response to variable x
            double y = stod(packet_rec[1]);

            clearLED();
            displayBlueLED();
            nav_xy(x, y);


            // If robot has reached goal
            if((pose[0] == final_pose[0]) && (pose[1] == final_pose[1])){
                jobComplete();
            }
            // Else indicate an object or error of some kind
            else if((pose[0] == final_pose[0]) && (pose[1] == final_pose[1])){
                objectDetected();

        }
    }

    displayBlueLED();
    SysCtlDelay(5000000);
    clearLED();
}

}




void jobComplete(){
    motorStop();
    clearLED();
    displayGreenLED();
    packet_send[1] = 0xDD;
    for(int i = 0; i < 3; i++) {
        UARTCharPut(UART1_BASE,packet_send[i]);
        }
    return;
}





void objectDetected(){
    motorStop();
    clearLED();
    displayRedLED();
    packet_send[1] = 0xDD;
    for(int i = 0; i < 3; i++) {
        UARTCharPut(UART1_BASE,packet_send[i]);
    }
    return;

}


