# Pulse Width Modulation (PWM)

In the data sheet:
- Section 11.4.5 describes PWM Mode for a General Purpose Timer
- General PWM information found in section 20
- From Table 20-1, pg 1233
  - Choose PWM Master Control `PWM0` = `PB6`
  - Choose PWM Master Control `PWM1` = `PB7`

In Peripheral Driver Library
- Section 21.3 gives a PWM programming example
- Use 14.3 GPIO UART example (but replace UART w/ PWM)

## Pseudocode
`#include driverlib/pwm.h` <br>

Enable PWM0 peripheral <br>
`SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);`

Wait for the PWM0 module to be ready. <br>
`while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){}`

Enable & wait for GPIOB

set pins as outputs <br>
`GPIOPinTypePWM(port_base, pin)` <br>
`GPIOPinConfigure(pin_PWM)`

configure generator <br>
`PWMGenConfigure(pwm_base, pwm_generator, period)`

set period <br>
`PWMGenPeriodSet(PWM_Base, PWM_generator, period)`

set duty cycle <br>
`PWMPulseWidthSet(pwm_base, pwmOutBit, pulseWidth)`

enable output <br>
`PWMOutputState(pwm_base, pwmOutBit, true)`

start generator timer <br>
`PWMGenEnable(pwm_base, pwmGenerator)`

## helpful info
**Make sure to setup both wheels and have a way to modify the duty cycles** 

**Duty Cycle changes speed of wheel**
- think fsm clock
- falling edge to next falling edge is 100%
- higher duty cycle = faster wheel speed
