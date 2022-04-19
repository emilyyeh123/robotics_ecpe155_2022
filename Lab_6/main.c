

/**
 * main.c
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"

#include "PWM.h"
#include "Motor_Control.h"
#include "quadEncoder.h"
#include "LED.h"
#include "bumpSensor.h"
#include "Trans_Reciever.h"
#include "timer.h"
#include "IR_Sensor.h"



// packet structure
#define startCommand 0xAA
#define endCommand 0x55

// Movement Commands
#define moveForward 0x01
#define moveBackward 0x02
#define turnRight 0x03
#define turnLeft 0x04

// IR Commands
#define rightIR 0x11
#define leftIR 0x12
#define backIR 0x13

// can receive up to 8 bytes of data
// 3 bytes reserved for start (0xAA), command, end (0x55)
char packet_rec[8];
char packet_send[8];

int main(void)
{
    initSerial();
    initLED();
    initMotor();
    initIRSensor();

    uint32_t leftSensor = 0;
    uint32_t rightSensor = 0;
    uint32_t backSensor = 0;

    while(1){
        // reset packet_rec
        for(int i = 0; i < 8; i++){
            packet_rec[i] = 0x00;
        }

        // reset packet_send
        packet_send[0] = startCommand;
        for(int i = 1; i < 8; i++){
            packet_send[i] = 0x00;
        }

        //motorForward();
        //travelTime(2);

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
                packet_send[2] = endCommand;
                for(int i = 0; i < 3; i++) {
                     UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            case moveBackward:
                // REPLACE THE FOLLOWING CODE WITH
                // TICK-BASED MOTOR FORWARD FUNCTION HERE
                // desired distance will be returned by packet_rec[2]
                packet_send[1] = 0x32;
                packet_send[2] = endCommand;
                for(int i = 0; i < 3; i++) {
                     UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            case turnRight:
                // REPLACE THE FOLLOWING CODE
                packet_send[1] = 0x33;
                packet_send[2] = endCommand;
                for(int i = 0; i < 3; i++) {
                     UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            case turnLeft:
                // REPLACE THE FOLLOWING CODE
                packet_send[1] = 0x34;
                packet_send[2] = endCommand;
                for(int i = 0; i < 3; i++) {
                     UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            case rightIR:
                rightSensor = getSensorData1();
                packet_send[1] = (rightSensor >> 8) & 0xFF; // send upper 8 bits of 16-bit data
                packet_send[2] = rightSensor & 0xFF; // send lower 8 bits of 16-bit data
                packet_send[3] = endCommand;
                for(int i = 0; i < 4; i++){
                    UARTCharPut(UART1_BASE,packet_send[i]);
                }
                rightSensor = 0;
                break;
            case leftIR:
                leftSensor = getSensorData1();
                packet_send[1] = (leftSensor >> 8) & 0xFF; // send upper 8 bits of 16-bit data
                packet_send[2] = leftSensor & 0xFF; // send lower 8 bits of 16-bit data
                packet_send[3] = endCommand;
                for(int i = 0; i < 4; i++){
                    UARTCharPut(UART1_BASE,packet_send[i]);
                }
                break;
            case backIR:
                backSensor = getSensorData1();
                packet_send[1] = (backSensor >> 8) & 0xFF; // send upper 8 bits of 16-bit data
                packet_send[2] = backSensor & 0xFF; // send lower 8 bits of 16-bit data
                packet_send[3] = endCommand;
                for(int i = 0; i < 4; i++){
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
}
