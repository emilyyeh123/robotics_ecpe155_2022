#!/usr/bin/python3

import picamera
import time
import cv2
import numpy as np
import PIL
from PIL import Image
#import matplotlib.pyplot as plt


def main():
	'''
	#img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/wallExamples/img%s.jpg' % 1)
	#img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/moreImages/img%s.jpg' % 4)
	hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	# 720, 360 is middle of frame
	coord = [720, 500]
	hsvColor = hsv[coord[1],coord[0]]
	#imgPoint = cv2.circle(img, coord, radius = 0, color = (0,0,0), thickness = 10)
	# 3, 159, 125 
	lowerRed = np.array([0,60,60])
	upperRed = np.array([100,180,180])
	#print("HSV:\t\t ", hsvColor)
	#print("Lower Bounds:\t ", lowerRed)
	#print("Upper Bounds:\t ", upperRed)
	
	for i in range(3):
		if not(hsvColor[i] >= lowerRed[i] and hsvColor[i] <= upperRed[i]):
			print(False)
			break
		else:
			if i == 2:
				print(True)
	
	
	for hsvPoint, lowerPoint, upperPoint in zip(hsvColor, lowerRed, upperRed):
		if hsvPoint < lowerPoint or hsvPoint > upperPoint:
			print(False)
			break
		else:
			if hsvPoint == hsvColor[2]:
				print(True)
	

	mask = cv2.inRange(hsv, lowerRed, upperRed)
	imgPoint = cv2.circle(img, coord, radius = 0, color = (256,0,0), thickness = 20)
	cv2.imshow("displayPoint", img)
	cv2.imshow("mask", mask)
	cv2.waitKey(0)

	'''

	# take 5 pictures and do color detection
	for i in range(5):
		#camera.capture('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/img.jpg')
		#img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/moreImages/img%s.jpg' % (i+3))
		img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/wallEx/img%s.jpg' % 1)

		# hue, saturation, brightness
		hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

		lowerRed = np.array([0,60,60])
		upperRed = np.array([100,180,180])
		mask = cv2.inRange(hsv, lowerRed, upperRed)
		cv2.imshow("image", hsv)
		cv2.imshow("mask", mask)
		cv2.waitKey(0)

	

	cv2.destroyAllWindows()

if __name__ == "__main__":
	main()
