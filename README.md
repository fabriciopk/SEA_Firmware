# SEA_Firmware
Firmware for series elastic actuator, this board contains a stm32f103 microcontroller

Installation
============

Upload using arduino IDE:
Download zip file containing the STM32 files from [here](https://github.com/fabriciopk/Arduino_STM32/archive/master.zip)

Follow the instructions [here](https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation)

Setup Arduino IDE
====================
Board:STM32F103C Generic

Variant:STM32F103C8

Upload method: Stlink

Copy the content of the folder lib to arduino libraries folder

You can find the pins for SWD setup in the hardware folder.

Usage
=======
```c++
#define SEA_ID 105
#define INVERTED
...
#define SEA_RECT //Type of the board, coment if is the rounded board
...
```
Testing(linux)
=======
Plug usb2Dinamyxel, power on the board.
```bash
cd test_board
make
./dynamixel_test ID_board
```
