#!/usr/bin/env python
# -*- coding: utf-8 -*-

from threading import Thread

import communicationController
import lcdController

class MainController(Thread):
    def __init__(self):
        Thread.__init__(self)
        self.communicationController = communicationController.COMController()
        self.lcdController = lcdController.LCDController()
        self.running = True

    def run(self):
        self.communicationController.start()
        self.lcdController.start()
        #while self.running:

def main():
    mc = MainController()
    mc.start()


if __name__ == "__main__":
    main()
