# SEA_Firmware [![Build Status](https://travis-ci.org/fabriciopk/SEA_Firmware.svg?branch=master)](https://travis-ci.org/fabriciopk/SEA_Firmware)
Firmware for series elastic actuator, this board contains a stm32f103 microcontroller

Installation
============

Upload using arduino IDE:
[Follow the instructions here](https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation)

Setup Arduino IDE
====================
Board:STM32F103C Generic

Variant:STM32F103C8

Upload method: Stlink

You can find the pins for SWD setup in the hardware folder.

Usage
=======
```c++
#define SEA_ID 105 //ID of the board in the dinamyxel 
#define INVERTED
...
#define SEA_RECT //Type of the board, coment if is the rounded board
...
```
Testing(linux)
=======

```bash
cd test_board
make
./dynamixel_test ID_board
```
