#!/usr/bin/env python

import time
import serial

def initialize_serial_port():
    serial_port = serial.Serial(
        port = '/dev/ttyUSB0',
        baudrate = 115200,
        parity = serial.PARITY_NONE,
        stopbits = serial.STOPBITS_ONE,
        bytesize = serial.EIGHTBITS,
        timeout = 1
    )

    print("serial port successfully initialized %s" % str(serial_port))

    return serial_port


def loop_read(serial_port):
    while True:
        response = serial_port.readline()
        print("Serial Response: ", response)

def loop_write(serial_port):
    letter = None

    while True:
        letter = input("What letter would you like to write to the serial port?")
        write_letter(serial_port, ord(letter[0]))

def write_letter(serial_port, letter):
    print(letter)
    serial_port.write(letter)


if __name__ == "__main__":
    serial_port = initialize_serial_port()

    serial_port.write('A')
#    loop_write(serial_port)
