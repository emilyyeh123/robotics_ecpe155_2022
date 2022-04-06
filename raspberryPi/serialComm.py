#!/usr/bin/python3

import serial
import time
import struct

def main():
    startCommand = b'\xaa'
    endCommand = b'\x55'
    motorForward = b'\x81' 

    ser = serial.Serial("/dev/ttyS0") # open named port

    # when sending data, need to pack to convert to C struct
    packData = struct.pack('3c', startCommand, motorForward, endCommand)
    ser.write(packData)

    '''
    # when recieving data, need to unpack to convert to python struct
    data = ser.read(10) #read 10 characters from serial port
    unpackData = struct.unpack, ('c', data)
    ser.write(data)
    ser.close()
    '''

    #packData = struct.pack('c', b'o')
    #print("Packed Data: ", packData, "\n")
    #print("Unpacked Data: ", unpackData, "\n")

    #binToHex = hex(int('10000001', 2))
    #print(binToHex)

if __name__ == "__main__":
    main()
