# Infrared Sensors and Object Avoidance

The purpose of this lab is to integrate three IR sensors into our robot and program a low level means of using those sensors to avoid objects.
  - We chose to attach the IR sensors to the chasis of the robot at the rear, left, and right sides. The front was excluded from thought because the bumper was already installed there.

## Pseudocode

- Configure the GPIO pins to use Analog to Digital Conversion (ADC) functions. 
  - This was very difficult since the path to set the registries was less clear to me. Luckily, Emily spearpointed this section and the code looks amazing.

- Use sample sequencers to retrieve data from each IR sensor

  ```
  // These functions include:
  ADCSequenceConfigure() or ADCSequenceStepConfigure()
  ```
  - We decidede to move forward with the ADCSequenceStepConfigure function since the programming example in section 4.3 of the Peripheral Driver Library illustrates its use.
  
  - I was thinking that we could use the ADC_TRIGGER_EXTERNAL function as the configuration parameter but my super smart teammate suggested using a timer or processor generated trigger which makes much more sense.
  -  This data must be stored in a specific address once the signal is retrived

- We'll need to test the incoming data and determine the maximum and minimum limits of the incoming signals.
  - We know the sensors are valid from 0 to 30 cm so by moving an objects between those ranges and monitoring the output, we could determine the maximum and minimum signals.

- Once we have the signal limits, we can determine a general threshold distance for which we want the robot to perform actions.
  ```
  // an example might be
  getIRSensor1Signal();
  if (that value) >= (arbitary about in cm){
    Robot will move to avoid the object
  }
  ```
  
  - Once we have all IR sensors installed properly, we must test the system and determine if the robot behavior is expected.
  
