# Pulse Width Modulation (PWM)

The pins selected for this lab will be 
- Pulse Width Modulator Zero `PWM0`
  - This corresponds to J2 Pin 7 on the Tiva Board marked as `PB6`
- Pulse Width Modulator One `PWM1`  = `PB7`
  - This corresponds to J2 Pin 6 on the Tiva Board marked as `PB7`

The TivaWare Peripheral Driver Library was the main reference material
- Section 21 describes all functions related to PWM
  - Section 21.3 offers a programming example which was taken as a template during code formulation
- The Tiva C Series TM4C123G LaunchPad Evaluation Board User's Guide was also used to help map pins

## Pseudocode
Note that repeated coding structures will only be written once

`#include driverlib/pwm.h` <br>

Enable PWM0 and PWM1 Peripheral Modules <br>
`SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);`
`SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);`

Enable the GPIO Peripheral Modules for the B port (GPIOB)
`SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);`

set pins as PWM outputs <br>
`GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6)` <br>
`GPIOPinConfigure(GPIO_PB6_PWM0)`

configure two of the four generators so that two separate pulses are controlled  <br>
`PWMGenConfigure(PWM0_BASE, PWM_GEN0, PWM_GEN_MODE_DOWN)`
  - PWM_GEN_MODE_DOWN specifies the counting mode

set period of each generator <br>
`PWMGenPeriodSet(PWM0_BASE, PWM0_GEN0, (user-defined vairable for period))`

set duty cycle <br>
`PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, (user defined variable for pulseWidth))`

enable output <br>
`PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT , true)`

start each generator timer <br>
`PWMGenEnable(PWM0_BASE, PWM_GEN0)`

## helpful info
**Make sure to setup both wheels and have a way to modify the duty cycles** 

**Duty Cycle changes speed of wheel**
- The bit numbers must match up. The signals will look very strange if they don't.
