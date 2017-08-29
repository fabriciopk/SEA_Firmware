# SEA_Firmware
Firmware for series elastic actuator, this board contains a stm32f103 microcontroller

#Installation(Upload using arduino IDE)

- Download arduino [IDE](https://www.arduino.cc/en/Main/Software)
- Download zip file containing the STM32 files from [here](https://github.com/fabriciopk/Arduino_STM32/archive/master.zip)
- Unzip in arduino hardware folder (arduino-1.6.xx/hardware/) and rename to Arduino_STM32
- Run the arduino IDE, and on the Tools menu, select the Boards manager (Tools > Boards > Boards Manager), and install the Arduino Zero(Arduino SAMD boards 32 bits cortex M3) from the list of available boards. You must do this step, it installs the arm-none-eabi-g++ toolchain!
- Copy AS5048A and DynamixelProtocol from [lib](https://github.com/fabriciopk/SEA_Firmware/tree/master/lib) folder to (arduino-1.6.xx/libraries/)
- Change the line #define BOARD_HAVE_SERIALUSB 0 in the file arduino-1.6.xx/hardware/STM32F1/cores/maple/boards.h 

#Setup Arduino IDE and board upload pins
- Board:STM32F103C Generic
- Variant:STM32F103C8
- Upload method: Stlink
- Open [src/src.ino](https://github.com/fabriciopk/SEA_Firmware/blob/master/src/src.ino)
- Pins for SWD(stlink v.2) setup:

![alt tag](https://github.com/fabriciopk/SEA_Firmware/blob/master/hardware/retangular.png)

![alt tag](https://github.com/fabriciopk/SEA_Firmware/blob/master/hardware/round.png)

NOTE: top-side of board.
#Board settings
```c++
#define SEA_ID 105 //define the board id in rs485 network
#define INVERTED
...
#define SEA_RECT //Type of the board, coment if is the rounded board
...
```
#Testing(linux)

Plug usb2Dinamyxel, power on the board.
```bash
cd test_board
make
./dynamixel_test ID_board
```
