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



def send_request(packetArr):
    packet.append(struct.pack('B', endCommand))

    # send all requests
    for i in range(len(packet)):
        print("transmit: " packet[i])
        ser.write(packet[i])

    respPacket = []
    while 1:
        # if there is data to recieve
        try:
            # recieve first byte of response
            resp = ser.read(1)
            respPacket.append(struct.unpack('B', resp))
            print("First response: ", respPacket[0])

            # if first response is equal to startCommand
            if respPacket[0] = startCommand:
                # recieve next response
                resp = ser.read(1)
                respPacket.append(struct.unpack('B', resp))
                print("First response: ", respPacket[0])

                while respPacket

        # if no data to recieve, handle exception
        except:
            print("no response recieved")



def main():
    #ser = serial.Serial("/dev/ttyS0") # initialize serial

    '''
    for i in range(len(packet)):
        print("transmit ", packet[i])
        ser.write(packet[i])

    # send start command and action
    #packData = struct.pack('2c', startCommand, motorForward)
    #print("transmit ", packet)
    #trans = ser.write(packData)

    # recieve 3 bytes of data
    rec = ser.read(3)
    print("recieve ", rec)
    #unpackData = struct.unpack('c', rec)
    #print("unpack ", unpackData)
    
    #if(unpackData == b'\x55'):
        #print("Data unpacked properly!")

    ser.close()
    '''


    packet = []
    packet.append(struct.pack('B', startCommand))

    while 1:
        # display UI
        print("Robot Actions Menu")
        print("0) move forwards\n"\
              "1) move backwards\n"\
              "2) turn right 45 degrees\n"\
              "3) turn left 45 degrees\n"\
              "4) turn right 90 degrees\n"\
              "5) turn left 90 degrees\n"\
              "6) exit")

        # recieve user input
        menuInp = int(input("   > "))

        # send packet according to user input
        match menuInp:
            case 0:
                # move forward
                packet.append(struct.pack('B', motorForward))
            case 1:
                # move backward
                packet.append(struct.pack('B', motorBackward))
            case _:
                # default
                print("not a valid option")

if __name__ == "__main__":
    main()
