#!/usr/bin/python3

import picamera
import time
import cv2
import numpy as np
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

	# open camera in window, stay open for a few seconds before closing again
	# window = (screen coord x, y, resolution width, height)
	#camera.start_preview(fullscreen = False, window = (100, 200, 1280, 720))
	#time.sleep(13)
	#camera.stop_preview()

	'''
	# take 5 pictures and do color detection
	for i in range(5):
		#camera.capture('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/img.jpg')
		img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/piImages/img%s.jpg' % i)

		# hue, saturation, brightness
		hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

		# color: red range
		lowerRange = np.array([0,100,70])
		upperRange = np.array([0,100,100])
		mask = cv2.inRange(hsv, lowerRange, upperRange)
		#lowerMask = cv2.inRange(img, np.array([0,100,20]), np.array([10,255,255]))
		#upperMask = cv2.inRange(img, np.array([160,100,20]), np.array([179,255,255]))
		#fullMask = lowerMask + upperMask

		#result = cv2.bitwise_and(img.copy(), img.copy(), mask = fullMask)

		cv2.imshow("mask", mask)
		#cv2.imshow("result", result)

		#plt.figure(figsize = [13,13])
		#plt.subplot(121);

		cv2.waitKey(0)
	'''

	cv2.destroyAllWindows()

if __name__ == "__main__":
	main()
