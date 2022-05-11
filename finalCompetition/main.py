#!/usr/bin/python3

import serial
import time
import struct

# packet structure
START_COMMAND = 0xAA
END_COMMAND = 0x55
rightIR = 0x11

# Movement Commands
MOVE_TOWARD_WP = 0X05
NO_WP_IN_SIGHT = 0x06
TASK_COMPLETE = 0x07

# initialize serial
ser = serial.Serial("/dev/ttyS0", 9600) 
#ser.flushInput()

# initialize packets
#sendPacket = []
recPacket = []



# return boolean input
def boolInp():
	while True:
		try:
			inp = int(input(">> yes (1) or no (0):   "))
			if inp == 1:
				return True
			elif inp == 0:
				return False
			else:
				print("Try again")
		except:
			print("INVALID INPUT")



# if waypoint seen, send move forward command
# otherwise request to turn at 45 degree angle
def seekWaypoint():
	print("\nDoes the robot see a blue circle?")
	if boolInp() == True:
		print("\tMoving Towards Blue Circle")
		ser.write(struct.pack('B', MOVE_TOWARD_WP))
		return True

	print("\nDoes the robot see a red circle?")
	if boolInp() == True:
		print("\tMoving Towards Red Circle")
		ser.write(struct.pack('B', MOVE_TOWARD_WP))
		return True

	print("\nThe robot sees no waypoint, turn 45 degrees and try again.")
	return False



# receive response packet, continue receiving until endCommand received
def recResp():
	# wait to receive response that action has been completed
	recPacket.clear()
	respPacket = []
	resp = ser.read()
	resp = struct.unpack('B', resp)
	resp = resp[0]

	if resp == startCommand:
		while 1:
			resp = ser.read()
			resp = struct.unpack('B', resp)
			resp = resp[0]
			if resp != endCommand:
				respPacket.append(resp)
			else:
				return True



def main():
	# initialize flags
	atBlue = False
	atRed = False
	seeCircle = False
	isRed = False
	isBlue = False
	sendEndCommand = False

	'''
	while True:
		# send start command
		ser.write(struct.pack('B', START_COMMAND))

		# clear packets
		#sendPacket.clear()
		recPacket.clear()

		# check if robot is currently at waypoint
		# supposed to use image processing, but that was unable to be fully implemented
		# instead, for current purposes, takes in user input
		while True:
			try:
				inp = int(input("\nIs the robot at a blue (0) or red (1) circle (all other options mean neither)?   "))
				if inp == 0:
					atBlue = True
					break
				elif inp == 1:
					atRed = True
					break
				else:
					print("Not currently at a waypoint. Turn and find new waypoint.")
					break
			except:
				print("INVALID INPUT")

		# exit loop if robot is at blue circle
		if atBlue == True:
			print("GOAL ACHIEVED!")
			break
		# if robot is at red circle
		elif atRed == True:
			print("Currently at red waypoint; Plotting point on map as red waypoint")

		# look for waypoint
		while seekWaypoint() == False:
			print("Searching for new waypoint")
			# send command to turn 45 degrees
			ser.write(struct.pack('B', NO_WP_IN_SIGHT))
			ser.write(struct.pack('B', END_COMMAND))
			time.sleep(0.5)
			#if recResp() == True:
				#print("Turned 45 degrees")

		print()
	'''
	packet = []
	packet.append(struct.pack('B', START_COMMAND))
	packet.append(struct.pack('B', 0x04))
	print("\tRight Sensor Data is: ", end = "")

	packet.append(struct.pack('B', END_COMMAND))
	# send all requests
	for i in range(len(packet)):
		ser.write(packet[i])
		print("\ttransmitting: ", packet[i])

	time.sleep(0.5)

	respPacket = []
	resp = ser.read()
	resp = struct.unpack('B', resp)
	resp = resp[0]
	#print("\tFirst byte of data (converted to hex): ", hex(resp))

	if resp == START_COMMAND:
		while 1:
			resp = ser.read()
			resp = struct.unpack('B', resp)
			resp = resp[0]
			#print("\tNext byte of data (converted to hex): ", hex(resp))
			if resp != END_COMMAND:
				respPacket.append(resp)
			else:
				break

	# CONVERT IR DATA
	# bitshift upper 8 bits and OR with lower 8 bits
	irData = (respPacket[0] << 8) | respPacket[1]
	print(irData)

	ser.close()

if __name__ == "__main__":
	main()

