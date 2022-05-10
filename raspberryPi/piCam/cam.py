#!/usr/bin/python3

import picamera
import time
import cv2
import numpy as np
import PIL
from PIL import Image
#import matplotlib.pyplot as plt


def main():
	# setup camera - orient right-side up and shrink resolution
	camera = picamera.PiCamera()
	camera.rotation = 180
	camera.resolution = (1280, 720)

	# take 5 pictures in 3 sec intervals and store them in piImages
	for i in range (10):
		camera.start_preview(fullscreen = False, window = (100, 200, 1280, 720))
		time.sleep(3)
		camera.stop_preview()
		camera.capture('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/moreImages/img%s.jpg' % i)

if __name__ == "__main__":
	main()
