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
# INCLUDE IR COMMANDS HERE

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
		print("\t3) turn right")
		print("\t4) turn left")

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
	print("\n\tHow far would you like to move?")
	print("\tEnter a number between 1 and 255 (movement is tick-based)")
	dist = int(input("\t>>> "))
	while dist < 1 or dist > 255:
		# receive user input
		print("\tINVALID TRY AGAIN")
		dist = int(input("\t>>> "))

	packet = []
	packet.append(struct.pack('B', startCommand))

	if dir == 1:
		packet.append(struct.pack('B', moveForward))
		packet.append(struct.pack('B', dist))
	elif dir == 2:
		packet.append(struct.pack('B', moveBackward))
		packet.append(struct.pack('B', dist))
	elif dir == 3:
		packet.append(struct.pack('B', turnRight))
		packet.append(struct.pack('B', dist))
	elif dir == 4:
		packet.append(struct.pack('B', turnLeft))
		packet.append(struct.pack('B', dist))

	packet.append(struct.pack('B', endCommand))
	# send all requests
	for i in range(len(packet)):
		ser.write(packet[i])
		print("\ttransmitting: ", packet[i])

	time.sleep(0.5)

	respPacket = []
	for i in range(3):
		resp = ser.read()
		resp = struct.unpack('B', resp)
		resp = hex(resp[0])
		print("\tFirst byte of data: ", resp)

		if resp == startCommand:
			while 1:
				resp = ser.read()
				resp = struct.unpack('B', resp)
				resp = hex(resp[0])
				print("\tNext byte of data: ", resp)
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
			pass
		else:
			# default
			print("NOT A VALID OPTION")
	ser.close()
		

if __name__ == "__main__":
	main()
