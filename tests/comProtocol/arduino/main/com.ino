/* поддерживаемые команды
 *  th - пакет текущего времени - часы
 *  tm - пакет текущего времени - минуты
 */
String const commandTHStart = "<th>";
String const commandTHEnd = "</th>";

String comDataString;
String comCurStartCommand;
String comCurEndCommand;
boolean comCurStartCommandCompleted;
boolean comCurEndCommandCompleted;
String comCurReceiveEndCommand;

void comInit() {
  Serial.begin(9600);
  comResetAll();
}

void comLoop(){
  while (Serial.available())
    Serial.print(Serial.read());
}

void comReadPack()
{
  while (Serial.available())           // Пока в буфере есть что читать и пакет не является принятым
  {
    int bufferChar = Serial.read();                           // Читаем очередной байт из буфера
    if (comCheckMarkerStart(bufferChar))
      if (comCheckMarkerEnd(bufferChar)){
        comMainProcessor();
        comReset();
      }
  }
}

boolean comCheckMarkerStart(int inChar){
  if (comCurStartCommandCompleted) return true;
  
  comCurStartCommand = comCurStartCommand + (char)inChar;
  // главный блок проверки команд
  // <th>
  if (comCurStartCommand.equals(commandTHStart)){
    comCurStartCommandCompleted = true; 
  }
  Serial.println("start: " + comCurStartCommand);
  
  return false;
}

void comCheckBadCommandStart(){
  if(comCurStartCommand.length()>4)
    comReset();
}

boolean comCheckMarkerEnd(int inChar){
  if (comCurEndCommandCompleted) return true;
  
  comCurEndCommand = comCurEndCommand + (char)inChar;
  
  if (comCurEndCommand.indexOf(commandTHEnd)>=0){
    comCurEndCommandCompleted = true;
    comCurReceiveEndCommand = commandTHEnd;
    comDataString = comExtractData();
    Serial.println("data: " + comDataString);
    return true;  
  }
  Serial.println("end: " + comCurEndCommand);
  
  return false;
}

void comCheckBadCommandEnd(){
  if(comCurEndCommand.length()>5)
    comReset();
}

String comExtractData(){
  if (comCurEndCommand.indexOf(commandTHEnd)>=0)
    return comCurEndCommand.substring(0,comCurEndCommand.length()-commandTHEnd.length());

  return "";
}

void comReset(){
  comCurStartCommandCompleted = false;
  comCurEndCommandCompleted = false;
  comCurStartCommand = "";
  comCurEndCommand = "";
  comCurStartCommandCompleted = false;
  comCurEndCommandCompleted = false;
}

void comResetAll(){
  comDataString = "";           // Обнуляем буфер приема данных
  comCurReceiveEndCommand = ""; // Закрывающий тег текущей принятой команды
  comReset();                   // Частичный сброс протокола
}

// главный обработчик команд
void comMainProcessor(){
  if(comCurReceiveEndCommand.equals(commandTHEnd)){
    exeTH(comDataString);
    comCurReceiveEndCommand = "";
    comDataString = "";
    return;
  }
}
