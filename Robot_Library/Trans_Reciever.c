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
#include "IR_Sensor.h"

char packet_rec[7];
char packet_send[7];

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



/*
void jobComplete(char *packet_send){
    motorStop();
    clearLED();
    displayGreenLED();
    packet_send[1] = 0xDD;
    for(int i = 0; i < 3; i++) {
        UARTCharPut(UART1_BASE,packet_send[i]);
        }
    return;
}





void objectDetected(char *packet_send){
    motorStop();
    clearLED();
    displayRedLED();

    packet_send[1] = 0xDD;
    for(int i = 0; i < 3; i++) {
        UARTCharPut(UART1_BASE,packet_send[i]);
    }
    return;

}
*/


void performAction(char *packet_rec, char *packet_send){
    uint32_t rightFrontSensor = 0;
    uint32_t leftFrontSensor = 0;
    uint32_t rightSideSensor = 0;
    uint32_t leftSideSensor = 0;

    // check if first command is start command
    if(packet_rec[0] == startCommand){
        switch(packet_rec[1]){


        case moveForward:
            // REPLACE THE FOLLOWING CODE WITH
            // TICK-BASED MOTOR FORWARD FUNCTION HERE
            // desired distance will be returned by packet_rec[2]
            packet_send[0] = startCommand;
            packet_send[1] = taskComplete;
            packet_send[2] = endCommand;

            for(int i = 0; i < 2; i++) {
                 UARTCharPut(UART1_BASE,packet_send[i]);
            }


        case autoForward:
            AutoForward();
            break;


        case moveBackward:
            // REPLACE THE FOLLOWING CODE WITH
            // TICK-BASED MOTOR FORWARD FUNCTION HERE
            // desired distance will be returned by packet_rec[2]
            packet_send[0] = startCommand;
            packet_send[1] = taskComplete;
            packet_send[2] = endCommand;

            for(int i = 0; i < 2; i++) {
                 UARTCharPut(UART1_BASE,packet_send[i]);
            }

            break;

        // 90 degree turn
        case turnRight:

            packet_send[0] = startCommand;
            packet_send[1] = taskComplete;
            packet_send[2] = endCommand;

            for(int i = 0; i < 2; i++) {
                 UARTCharPut(UART1_BASE,packet_send[i]);
            }

            break;

        // 90 degree turn
        case turnLeft:

            packet_send[0] = startCommand;
            packet_send[1] = taskComplete;
            packet_send[2] = endCommand;

            for(int i = 0; i < 2; i++) {
                 UARTCharPut(UART1_BASE,packet_send[i]);
            }

            break;


        case rightFrontIR:
            rightFrontSensor = getSensorData2();

            packet_send[1] = (rightFrontSensor >> 8) & 0xFF; // send upper 8 bits of 16-bit data
            packet_send[2] = rightFrontSensor & 0xFF; // send lower 8 bits of 16-bit data
            packet_send[3] = endCommand;
            for(int i = 0; i < 4; i++){
                UARTCharPut(UART1_BASE,packet_send[i]);
            }
            break;


        case leftFrontIR:
            leftFrontSensor = getSensorData3();
            packet_send[1] = (leftFrontSensor >> 8) & 0xFF; // send upper 8 bits of 16-bit data
            packet_send[2] = leftFrontSensor & 0xFF; // send lower 8 bits of 16-bit data
            packet_send[3] = endCommand;
            for(int i = 0; i < 4; i++){
                UARTCharPut(UART1_BASE,packet_send[i]);
            }
            break;


        case rightSideIR:
            rightSideSensor = getSensorData1();
            packet_send[1] = (rightSideSensor >> 8) & 0xFF; // send upper 8 bits of 16-bit data
            packet_send[2] = rightSideSensor & 0xFF; // send lower 8 bits of 16-bit data
            packet_send[3] = endCommand;
            for(int i = 0; i < 4; i++){
                UARTCharPut(UART1_BASE,packet_send[i]);
            }
            break;


        case leftSideIR:
            leftSideSensor = getSensorData0();
            packet_send[1] = (leftSideSensor >> 8) & 0xFF; // send upper 8 bits of 16-bit data
            packet_send[2] = leftSideSensor & 0xFF; // send lower 8 bits of 16-bit data
            packet_send[3] = endCommand;
            for(int i = 0; i < 4; i++){
                UARTCharPut(UART1_BASE,packet_send[i]);
            }
            break;


        case searchWaypoint:
            // Robot travels 45 degrees
            turnMultiplier = 1;
            motorRightTurn45();

            // send data to Pi
            packet_send[0] = startCommand;
            packet_send[1] = taskComplete;
            packet_send[2] = turnMultiplier;
            packet_send[3] = endCommand;

            // Send Data
            for(int i = 0; i < 3; i++) {
                 UARTCharPut(UART1_BASE,packet_send[i]);
            }

            break;


        case objectAvoidence:

            // Toggle Object Avoidance
            objectAvoid();

            // Fill in transmission array
            packet_send[0] = startCommand;
            packet_send[1] = taskComplete;
            packet_send[2] = turnMultiplier;
            packet_send[3] = endCommand;

            // send data to pi
            for(int i = 0; i < 3; i++){
                UARTCharPut(UART1_BASE,packet_send[i]);
            }

            break;


        default:
            // display red light if invalid command passed
            // theoretically should never receive invalid command
            displayRedLED();
            SysCtlDelay(5000000);
            clearLED();
        }
    }
}


void initRecPacket(char *packet_rec){
    // reset packet_rec
    for(int i = 0; i < 7; i++){
        packet_rec[i] = 0x00;
    }
}

void initSendPacket(char *packet_send){
    // reset packet_send
    packet_send[0] = startCommand;
    for(int i = 1; i < 7; i++){
        packet_send[i] = 0x00;
    }
}


void storeReceivedPacket(char *packet_rec){
    // Wait until a byte is received
    while(!UARTCharsAvail(UART1_BASE)){}

    // run until all bytes of data have been received
    // or until end command has been received
    int count = 0;
    while(1){
        // Store the incoming data
        packet_rec[count] = UARTCharGet(UART1_BASE);
        if(packet_rec[count] == endCommand){break;}
        count++;
    }
}

void AutoForward(){
    // Reset quad encoder
     revCountLeft = 0;
     revCountRight = 0;

     // begin forward motion
     motorForward(300,350);

     while(1){
         SysCtlDelay(10000);

         // Monitor IR Data
         int fLeft = getSensorData3();
         int fRight = getSensorData2();

         // When an object is encountered
         if((fLeft >= 1500) | (fRight >= 1500)){
             motorStop();
             packet_send[1] = objectEncounter;
             break;
         }

         // If robot has traveled about 0.5 meters stop
         if((revCountLeft >= 80) | (revCountRight >= 80)){
             motorStop();
             packet_send[1] = taskComplete;
             break;
         }
     }
     // Average position
     int avg = round((revCountLeft + revCountRight)/2);

     // Send data to Pi
     packet_send[0] = startCommand;
     packet_send[1] = revCountLeft;
     packet_send[2] = endCommand;
     for(int i = 0; i <= 2; i++){
         UARTCharPut(UART1_BASE,packet_send[i]);;
     }
}
