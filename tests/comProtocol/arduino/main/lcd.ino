void cldInit(){
  myGLCD.InitLCD();
  myGLCD.clrScr();
}

void lcdPrintHour(String hours) {
  myGLCD.setFont(SevenSegNumFontPlus);
  myGLCD.print(hours, 30, 30);
}

void lcdPrintMin(String minets) {
  myGLCD.setFont(SevenSegNumFontPlus);
  myGLCD.print(":" + minets, 100, 30);
}

void lcdTimeFrame(){
  myGLCD.setFont(BigFont);
  myGLCD.print("current time:", 10, 9);
  myGLCD.drawRect(1, 1, 220, 90);
}
