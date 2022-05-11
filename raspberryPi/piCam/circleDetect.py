#!/usr/bin/python3

import cv2
import numpy as np

def main():
	img = cv2.imread('/home/pi/bishop_ecpe155_2022/raspberryPi/wallEx/img%s.jpg' % 2)
	#img = cv2.imread('/home/pi/Desktop/colorDetection.png')
	output = img.copy()
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

	circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, param1 = 100, param2 = 30, minRadius = 0, maxRadius = 0)
	print(circles)

	cv2.imshow("grayscale", gray)

	# ensure at least some circles were found
	if circles is not None:
		print("Detecting Circles")

		# convert the (x, y) coordinates and radius of the circles to integers
		circles = np.round(circles[0, :]).astype("int")

		# loop over the (x, y) coordinates and radius of the circles
		for (x, y, r) in circles:
			# draw the circle in the output image, then draw a rectangle
			# corresponding to the center of the circle
			cv2.circle(output, (x, y), r, (0, 255, 0), 4)
			cv2.rectangle(output, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)

		# show the output image
		#cv2.imshow("output", np.hstack([img, output]))
		cv2.imshow("output", output)

	cv2.waitKey(0)
	cv2.destroyAllWindows()

if __name__ == "__main__":
	main()
