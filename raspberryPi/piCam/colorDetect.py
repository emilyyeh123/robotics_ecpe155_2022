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
	#for i in range (5):
		#camera.start_preview(fullscreen = False, window = (100, 200, 1280, 720))
		#time.sleep(3)
		#camera.stop_preview()
		#camera.capture('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/piImages/img%s.jpg' % i)

	'''
	img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/piImages/img%s.jpg' % 4)
	hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	coord = [720, 360]
	hsvColor = hsv[coord[1],coord[0]]
	print(hsvColor)
	imgPoint = cv2.circle(img, coord, radius = 0, color = (0,0,0), thickness = 10)
	# 3, 159, 125 
	lowerRed = np.array([0,60,60])
	upperRed = np.array([20,180,180])
	mask = cv2.inRange(hsv, lowerRed, upperRed)
	#cv2.imshow("displayPoint", imgPoint)
	cv2.imshow("mask", mask)
	cv2.waitKey(0)
	'''

	# take 5 pictures and do color detection
	for i in range(5):
		#camera.capture('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/img.jpg')
		img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/piImages/img%s.jpg' % i)

		# hue, saturation, brightness
		hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

		lowerRed = np.array([0,60,60])
		upperRed = np.array([20,180,180])
		mask = cv2.inRange(hsv, lowerRed, upperRed)
		cv2.imshow("mask", mask)
		cv2.waitKey(0)

	cv2.destroyAllWindows()

if __name__ == "__main__":
	main()
