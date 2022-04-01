#!/usr/bin/python3

import serial
import time

def main():
    ser = serial.Serial("/dev/ttyS0") # open named port
    for i in range(5):
        ser.write(bytes(b'Hello'))
        time.ctime(30)
    #ser.baudrate = 9600
    data = ser.read(10) #read 10 characters from serial port
    ser.write(data)
    ser.close()

if __name__ == "__main__":
    main()
