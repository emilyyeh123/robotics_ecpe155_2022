

/**
 * main.c
<<<<<<< HEAD
 * The purpose of this program is to test the PI control function
 * The robot will be set to a specific speed.
 * The timer will kick in and correct the robots orientation every 2 seconds
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


// can receive up to 8 bytes of data
// 3 bytes reserved for start (0xAA), command, end (0x55)
char packet_rec[8];
char packet_send[8];
int turnMultiplier;

int main(void)
{
    //initSerial();
    initIRSensor();
    initLED();
    initMotor();

    initQEInterrupt();


      // initRecPacket(packet_rec);
        //initSendPacket(packet_send);



/*        storeReceivedPacket(packet_rec);

        clearLED();
        SysCtlDelay(5000000);

        performAction(packet_rec, packet_send);

        objectAvoid();
*/
while(1){
int dist0 = getSensorData0();
int dist1 = getSensorData1();
int dist2 = getSensorData2();
int dist3 = getSensorData3();
SysCtlDelay(1000000);
}



/*
        SysCtlDelay(2000000);

        objectAvoid();
        SysCtlDelay(1000000);
        clearLED();
        SysCtlDelay(5000000);
*/





}
