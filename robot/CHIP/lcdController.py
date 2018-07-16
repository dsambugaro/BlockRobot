#!/usr/bin/env python
# -*- coding: utf-8 -*-

import CHIP_IO.GPIO as GPIO
from threading import Thread
from time import *

import I2C_LCD

class LCDController(Thread):
    def __init__(self):
        Thread.__init__(self)
        self.running = True
        self.mylcd = I2C_LCD.lcd()
        self.eye = [
            # char(0) - Upper-left character
            [0x1,0x3,0x7,0xf,0x1f,0x1f,0x1f,0x1f],
            # char(1) - Upper-right character
            [0x10,0x18,0x1c,0x1e,0x1f,0x1f,0x1f,0x1f],
            # char(2) - Lower-left character
            [0x1f,0x1f,0x1f,0x1f,0xf,0x7,0x3,0x1,0x1f],
            # char(3) - Lower-right character
            [0x1f,0x1f,0x1f,0x1e,0x1c,0x18,0x10,0x1f],
            # char(4) - Upper/Lower-middle character
            [0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f],
        ]
        self.mylcd.lcd_load_custom_chars(self.eye)
        self.mylcd.lcd_write(0x80+4)
        self.mylcd.lcd_write_char(0)
        self.mylcd.lcd_write_char(4)
        self.mylcd.lcd_write_char(1)
        self.mylcd.lcd_write(0xC0+4)
        self.mylcd.lcd_write_char(2)
        self.mylcd.lcd_write_char(4)
        self.mylcd.lcd_write_char(3)

        self.mylcd.lcd_write(0x80+10)
        self.mylcd.lcd_write_char(0)
        self.mylcd.lcd_write_char(4)
        self.mylcd.lcd_write_char(1)
        self.mylcd.lcd_write(0xC0+10)
        self.mylcd.lcd_write_char(2)
        self.mylcd.lcd_write_char(4)
        self.mylcd.lcd_write_char(3)
        sleep(2)
        # GPIO.setup("XIO-P0", GPIO.OUT)
        # GPIO.output("XIO-P0", GPIO.LOW)




    def run(self):
        while self.running:
            sleep(1)
