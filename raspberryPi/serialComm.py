#!/usr/bin/python3

import serial
import time
import struct

# packet structure
startCommand = 0xAA
endCommand = 0x55

# motor commands
motorForward = 0x81
motorBackward = 0x82
right45 = 0x83
left45 = 0x84
right90 = 0x85
left90 = 0x86



def mainMenu():
    # display UI
    print("\nROBOT ACTIONS MENU")
    print("0) move forwards\n"\
          "1) move backwards\n"\
          "2) turn right 45 degrees\n"\
          "3) turn left 45 degrees\n"\
          "4) turn right 90 degrees\n"\
          "5) turn left 90 degrees\n"\
          "6) exit")

    # receive user input
    menuInp = int(input("> "))
    return menuInp



def send_request(ser, packet):
    packet.append(struct.pack('B', endCommand))

    # send all requests
    for i in range(len(packet)):
        ser.write(packet[i])
        print("transmit: ", packet[i])
    packet.clear()

    # store responses
    respPacket = []
    #print("endCommand to hex ", bytes.fromhex(str(endCommand)))

    while 1:
        # receive first response
        resp = ser.read()
        print("response: ", resp)
        #resp = list(struct.unpack('c', resp))

        #if resp == b'\xaa'
            #print("Action has begun")

        if resp == b'U':
            print("Action Completed")
            break



def main():
    ser = serial.Serial("/dev/ttyS0") # initialize serial

    packet = []

    while 1:
        menuInp = mainMenu()

        # send packet according to user input
        if menuInp == 0:
            # move forward
            packet.append(struct.pack('B', startCommand))
            packet.append(struct.pack('B', motorForward))
            send_request(ser, packet)
        elif menuInp == 1:
            # move backward
            packet.append(struct.pack('B', startCommand))
            packet.append(struct.pack('B', motorBackward))
        elif menuInp == 6:
            return
        else:
            # default
            print("not a valid option")

if __name__ == "__main__":
    main()
