

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

char packet_send[3];
char packet_rec[3];

int main(void)
{
    initSerial();
    initLED();

    while(1){

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
        if (packet_rec[0] == 0xAA) {

            switch(packet_rec[1]) {

            // When THIS command is received
            case 0x81:
                displayRedLED();
                for(int i = 0; i < 3; i++) {
                    UARTCharPut(UART1_BASE,packet_send[i]);
                    clearLED();
                    displayBlueLED();
                    SysCtlDelay(5000000);
                }
                clearLED();
                break;
            }
        }

        displayBlueLED();
        SysCtlDelay(5000000);
        clearLED();

        }
    }
