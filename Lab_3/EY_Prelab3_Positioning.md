# Outline an approach to use for robot motor control such that you can define a position and have the robot reach it



## Quadrature Encoder (QE) Explanation & Implementation
- A quadrature encoder has 2 signals (in this case, QEA and QEB).
- The total number of QE ticks in each wheel is 128
  - This number is reduced to 64 if we are counting both edges, one signal
  - This number is reduced to 32 if we are counting a single edge, one signal
  - Reducing it to single edge would make position control less precise

In [interrupt.c](Robot_Library/interrupt.c), we created a QE interrupt handler to count each tick recieved by one signal (QEA) on both rising & falling edges.

- Interrupt psuedocode:
  ```
  // Using PA3 and PA4 for QEA and QEB on left wheel
  SysCtlPeripheralEnable(gpioPort);
  while(!SysCtlPeripheralReady(gpioPort)){}

  // Register the port-level interrupt handler. This handler is the first level interrupt handler for all the pin interrupts
  GPIOIntRegister(portBase, QEInterruptHandler);

  // Set Input pins to read encoder data
  GPIOPinTypeGPIOInput(portBase, Pins);

  // Set pins for input signal from encoder
  // checking for both edges, so 64 ticks is one revolution
  GPIOIntTypeSet(portBase, pins, GPIO_BOTH_EDGES);

  // Enable the Interrupts
  GPIOIntEnable(portBase, pins);
  ```

- Interrupt handler psuedocode:
  ```
  //clear interrupt
  GPIOIntClear(portBase, pins);
  
  increment left count if left wheel recieves signal
  if(GPIOPinRead(portBase, leftPin) == leftPin){}
  
  increment right count if right wheel recieves signal
  if(GPIOPinRead(portBase, rightPin) == rightPin){}
  ```

## Measuring Distance
- The number of ticks in one revolution is 64 with both edges, one signal
- The circumference of a circle is equal to 2 * pi * r
- The radius of each wheel is 3cm, so the circumference of each wheel is about 18.85cm

This means that the system moves about 18.85cm forward/backward in 64 ticks

*In the future, we want to implement velocity & ICR to test distance & movement, but for now we will simply account for distance to reach a specific destinations.
Velocity will require the use of timers.*



## Implementing Positioning
- initialize count variables to 0 in initQEInterrupt function
- declare global variable `totalRev` to keep track of total revolutions (initialize to 0 in initQEInterrupt)
  - resets anytime there's a direction change 
- Modify Interrupt Handler:
  - Instead of flashing LED at every tick, display LED every time wheel has achieved one revolution.
    - if one revolution, reset count to 0 and display led; otherwise, continue incrementing count<br>
      ```
      if count > 63
        display led
        set count to 0
      else
        count++
      ```
    - alternatively can wait until both wheels have gone a full revolution (due to imperfect hardware, counts may be slightly off);
      this can be implemented to the end of the handler
      ```
      if leftCount > 63 && rightCount > 63
        display led
        totalRev++ // increment total revolutions
        set right & left count to 0 // reset left and right counts to zero
      ```
      - with this, we would be able to claim that the system has moved approximately 18.85 cm (+/- error) everytime we see the LED flash
  - Create function that takes in specific distance and stops robot at specified distance
    ```
    moveDist(int distance) // maybe make int 16 bits?
      fullRevs = distance/18.85 // defines the amount of full revolutions to move
      excessDistance = distance % 18.85 // defines excess distance
      excessRev = excessDistance*64 / 18.85 // multiply excess distance by 64 ticks and divide by circumference to get excess revolutions

      if(totalRev == fullRevs)
        if leftCount > excessRev && rightCount > excessRev
          stopmotor
    ```




