# Emily's Documentation
Originally I was going to type it up all nicely and format it similarly to our other documentation,
but I don't really think my brain has the functionality to make this nice right now.
Also you said that we didn't need the nice formatting so I decided to make this a little more raw.
Apologies for the word vomit that may be about to happen. 

## UART Communication
Uri did a really great job implementing object detection. Unfortunately, we weren't able to perform that as we spent the final day working out 
unexpected serial communication issues and just barely got our pi to tell it to move the robot forward. The addition of the extra IR sensor
caused a lot more trouble than expected (Uri may get more into this in his documentation). It somehow messed with our UART communication. I don't think
it was working alone, though. Uri added obstacle avoidance and autonomous motor forward functions that used obstacle avoidance, but we didn't test it with the
communication until the last day when we realized our communication wasn't working the same way.

I was trying to come up with a new communication protocol and I got partially through that (as can be seen in main.py). My idea sounded great in my head, 
but I ended up stopping after realizing something was wrong with the communication system. A couple hours before the final competition, we finally decided to
just revert our code back to when it was working with the UART and work from there. We just barely had enough time to get it to perform the move forward function
before showing up the final.

I can't quite remember exactly what my plan was, but it was basically to take some user input to set the flags for when the blue goal was detected
or red waypoints were found. The autonomous move forward function would send back a signal when it completed its action (of moving a certain distance) or 
return a signal saying that it didn't complete the action due to and obstacle. This would be used to attempt to calculate distance. Then, the pi would turn
at increments of 45 degree angles to find a new waypoint and move forward towards it. The idea and flowchart for this can be seen in the
(algorithms_flowCharts_diagrams)[finalCompetition/algorithms_flowCharts_diagrams/] directory.

In the future, I would definitely try to make the menu function easier to update with the addition and removal of commands. I also kept changing the communication
protocol as I was trying to figure out how to execute it. I think the current communication protocol is very incorrect from having to revert back to our old 
communication plans. There's also many incorrrect labels as I continued to think through the idea.

## openCV Image Detection


