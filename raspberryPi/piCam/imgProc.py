#!/usr/bin/python3

import cv2
import numpy as np

def empty(img):
	pass

def main():
	video = cv2.VideoCapture(0)

	cv2.namedWindow("TrackBar")
	cv2.resizeWindow("TrackBar", 600, 300)
	cv2.createTrackbar("hue_min", "TrackBar", 0, 179, empty

	while True:
		ret,img = video.read()

		# hsv = hue, saturation, brightness
		hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
		mask = cv2.inRange(hsv, lower, upper)

		# show frame
		cv2.imshow("Frame", img)
		cv2.imshow("hsv", hsv)

		# wait for pressed key
		check = cv2.waitKey(1)

		if check == ord('q'):
			break

	video.release()
	cv2.destroyAllWindows()

if __name__ == "__main__":
	main()
