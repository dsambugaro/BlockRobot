#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import serial
from threading import Thread

import smbus
import CHIP_IO.GPIO as GPIO


class COMController(Thread):
    startflag = "["
    endflag = "]"
    splitflag = ' '
    stopflag = '*'
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

        GPIO.setup("XIO-P0", GPIO.OUT)
        GPIO.output("XIO-P0", GPIO.LOW)


    def run(self):
        while self.teste < 5:
            commands = self.read_commands()

            for command in commands:
                self.bus.write_byte(self.uno_address, command)
            time.sleep(0.5)
            self.teste += 1

    def read_commands(self):
        commandList = []
        while self.running:
            command = self.bluetooth.read()
            if command == self.startflag:
                command = self.bluetooth.read()
                aux = ''
                while command != self.endflag:
                    if command != self.splitflag:
                        aux += command
                    else:
                        commandList.append(int(aux))
                        aux = ''
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
