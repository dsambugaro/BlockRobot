#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import serial
from threading import Thread

class COMController(Thread):
    startflag = "["
    endflag = "]"
    host = "/dev/rfcomm0"
    port = 9600

    def __init__(self):
        Thread.__init__(self)
        self.running = True

    def run(self):
        while self.running:
            commands = self.read_commands()
            for command in range(commands):
                print("teste: ", command)
                time.sleep(5)

    def read_commands(self):
        rfcomm = serial.Serial(port=self.host, baudrate=self.port)
        rfcomm.close()
        commandList = []
        while self.running:
            rfcomm.open()
            command = rfcomm.read()
            if command == self.startflag:
                command = rfcomm.read()
                while command != self.endtag:
                    commandList.append(int(command))
                    command = rfcomm.read()
                print("------------------------------------------")
                print("Commands: ", commandList)
                print("------------------------------------------")
                return commandList
