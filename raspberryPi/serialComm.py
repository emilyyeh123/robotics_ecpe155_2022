#!/usr/bin/python3

import serial
import time
import struct

def main():
    ser = serial.Serial("/dev/ttyS0") # open named port

    startCommand = b'\xaa'
    endCommand = b'\x55'
    motorForward = b'\x81' 

    # send start command and action
    packData = struct.pack('2c', startCommand, motorForward)
    print("transmit ", packData)
    trans = ser.write(packData)

    # recieve 3 bytes of data
    rec = ser.read(3)
    print("recieve ", rec)
    #unpackData = struct.unpack('c', rec)
    #print("unpack ", unpackData)
    
    #if(unpackData == b'\x55'):
        #print("Data unpacked properly!")

    ser.close()

if __name__ == "__main__":
    main()
