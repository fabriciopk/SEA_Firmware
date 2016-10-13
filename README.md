# SEA_Firmware [![Build Status](https://travis-ci.org/fabriciopk/SEA_Firmware.svg?branch=master)](https://travis-ci.org/fabriciopk/SEA_Firmware)
Firmware for series elastic actuator, this board contains a stm32f103 microcontroller

Installation
============

UPLOAD USING ARDUINO IDE
=======
```
#install tool for flash the device
> sudo apt-get install openocd

#Install platformio for build the code
> pip install -U platformio

#build the code
> platformio run

#flash the target
> make flash
```
