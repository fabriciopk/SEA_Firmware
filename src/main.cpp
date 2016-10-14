#include <DynamixelProtocol.h>
#include <AS5048A.h>
#include <SPI.h>

#define SEA_ID 108
#define INVERTED
#define SEA_INSTRUCTION 0x24

//Leds PB0, PB1, PB2, PB10
#define LED_ORANGE PB0
#define LED_RED PB2
//Leds placa cantos vivos, PA12, PA13, PA14 ,PA15

#define SPI_NSS PA4
#define BAUDRATE_DX 1000000

//Para a placa com canto arredondado
#define SERIAL Serial2 //Tem que mudar dentro da biblioteca do dynamixel tambem (Serial)
#define EN PA1 //PA11 para que tem canto vivo.

AS5048A mag(SPI_NSS);
DynamixelProtocol dxl(BAUDRATE_DX,SEA_ID);

void blink(int times)
{
  for (int i = 0 ; i < times ; i++)
  {
    digitalWrite(LED_ORANGE,LOW);
    delay(125);
    digitalWrite(LED_ORANGE,HIGH);
    delay(125);
  }
  delay(500);
}

void setup()
{
  pinMode(LED_ORANGE, OUTPUT);
  //Enable rs485
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  mag.init();
  dxl.init();
  blink(SEA_ID - 100);
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
        //SERIAL.waitDataToBeSent();
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
              digitalWrite(LED_RED, HIGH);
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
          //SERIAL.waitDataToBeSent();
          digitalWrite(EN, LOW);
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
    digitalWrite(LED_ORANGE,HIGH);
  }
  digitalWrite(LED_RED, LOW);
}
