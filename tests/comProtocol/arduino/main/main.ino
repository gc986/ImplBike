//Цветной графический дисплей 3.2 TFT 480x320 MEGA http://iarduino.ru/shop/Displei/cvetnoy-graficheskiy-displey-3-2-tft-480x320.html

#include <UTFT.h>                              // подключаем библиотеку UTFT
UTFT myGLCD(TFT32MEGA, 38, 39, 40, 41);        // объявляем объект myGLCD класса библиотеки UTFT указывая тип дисплея TFT32MEGA и номера выводов Arduino к которым подключён дисплей: RS, WR, CS, RST. Выводы параллельной шины данных не указываются
//          TFT32MEGA_2                        // если изображение на дисплее отображается зеркально, значит для инициализации Вашего дисплея, нужно указать не TFT32MEGA, а TFT32MEGA_2.
// (тип TFT32MEGA - для дисплеев на базе чипа ILI9481, а тип TFT32MEGA_2 - для дисплеев на базе чипа HX8357С).
//
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t SevenSegNumFontPlus[];
String buffer;

void setup() {
  comInit();
  cldInit();
  
  lcdTimeFrame();
  lcdPrintHour("00");
  lcdPrintMin("01");
}

void loop() {
  comReadPack();
}

void exeTH(String hour){
  lcdPrintHour(hour);
}
