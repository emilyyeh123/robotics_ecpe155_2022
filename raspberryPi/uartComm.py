#!/usr/bin/python3

import serial
import time
import struct

# packet structure
startCommand = 0xAA
endCommand = 0x55

# Movement Commands
moveForward = 0x01
moveBackward = 0x02
turnRight = 0x03
turnLeft = 0x04

# IR Commands
rightIR = 0x11
leftIR = 0x12
backIR = 0x13

# initialize serial
ser = serial.Serial("/dev/ttyS0", 9600) 



def mainMenu():
	# display UI
	print("\nWhat would you like the robot to do?")
	print("0) exit")
	print("1) move")
	print("2) retreive IR Data")

	# receive user input
	menuInp = int(input(">>> "))
	return menuInp

def moveMenu():
	while 1:
		print("\tWhich direction would you like to move?")
		print("\t0) cancel")
		print("\t1) move forward")
		print("\t2) move backward")
		print("\t3) turn right 90 degrees")
		print("\t4) turn left 90 degrees")

		# receive user input
		directionInp = int(input("\t>>> "))
		if directionInp == 0:
			return
		elif directionInp < 1 or directionInp > 4:
			# default
			print("\tNOT A VALID OPTION\n")
		else:
			sendMovePacket(directionInp)
			return

def sendMovePacket(dir):
	packet = []
	packet.append(struct.pack('B', startCommand))

	if dir == 1:
		print("\n\tHow far would you like to move?")
		print("\tEnter a number between 1 and 255 (movement is tick-based)")
		dist = int(input("\t>>> "))
		while dist < 1 or dist > 255:
			# receive user input
			print("\tINVALID TRY AGAIN")
			dist = int(input("\t>>> "))

		packet.append(struct.pack('B', moveForward))
		packet.append(struct.pack('B', dist))
	elif dir == 2:
		print("\n\tHow far would you like to move?")
		print("\tEnter a number between 1 and 255 (movement is tick-based)")
		dist = int(input("\t>>> "))
		while dist < 1 or dist > 255:
			# receive user input
			print("\tINVALID TRY AGAIN")
			dist = int(input("\t>>> "))

		packet.append(struct.pack('B', moveBackward))
		packet.append(struct.pack('B', dist))
	if dir == 3:
		packet.append(struct.pack('B', turnRight))
	elif dir == 4:
		packet.append(struct.pack('B', turnLeft))


	packet.append(struct.pack('B', endCommand))
	# send all requests
	for i in range(len(packet)):
		ser.write(packet[i])
		print("\ttransmitting: ", packet[i])

	time.sleep(0.5)

	respPacket = []
	resp = ser.read()
	resp = struct.unpack('B', resp)
	resp = resp[0]
	print("\tFirst byte of data (converted to hex): ", hex(resp))

	if resp == startCommand:
		while 1:
			resp = ser.read()
			resp = struct.unpack('B', resp)
			resp = resp[0]
			print("\tNext byte of data (converted to hex): ", hex(resp))
			if resp != endCommand:
				respPacket.append(resp)
			else:
				break

def sendIRCommand():
	while 1:
		print("Which IR sensor would you like to retreive data from?")
		print("\t0) cancel")
		print("\t1) Right IR Sensor")
		print("\t2) Left IR Sensor")
		print("\t3) Back IR Sensor")

		# receive user input
		IRinp = int(input("\t>>> "))
		if IRinp == 0:
			return
		elif IRinp < 1 or IRinp > 3:
			# default
			print("\tNOT A VALID OPTION\n")
		else:
			break

	packet = []
	packet.append(struct.pack('B', startCommand))

	if IRinp == 1:
		packet.append(struct.pack('B', rightIR))
	elif IRinp == 2:
		packet.append(struct.pack('B', leftIR))
	elif IRinp == 3:
		packet.append(struct.pack('B', backIR))

	packet.append(struct.pack('B', endCommand))
	# send all requests
	for i in range(len(packet)):
		ser.write(packet[i])
		print("\ttransmitting: ", packet[i])

	time.sleep(0.5)

	respPacket = []
	resp = ser.read()
	resp = struct.unpack('B', resp)
	resp = resp[0]
	print("\tFirst byte of data (converted to hex): ", hex(resp))

	if resp == startCommand:
		while 1:
			resp = ser.read()
			resp = struct.unpack('B', resp)
			resp = resp[0]
			print("\tNext byte of data (converted to hex): ", hex(resp))
			if resp != endCommand:
				respPacket.append(resp)
			else:
				break

def main():
	while 1:
		menuInp = mainMenu()

		if menuInp == 0:
			return
		elif menuInp == 1:
			# call move function
			moveMenu()
		elif menuInp == 2:
			# call IR function
			sendIRCommand()
		else:
			# default
			print("NOT A VALID OPTION")
	ser.close()
		

if __name__ == "__main__":
	main()
