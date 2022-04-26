#!/usr/bin/python3

import picamera
import time

def main():
	camera = picamera.PiCamera()
	camera.rotation = 180
	camera.resolution = (1280, 720)
	camera.annotate_text = "Hello!"
	camera.capture('/home/pi/Desktop/img.jpg')

	# window = (screen coord x, y, resolution width, height)
	#camera.start_preview(fullscreen = False, window = (100, 200, 1280, 720))
	#time.sleep(3)
	#camera.stop_preview()

if __name__ == "__main__":
	main()
