/**
Программа проверки протокола Firmata и отображения информации на дисплее
*/

#include <FirmataDefines.h>
#include <FirmataConstants.h>
#include <Boards.h>
#include <Firmata.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

// библиотека для работы с дисплеем
#include <UTFT.h>
// создаём объект класса UTFT
// и передаём идентификатор модели дисплея и номера управляющих пинов
UTFT myGLCD(CTE32HR, 38, 39, 40, 41);
// объявления встроенного шрифта
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

void analogWriteCallback(byte pin, int value)
{
    pinMode(pin,OUTPUT);
    analogWrite(pin,value);
}

void setup()
{

  // инициализируем дисплей
  myGLCD.InitLCD();
  // очищаем экран
  myGLCD.clrScr();
  // выбираем тип шрифта
  myGLCD.setFont(BigFont);
  // печатаем «New e-mails:» в центре верхней строки дисплея
  myGLCD.print("New e-mails:", 10, 9);

  // init firmata
  Firmata.setFirmwareVersion(0, 1);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
//  Firmata.begin(9600);
  // send to masters version of protocol
  Firmata.printVersion();
  // send test string
  Firmata.sendString("gc986!");
}
void loop()
{
  myGLCD.drawRect(1, 1, 210, 90);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.print("00001", 10, 30);

  myGLCD.setFont(BigFont);
  String str = "";

  // send to masters version of protocol
  Firmata.printVersion();
  // send test string
  Firmata.sendString("gc986!");

}

