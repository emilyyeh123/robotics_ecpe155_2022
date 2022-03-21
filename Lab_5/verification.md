To verify that the sensors work, only include the IR sensor code in main.
Initialize the IR sensor and call getSensorData for each sensor.
Then, add a breakpoint to the beginning of the while loop.

```
int main(){
    initIRSensor();

    while(1){
        uint32_t sensor0 = getSensorData0();
        uint32_t sensor1 = getSensorData1();
        uint32_t sensor2 = getSensorData2();
    }
}
```

Include sensor0, sensor1, and sensor2 in the expressions tab and run the code.
- Low values (around 300) are returned when nothing is blocking each sensor.
- High values (up to about 5000) are returned when I use my hand to block the sensor.


Adding the breakpoint allows the user to continuously hit the run button as necessary. Each time the run button is hit, the values for each sensor will get updated.

**Issue 1: sensor1 always returned the exact same number**
- Solution: switch from using PD1 to PD3 because PD1 was getting mixed up with PB7.

**Issue 2: values would not update immediately**
- Problem: If I moved my hand in front of the sensor, the value would remain approximately the same on the following run, then jump to the more appropriate higher value after another run.
- Solution: in the getSensorData function, add a very brief delay between the processorTrigger and the dataGet calls to allow enough time for the sensor values to update properly upon calling the function.
