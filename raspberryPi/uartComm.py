#!/usr/bin/python3

import serial
import time
import struct
import picamera

# packet structure
startCommand = 0xAA
endCommand = 0x55
ACTION_COMPLETE = 0x27

# Movement Commands
MOVE_TOWARD_WP = 0x08
moveForward = 0x01
moveBackward = 0x02
turnRight = 0x03
turnLeft = 0x04
moveToXY = 0x05

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
	print("3) take picture")

	# receive user input
	try:
		menuInp = int(input(">>> "))
		return menuInp
	except:
		return

def moveMenu():
	while 1:
		print("\n\tWhich direction would you like to move?")
		print("\t0) cancel")
		print("\t1) move forward")
		print("\t2) move backward")
		print("\t3) turn right 90 degrees")
		print("\t4) turn left 90 degrees")
		print("\t5) automatically move forward (maze navigation)")

		# receive user input
		try:
			directionInp = int(input("\t>>> "))
		except:
			print("\tMUST INPUT INTEGER. TRY AGAIN.")

		if directionInp == 0:
			return
		elif directionInp < 1 or directionInp > 5:
			# default
			print("\tINTEGER MUST BE BETWEEN 0 AND 5. TRY AGAIN.\n")
		else:
			sendMovePacket(directionInp)
			break

def promptDistance(strDirectionPrompt):
	print()
	print(strDirectionPrompt)
	print("\tEnter a number between 1 and 255 (distance in cm)")
	print("\tEnter 0 to cancel")

	# receive user input
	while 1:
		try:
			dist = int(input("\t>>> "))
		except:
			print("\tMUST INPUT INTEGER. TRY AGAIN.")
		if dist < 0 or dist > 255:
			print("\tINTEGER MUST BE BETWEEN 1 AND 255. TRY AGAIN.")
		else:
			break

	return dist

def sendMovePacket(dir):
	packet = []
	packet.append(struct.pack('B', startCommand))

	if dir == 1:
		dist = promptDistance("\tHow far would you like to move?")
		if dist == 0:
			return
		packet.append(struct.pack('B', moveForward))
		packet.append(struct.pack('B', dist))
	elif dir == 2:
		dist = promptDistance("\tHow far would you like to move?")
		if dist == 0:
			return
		packet.append(struct.pack('B', moveBackward))
		packet.append(struct.pack('B', dist))
	elif dir == 3:
		packet.append(struct.pack('B', turnRight))
	elif dir == 4:
		packet.append(struct.pack('B', turnLeft))
	elif dir == 5:
		packet.append(struct.pack('B', MOVE_TOWARD_WP))

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
		print("\n\tWhich IR sensor would you like to retreive data from?")
		print("\t0) cancel")
		print("\t1) Right IR Sensor")
		print("\t2) Left IR Sensor")
		print("\t3) Back IR Sensor")

		# receive user input
		try:
			IRinp = int(input("\t>>> "))
			if IRinp == 0:
				return
			elif IRinp < 1 or IRinp > 3:
				# default
				print("\tNOT A VALID OPTION\n")
			else:
				break
		except:
			print("\tNOT A VALID OPTION\n")

	packet = []
	packet.append(struct.pack('B', startCommand))

	if IRinp == 1:
		packet.append(struct.pack('B', rightIR))
		print("\tRight Sensor Data is: ", end = "")
	elif IRinp == 2:
		packet.append(struct.pack('B', leftIR))
		print("\tLeft Sensor Data is: ", end = "")
	elif IRinp == 3:
		packet.append(struct.pack('B', backIR))
		print("\tBack Sensor Data is: ", end = "")

	packet.append(struct.pack('B', endCommand))
	# send all requests
	for i in range(len(packet)):
		ser.write(packet[i])
		#print("\ttransmitting: ", packet[i])

	time.sleep(0.5)

	respPacket = []
	resp = ser.read()
	resp = struct.unpack('B', resp)
	resp = resp[0]
	#print("\tFirst byte of data (converted to hex): ", hex(resp))

	if resp == startCommand:
		while 1:
			resp = ser.read()
			resp = struct.unpack('B', resp)
			resp = resp[0]
			#print("\tNext byte of data (converted to hex): ", hex(resp))
			if resp != endCommand:
				respPacket.append(resp)
			else:
				break

	# CONVERT IR DATA
	# bitshift upper 8 bits and OR with lower 8 bits
	irData = (respPacket[0] << 8) | respPacket[1]
	print(irData)

def captureImg():
	# setup camera - orient right-side up and shrink resolution
	camera = picamera.PiCamera()
	camera.rotation = 180
	camera.resolution = (1280, 720)

	# take 5 pictures in 3 sec intervals and store them in piImages
	for i in range (10):
		#camera.start_preview(fullscreen = False, window = (100, 200, 1280, 720))
		time.sleep(3)
		#camera.stop_preview()
		camera.capture('/home/pi/bishop_ecpe155_2022/raspberryPi/INSERTFILE/img%s.jpg' % i)
		print("Picture ", i)

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
		elif menuInp == 3:
			captureImg()
		else:
			# default
			print("NOT A VALID OPTION")
	ser.close()
		

if __name__ == "__main__":
	main()
