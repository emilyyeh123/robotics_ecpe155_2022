# Raspberry Pi Python Menu

There are .png files that show how the various menu functions are working. After each menu action has been completed and the Pi has been notified, 
it will respawn the main menu to continue receiving actions. Motor Functions have been set up in the menu, but
not yet implemented on the Tiva as we were having trouble getting the robot to move a certain distance.
The code is setup in Lab 6 main.c, ready for the motor control functions to be implemented as necessary.
The following explains the function of each menu command as it works right now, not necessarily as it should work.
Future plans are described for each function that is not fully complete.

## 1. Movement

- User is prompted to make the robot move forward [(Screenshot 1-1)](raspberryPi/piRobotMenu_moveForward_1-1.png),
backward [(Screenshot 1-2)](raspberryPi/piRobotMenu_moveBackward_1-2.png),
turn right [(Sample Screenshot 1-3)](raspberryPi/piRobotMenu_turnRight_1-3.png),
or turn left [(Sample Screenshot 1-4)](raspberryPi/piRobotMenu_turnLeft_1-4.png).
- If linear motion is selected, either forward or backward, user will be prompted to select a distance in centimeters between 0 and 255 cm. This command and parameters will then be transmitted to the Tiva. If the Tiva has recieved the correct commands (start command and move forward/backward command), data will be sent back to the Pi to show that data from the pi is being sent and received properly.
   - Pi transmits 4 bytes of data: start command, move forward command, distance requested, end command
   - Pi receives 3 bytes of data: start command, `0x31` or `0x32` (arbitrary values we randomly chose and set on the Tiva), end command
   - Future plans: Remove receiving function on the Pi and replace Tiva's packet sending with motorforward/backward controls.
- If the user selects a right or left turn, there are no additional parameters. It is assumed that the turn will be 90 degrees either counterclock-wise or clock-wise. The command will then be transmitted to the Tiva for execution.
   - Pi transmits 3 bytes of data: start command, turn command, end command
   - Pi receives 3 bytes of data: start command, `0x33` or `0x34` (arbitrary values we randomly chose and set on the Tiva), end command
   - Future plans: Remove receiving function on the Pi and replace Tiva's packet sending with turn right/left controls (hard set to 90 degree turns).
- Once the commands have been transmitted, the Pi will enter a recieving mode where it will await data transmitted from the Tiva to indicate that the motion was completed. This data will be stored in a character array called `respPacket`.


## 2. Request IR Data

3 options: retrieve right [(Sample Screenshot 2-1)](raspberryPi/piRobotMenu_returnRightIRData_2-1.png),
left [(Sample Screenshot 2-2)](raspberryPi/piRobotMenu_returnLeftIRData_2-2.png),
and back [(Sample Screenshot 2-3)](raspberryPi/piRobotMenu_returnBackIRData_2-3.png)
IR sensor data. They all have the same functionality, but each one is set to the proper IR sensor.
Each screenshot shows the function being used twice to show that the value changes as an obstacle moves near/away from the sensor.

- Tiva splits the IR sensor data into two bytes to sends to the pi
- Pi converts the 2-byte number back to the original 16-bit integer and prints that value

Future Plans: convert this number to a human-understandable range
