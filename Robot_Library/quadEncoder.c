/*
 * quadEncoder.c
 *
 *  Created on: Feb 22, 2022
 *      Author: emily
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/qei.h"

#include "quadEncoder.h"

/*
// use a quadrature encoder to measure the speed of one wheel of your robot
void quadEnc_init(){
    // Enable the QEI0A & QEAI1A modules and wait for them to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_QEI0)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_QEI1)){}

    // left wheel QEI0: PF0 - Enable & wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
    // right wheel QEI1: PC5 - Enable & wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)){}

    // Configure the quadrature encoder to capture edges on both signals and maintain an absolute position by resetting on index pulses.
    // Using a 1000 line encoder at four edges per line, there are 4000 pulses per revolution;
    // therefore set the maximum position to 3999 as the count is zero based.
    // HUB-ee: 128 counts per rev for A & B - divide by 2 bc ignoring B, divide by 2 again if only using one edge
    //         - 64 if using both rising & falling --> max position = 63
    QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 63);
    QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 63);

    // Enable the quadrature encoder.
    QEIEnable(QEI0_BASE);
    QEIEnable(QEI1_BASE);

    // configure QE velocity
    QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, 100);
    QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, 100);

    // enable QE velocity
    QEIVelocityEnable(QEI0_BASE);
    QEIVelocityEnable(QEI1_BASE);

    // Delay for some time...
}

uint32_t getVelocityLeft(){
    return QEIVelocityGet(QEI0_BASE);
}

uint32_t getVelocityRight(){
    return QEIVelocityGet(QEI1_BASE);
}
*/


void initQE(){
    //setup & initialize

    /*
    while(1){
        if(flag){
            motor stuff
            flag = 0;
        }
    }
    */

    // (GPIO_Read(port, GPIO_PIN_0) == GPIO_PIN_0) && (GPIO_Read(port, GPIO_PIN_2) == GPIO_PIN_2)

}

void QEIntHandler(){
    //set flag
    //clear int
}
