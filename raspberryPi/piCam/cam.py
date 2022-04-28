#!/usr/bin/python3

import picamera
import time

def main():
	# setup camera - orient right-side up and shrink resolution
	camera = picamera.PiCamera()
	camera.rotation = 180
	camera.resolution = (1280, 720)

	#for i in range (3):
	camera.start_preview(fullscreen = False, window = (100, 200, 1280, 720))
	time.sleep(3)
	camera.stop_preview()
	camera.capture('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/img%s.jpg' % 3)

	# window = (screen coord x, y, resolution width, height)
	#camera.start_preview(fullscreen = False, window = (100, 200, 1280, 720))
	#time.sleep(13)
	#camera.stop_preview()

if __name__ == "__main__":
	main()
