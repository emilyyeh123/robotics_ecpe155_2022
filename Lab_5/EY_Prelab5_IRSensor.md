```
// Set up PDO, PD3, PD2 for the ADC according to the Tiva Data Sheet
// AIN 7, 4, 5

// Peripheral base addresses.
#define GPIO_PORTD              ((volatile uint32_t *)0x40007000)
#define ADC0                    ((volatile uint32_t *)0x40038000)

// Peripheral register offsets and special fields
enum {
#define   PIN_0              (1 << 0)      // pin 0
#define   PIN_3              (1 << 3)      // pin 3
#define   PIN_2              (1 << 2)      // pin 2
  GPIO_AFSEL  =   (0x420 >> 2),
  ADCSSMUX0   =   (0x040 >> 2),
};



uint32_t dist0;

void initIRSensor(){
    // initialize count variables
    dist0 = 0;

    // Enable ADC Module 0 and GPIO Port D
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}

    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0);

    // enable alternate function
    GPIO_PORTD[GPIO_AFSEL] = PIN_0;
    // Set the pins for each mux
    ADC0[ADCSSMUX0] |= (7 << 0);

    // each pin requires a separate sequence number
    ADCSequenceDisable(ADC0_BASE, 0);

    // Configures the trigger source and priority of a sample sequence.
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

    // Configure a step of the sample sequencer.
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH7 | ADC_CTL_END);

    // Enable sample sequence
    ADCSequenceEnable(ADC0_BASE, 0);
}

uint32_t getSensorData(){
    ADCProcessorTrigger(ADC0_BASE, 0);
    ADCSequenceDataGet(ADC0_BASE, 0, &dist0);
    return dist;
}
```
