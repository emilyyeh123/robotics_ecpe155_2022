#!/usr/bin/python3

import picamera
import time
import cv2
import numpy as np
import PIL
from PIL import Image
#import matplotlib.pyplot as plt


def main():
	img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/paperBack/img%s.jpg' % 1)
	grayImg = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	_, thresh = cv2.threshold(grayImg, 120, 255, cv2.THRESH_BINARY)
	contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

	hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	lowerRed = np.array([0,60,60])
	upperRed = np.array([100,180,180])

	skipFirstInstance = 0
	for cnt in contours:
		# ignore first instance since whole image is detected as a shape
		if skipFirstInstance == 0:
			skipFirstInstance = 1
			continue

		# approximate shape and draw contour
		approx = cv2.approxPolyDP(cnt, 0.01*cv2.arcLength(cnt, True), True)
		cv2.drawContours(img, [cnt], 0, (255, 0, 0), 5)

		shapeCenter = cv2.moments(cnt)
		if shapeCenter['m00'] != 0.0:
			x = int(shapeCenter['m10'] / shapeCenter['m00'])
			y = int(shapeCenter['m01'] / shapeCenter['m00'])


		# if contour has between 10-15 edges (is a circle)
		sides = len(approx)
		#print(sides)
		if sides >= 10 and sides <= 15:
			# if color at point is within range of red, label as circle
			hsvColor = hsv[y,x]
			for i in range(3):
				if not(hsvColor[i] >= lowerRed[i] and hsvColor[i] <= upperRed[i]):
					pass
				else:
					if i == 2:
						cv2.putText(img, 'circle', (x,y), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,0,0), 2)
			#cv2.drawContours(img, [cnt], 0, (255, 255, 0), -1)
	
	
	cv2.imshow("binary", thresh)
	cv2.imshow("image", img)

	'''

	# take 5 pictures and do color detection
	for i in range(5):
		#camera.capture('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/img.jpg')
		img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/piCam/moreImages/img%s.jpg' % i)

		# hue, saturation, brightness
		hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

		lowerRed = np.array([0,60,60])
		upperRed = np.array([100,180,180])
		mask = cv2.inRange(hsv, lowerRed, upperRed)
		cv2.imshow("image", hsv)
		cv2.imshow("mask", mask)
		cv2.waitKey(0)

	'''

	cv2.waitKey(0)
	cv2.destroyAllWindows()

if __name__ == "__main__":
	main()
