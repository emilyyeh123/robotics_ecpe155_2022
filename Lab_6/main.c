

/**
 * main.c
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

// packet structure
#define startCommand 0xAA
#define endCommand 0x55

// Movement Commands
#define moveForward 0x01
#define moveBackward 0x02
#define turnRight 0x03
#define turnLeft 0x04

// IR Commands
// INCLUDE IR COMMANDS HERE

char packet_send[3] = {startCommand, 0x02, endCommand};
// can receive up to 8 bytes of data
// 3 bytes reserved for start (0xAA), command, end (0x55)
char packet_rec[8];

int main(void)
{
    initSerial();
    initLED();

    while(1){
        //clear packet_rec
        for(int i = 0; i < 8; i++){
            packet_rec[i] = 0x00;
        }

        // Indicate ready to receive
        displayGreenLED();

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

        clearLED();
        SysCtlDelay(5000000);

        // check if first command is start command
        if(packet_rec[0] == startCommand){
            switch(packet_rec[1]){
            case moveForward:
                // REPLACE THE FOLLOWING CODE WITH
                // TICK-BASED MOTOR FORWARD FUNCTION HERE
                // desired distance will be returned by packet_rec[2]
                packet_send[1] = 0x31;
                for(int i = 0; i < 3; i++) {
                     UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            case moveBackward:
                // REPLACE THE FOLLOWING CODE WITH
                // TICK-BASED MOTOR FORWARD FUNCTION HERE
                // desired distance will be returned by packet_rec[2]
                packet_send[1] = 0x32;
                for(int i = 0; i < 3; i++) {
                     UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            case turnRight:
                // REPLACE THE FOLLOWING CODE
                packet_send[1] = 0x33;
                for(int i = 0; i < 3; i++) {
                     UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            case turnLeft:
                // REPLACE THE FOLLOWING CODE
                packet_send[1] = 0x34;
                for(int i = 0; i < 3; i++) {
                     UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            //include IR cases here once implemented
            default:
                // display red light if invalid command passed
                // theoretically should never receive invalid command
                displayRedLED();
                SysCtlDelay(5000000);
                clearLED();
            }
        }
    }
}
