#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import serial
import smbus2 as smbus
import CHIP_IO.GPIO as GPIO
from threading import Thread

class COMController(Thread):
    startflag = b'['
    endflag = b']'
    splitflag = b','
    stopflag = b'*'
    rfcomm = "/dev/rfcomm0"
    baudrate = 9600
    uno_address = 0x04

    def __init__(self):
        Thread.__init__(self)
        self.running = True
        self.teste = 0

        self.bluetooth = serial.Serial(port=self.rfcomm, baudrate=self.baudrate)
        self.bluetooth.close()
        self.bluetooth.open()
        self.bus = smbus.SMBus(2)

        GPIO.setup('XIO-P0', GPIO.OUT)
        GPIO.output('XIO-P0', GPIO.LOW)


    def run(self):
        while self.running:
            commands = self.read_commands()
            for command in commands:
                self.bus.write_byte(self.uno_address, command)
            time.sleep(0.5)

    def read_commands(self):
        commandList = []
        while self.running:
            command = self.bluetooth.read()
            if command == self.startflag:
                command = self.bluetooth.read()
                aux = b''
                while command != self.endflag:
                    if command != self.splitflag:
                        aux += command
                    else:
                        commandList.append(int(aux.decode('utf-8')))
                        aux = b''
                    command = self.bluetooth.read()
                    time.sleep(0.5)
                print("------------------------------------------")
                print("Commands: ", commandList)
                print("------------------------------------------")
                return commandList
            elif command == self.stopflag:
                GPIO.output("XIO-P0", GPIO.HIGH)
                time.sleep(0.1)
                GPIO.output("XIO-P0", GPIO.LOW)
            time.sleep(0.5)
