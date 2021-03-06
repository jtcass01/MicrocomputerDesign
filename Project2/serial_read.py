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


if __name__ == "__main__":
    serial_port = initialize_serial_port()

    loop_read(serial_port)
