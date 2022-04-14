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



def send_request(ser, packet):
    packet.append(struct.pack('B', endCommand))

    # send all requests
    for i in range(len(packet)):
        print("transmit: ", packet[i])
        ser.write(packet[i])
    packet.clear()

    # check for response
    respPacket = []

    while ser.in_waiting <= 0:
        pass

    # in_waiting returns number of bytes
    # if there is data to receive
    while ser.in_waiting < 0:
        # receive first byte of response
        resp = ser.read()
        print("response is: ", resp)
        respPacket.append(list(struct.unpack('c', resp)))

        # if first response is equal to startCommand
        if respPacket[0] == startCommand:
            # receive command
            resp = ser.read(1)
            respPacket.append(struct.unpack('B', resp))
            print("First response: ", respPacket[0])

            #while respPacket




def main():
    ser = serial.Serial("/dev/ttyS0") # initialize serial

    packet = []

    while 1:
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
