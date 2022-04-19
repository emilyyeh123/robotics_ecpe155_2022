# Raspberry Pi Python Menu

There are .png files that show how the various menu functions are working. We are working out some kinks in motor functions,
but we have a working menu that allows us to send and receive data. Motor Functions have been set up in the menu, but
not yet implemented on the Tiva as we were having trouble getting the robot to move a certain distance.
The code is setup in Lab 6 main.c, ready for the motor control functions to be implemented as necessary.
The following explains the function of each menu command as it works right now, not necessarily as it should work.
Future plans are explained for each function that is not fully complete.

## 1. Movement

1. Move Forward [(Sample Screenshot 1-1)](raspberryPi/piRobotMenu_moveForward_1-1.png)

   - Asks for a distance (value between 1 and 255)
   - Shows the data it's transmitting and receiving
   - Only receives data if the Tiva has received a start command and move forward command
   - Pi transmits 4 bytes of data: start command, move forward command, distance requested, end command
   - Pi receives 3 bytes of data: start command, `0x31` (arbitrary value we randomly chose and set on the Tiva), end command

Future plans: Remove receiving function on the Pi and replace Tiva's packet sending with motorforward controls.

2. Move Forward [(Sample Screenshot 1-2)](raspberryPi/piRobotMenu_moveBackward_1-2.png)

   - Asks for a distance (value between 1 and 255)
   - Shows the data it's transmitting and receiving
   - Only receives data if the Tiva has received a start command and move backward command
   - Pi transmits 4 bytes of data: start command, move backward command, distance requested, end command
   - Pi receives 3 bytes of data: start command, `0x32` (arbitrary value we randomly chose and set on the Tiva), end command

Future plans: Remove receiving function on the Pi and replace Tiva's packet sending with motorBackward controls.

3. Turn Right [(Sample Screenshot 1-3)](raspberryPi/piRobotMenu_turnRight_1-3.png)
   - Shows the data it's transmitting and receiving
   - Only receives data if the Tiva has received a start command and turn right command
   - Pi transmits 3 bytes of data: start command, turn right command, end command
   - Pi receives 3 bytes of data: start command, `0x33` (arbitrary value we randomly chose and set on the Tiva), end command

Future plans: Remove receiving function on the Pi and replace Tiva's packet sending with turn right controls (hard set to 90 degree turns).

4. Turn Left [(Sample Screenshot 1-4)](raspberryPi/piRobotMenu_turnLeft_1-4.png)
   - Shows the data it's transmitting and receiving
   - Only receives data if the Tiva has received a start command and turn left command
   - Pi transmits 3 bytes of data: start command, turn right command, end command
   - Pi receives 3 bytes of data: start command, `0x34` (arbitrary value we randomly chose and set on the Tiva), end command

Future plans: Remove receiving function on the Pi and replace Tiva's packet sending with turn left controls (hard set to 90 degree turns).

## 2. Request IR Data

3 options: retrieve right [(Sample Screenshot 2-1)](raspberryPi/piRobotMenu_returnRightIRData_2-1.png),
left [(Sample Screenshot 2-2)](raspberryPi/piRobotMenu_returnLeftIRData_2-2.png),
and back [(Sample Screenshot 2-3)](raspberryPi/piRobotMenu_returnBackIRData_2-3.png)
IR sensor data. They all have the same functionality, but each one is set to the proper IR sensor.
Each screenshot shows the function being used twice to show that the value changes as an obstacle moves near/away from the sensor.

- Tiva splits the IR sensor data into two bytes to send to the pi
- Pi converts the 2-byte number back to the original 16-bit integer and prints that value 
