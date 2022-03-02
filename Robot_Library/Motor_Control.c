/*
 * Motor_Control.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Emily
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

#include "PWM.h"



void initMotor(uint16_t period){
    initPWM(period);

    // Enable GPIOE peripheral (in1 & in2) and wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}
    // set wheel control outputs for PE1, PE2, PE4, PE5
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5));

    // Enable GPIOA peripheral (standby) and wait for it to be ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}
    // set standby outputs
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, (GPIO_PIN_6 | GPIO_PIN_7));
    // set standby to active high
    GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_6 | GPIO_PIN_7), (GPIO_PIN_6 | GPIO_PIN_7));
}



void motorForward(uint16_t PWLeft, uint16_t PWRight){
    // set pulse width
    setPW(PWLeft, PWRight);

    // based on the HUB-ee control sheet,
    // Forward in1: Low, Forward in2: High
    // left wheel does the opposite (bc wheel placement mirrored)
    // - low pins: PE2 & PE4
    // - high pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_5 | GPIO_PIN_1), (GPIO_PIN_5 | GPIO_PIN_1));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);
}



void motorBackward(uint16_t PWLeft, uint16_t PWRight){
    // set pulse width
    setPW(PWLeft, PWRight);

    // based on the HUB-ee control sheet,
    // Forward in1: High, Forward in2: Low
    // left wheel does the opposite (bc wheel placement mirrored)
    // - high pins: PE2 & PE4
    // - low pins: PE1 & PE5
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_4), (GPIO_PIN_2 | GPIO_PIN_4));
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
}



void motorStop(){
    // stop/brake in1 & in2 High - set all 4 pins high
    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5), (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5));
}



// return global position after some time t
// diameter (cm), length (cm), phi (rad/s), time (s),
// initial position parameter is a 1x3 matrix
/*void ICRPosition(uint8_t d, uint8_t l, uint8_t phi1, uint8_t phi2, uint8_t time, initialPos){
    // initial conditions
    r = d/2; // radius (cm)
    w = ( (r*phi1) / (2*l) ) - ( (r*phi2) / (2*l) );
    R = ( l * (phi1 + phi2) ) / (phi1 - phi2);
}*/

/*
% diameter (cm), length (cm), phi (rad/s), time (s),
% initial position 1x3 matrix
function [Eg] = ICRmatrix(d, l, phi1, phi2, time, initialPos)
    % initial conditions
    r = d/2; % radius (cm)
    w = ( (r*phi1) / (2*l) ) - ( (r*phi2) / (2*l) );
    R = ( l * (phi1 + phi2) ) / (phi1 - phi2);

    % setting initial positions
    x = initialPos(1);
    y = initialPos(2);
    theta = initialPos(3);

    Eg = [R*cos(w*time)*sin(theta)+R*sin(w*time)*cos(theta)+x-R*sin(theta);
          R*sin(w*time)*sin(theta)-R*cos(w*time)*cos(theta)+y+R*cos(theta);
          theta+w*time];
end

% ICR when both wheels have the same speed
function [Eg] = ICRmatrixSameWheel(d, l, phi, time, initialPos)
    % initial conditions
    r = d/2; % radius (cm)

    % setting initial positions
    x = initialPos(1);
    y = initialPos(2);
    theta = initialPos(3);

    Eg = [x+r*time*phi*cos(theta);
          y+r*time*phi*sin(theta);
          theta];
end
*/
