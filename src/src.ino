#include <SPI.h>

#include <DynamixelProtocol.h>
#include <AS5048A.h>

//TODO check if serial of maple core is in the correct pins
//HardwareSerial Serial1(&rx_buffer1, &UBRR1H, &UBRR1L, &UCSR1A, &UCSR1B, &UDR1, RXEN1, TXEN1, RXCIE1, UDRE1, U2X1);

#define SEA_ID 105
#define INVERTED
#define SEA_INSTRUCTION 0x24

//#define SEA_RECT

#ifdef SEA_RECT

#define LED PB12
#define LED_RED PB14
#define LED_BLUE PB15
#define LED_GREEN PB13
#define SERIAL Serial1
#define EN PA11

#else

#define LED PB0
#define LED_RED PB2
#define LED_BLUE PB1
#define LED_GREEN PB10
#define SERIAL Serial2
#define EN PA1

#endif

#define SPI_NSS PA4
#define BAUDRATE_DX 1000000

int RGB[3] = {LED_RED, LED_GREEN, LED_BLUE};
int color = 0;

AS5048A mag(SPI_NSS);
DynamixelProtocol dxl(BAUDRATE_DX, SEA_ID, SERIAL);

void blink(int times)
{
  for (int i = 0 ; i < times ; i++)
  {
    digitalWrite(LED, LOW);
    delay(125);
    digitalWrite(LED, HIGH);
    delay(125);
  }
  delay(500);
}

void setup()
{
  delay(1000);
  pinMode(LED, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  //Enable rs485
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  mag.init();
  dxl.init();
  blink(SEA_ID - 100);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
}

void loop() {
#ifndef INVERTED
  word val = mag.getRawRotation();
#else
  word val = 8192 - mag.getRawRotation();
#endif
  dxl.checkMessages();
  if (dxl.instruction != DXL_NO_DATA)
  {

    switch (dxl.instruction)
    {
      case DXL_PING:
        digitalWrite(EN, HIGH);
        dxl.sendStatusPacket(0x00, NULL, 0);
        SERIAL.waitDataToBeSent();
        digitalWrite(EN, LOW);
        break;
      case DXL_READ_DATA:
        if (dxl.total_parameters == 2 && dxl.parameters[1] == 2)
        {
          unsigned char values[2];
          switch (dxl.parameters[0])
          {
            case SEA_INSTRUCTION:
              values[0] = (unsigned char)val;
              values[1] = (unsigned char)(val >> 8);
              digitalWrite(LED, HIGH);
              break;
            case 0x00:
              values[0] = 54;
              values[1] = 1;
              break;
            case 0x01:
              values[0] = 0;
              values[1] = 1;
              break;
            default:
              values[0] = 0;
              values[1] = 0;
              break;
          }
          digitalWrite(EN, HIGH);
          dxl.sendStatusPacket(0x00, values, 2);
          SERIAL.waitDataToBeSent();
          digitalWrite(EN, LOW);
          digitalWrite(RGB[color], LOW);
          color = (color + 1) % 3;
          digitalWrite(RGB[color], HIGH);
        }
        break;
      case DXL_WRITE_DATA:
        break;
      case DXL_REG_WRITE:
        break;
      case DXL_ACTION:
        break;
      case DXL_RESET:
        break;
      case DXL_SYNC_WRITE:
        break;
      default:
        break;
    }
  } else {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED, HIGH);
  }
  digitalWrite(LED, HIGH);
}
