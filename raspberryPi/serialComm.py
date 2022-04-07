#!/usr/bin/python3

import serial
import time
import struct

def main():
    ser = serial.Serial("/dev/ttyS0") # open named port

    startCommand = b'\xaa'
    endCommand = b'\x55'
    motorForward = b'\x81' 

    # send start command
    packData = struct.pack('2c', startCommand, motorForward)
    print("transmit ", packData)
    trans = ser.write(packData)
    rec = ser.read(1)
    print("recieve ", rec)
    unpackData = struct.unpack('c', rec)
    print("unpack ", unpackData)
    
    if(unpackData == b'\x55'):
        print("Data unpacked properly!")

        #for i in range(2):
            #packData = b'' 
            #print("recieving index:", i)
            #recieve = ser.read(1)
            #packData += struct.pack('c', recieve)
        #print("transmitting", packData)

    ser.close()

if __name__ == "__main__":
    main()
