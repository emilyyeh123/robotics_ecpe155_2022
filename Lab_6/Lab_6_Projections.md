# Lab 6 Challenges and Solutions

  ## Completed Work 
   ### Tiva ticks to velocity
  Serial communication has been successfully implemented between the Raspberry Pi and the Tiva. However, motor control is through the Raspberry Pi is still under evaluation.
  To navigate the robot from an initial position to a specified point on a coordinate plane, the motor control source code had to be restructured. 
    - Previously, the source code was based on the ticks counted by the quadrature encoder. This allowed for the speed of each wheel on the robot to be specified by the user. It proved very effective at rotating the robot and showed some promise in rectifying robot speed if the robot began to deviate from a straight line.
      However, this apporach relied on a global counter being constantly called and reset as it was passed between functions that controlled motor functions. 
  The proposed solution to this issue was to completely revise the motor control source code included in the Robot Library folder as: [Motor_Control.c](Robot_Library/Motor_Control.c).
  The current motor control functions was designed to minimize the number of variables that was passed from the user to the robot. Instead of taking three parameters, one to call the function, and two to specify speed, the speed of the robot was kept static and a distance to travel was specified by the user. 
  
  To arrive at this, experiments were conducted to determine a low to moderate robot speed that allwoed the robot to travel in a straight line (approximately straight). The PWM was initialized at 800 and the inital duty cycle was assumed at 300.
  The robot was run forward and backward to monitor the performance of each wheel under the a duty cycle of 300 for each wheel. The duty cycle was then finely adjusted until the robot would move in a straight line. These wheel speed values, 300 for the left wheel and 311 for the right, were then kept static for all linear motion in the motor control functions.
  
  Once the wheel speed was kept static, further experiments were run to determine the time it would take the robot to travel 40 cm. A stopwatch was used to capture time and and average was taken from three data points. That average was 2.95 seconds, rounded to 3 seconds. The velocity of the robot then at the given wheel speeds was 40cm/3sec or `13.3 cm/s`.
  
  With the velocity of the robot in hand a new function was created in Motor_Control.c that could take in a single distance parameter, given in centimeters, and determine the time necessesary for the robot to reach a given point. This was significant because a timer could then be developed to updated the robots local position at regular time intervals.
  
   ### Raspberry Pi User Interface
  The user interface has been completed for simple navigation function on the robot and to recieve sensor data. This coupled with the updated basic motor control source code on the Tiva should allow the Raspberry Pi to wireless control simple motion on the robot. 
  
  Serial communication between the two boards has been successful. 
  
  
  
  ## Tiva Work in Progress
  A navigation function, `nav_xy`, was written with this foundation to allow the robot to orient itself and navigate to a user defined position within 2.55 meters of the robots initilized position.
  The code for this, and other functions that rely on a velocity or time interrupts, have successfully compiled in the main code included in the Lab_6 folder: [main.c](Lab_6/main.c). However, there seems to be issues in the delay function that controls when the robot should stop forward to backward motion. This is currently under review and resolutions are the next top objective.
  
  Code has been added to the Lab_6 main.c file to forward IR sensor data to the raspberry pi to toggle the simple Object Avoidence functions. This is currently being validated. 
  
  
  ## Raspberry Pi Work in Progress
  The list of commands for the Raspberry Pi will be expanded to include more and more complex robot bahavioral control functions for the user to select.
  
  
