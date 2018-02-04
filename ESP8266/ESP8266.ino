#include <SoftwareSerial.h>
#define DEBUG true
#define MAX_BUFFER 1024
#define NOT_FOUND "Not found"
SoftwareSerial esp8266(10, 11); //  10-RX, 11-TX
int baudrate=9600; 
bool x;
String html = "";
unsigned long timerResquest=0;
int minTimerResquest=3000;
char InLine[MAX_BUFFER]; //Hạn chế ký tự
unsigned int Position = 0;

void setup() {
  Serial.begin(baudrate);
  esp8266.begin(baudrate); // chu y phai cung toc do voi ESP 8266
  
  //========================gui tap lenh AT cho ESP 8266 de cai dat cac tham so cho WiFi================================
  SendCommand("AT\r\n", 100, DEBUG); // gui lenh AT
  SendCommand("AT+CWMODE=1\r\n", 1000, DEBUG); // Chọn chức năng client cho esp
  SendCommand("AT+RST\r\n", 5000, DEBUG); // reset module

  SendCommand("AT+CWJAP=\"Hello World\",\"hieudesu\"\r\n", 10000, DEBUG); // Kết nối với wifi
  SendCommand("AT+CIFSR\r\n", 1000, DEBUG); // xem ip là bn
  SendCommand("AT+CIPMUX=1\r\n", 1000, DEBUG); // configure for multiple connections
  //SendCommand("AT+CIPSTART=0,\"TCP\",\"192.168.1.10\",4000\r\n",1000,DEBUG);
  SendCommand("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // Mở cổng 80
}
 
void loop() {
  while (esp8266.available()) {
    IncomingChar(esp8266.read());
  }

  if (x){
    sendData();
  }

//  timerResquest=millis();
//  if (x) {
//    if ((unsigned long)(millis()-timerResquest)>minTimerResquest){
//      timerResquest=millis();
//    }
//    String cipsend = "AT+CIPSEND=0,"; //gui chuoi data qua Wifi
//    if (html.length()==0){
//       html="Not found";
//    }
//    cipsend += html.length();
//    cipsend += "\r\n";
//    SendCommand(cipsend, 1000, DEBUG);
//    SendCommand(html, 1000, DEBUG);
//    SendCommand("AT+CIPCLOSE=0\r\n", 1000, false);
//    x = !x;
//    html="";
//  }
}

void sendData()//send data to module
{
    timerResquest=millis();
    if ((unsigned long)(millis()-timerResquest)>minTimerResquest){
      timerResquest=millis();
    }
    String cipsend = "AT+CIPSEND=0,"; //gui chuoi data qua Wifi
    unsigned int len=html.length();
    if (len==0){
      html=String(NOT_FOUND);
    }
    len=html.length();
    cipsend += len;
    cipsend += "\r\n";
    SendCommand(cipsend,1000,DEBUG);
    SendCommand(html, 1000, DEBUG);
    SendCommand("AT+CIPCLOSE=0\r\n", 1000, DEBUG);
    x = !x;
    html="";
}
 
void IncomingChar(const byte InChar) {
  switch (InChar) {
    case '\r': //Cái này là xuống dòng...cho linux
      break;
    case '\n': // xuống dòng cho window...( kết thúc bảng tin )
      InLine[Position] = 0;
      ProcessCommand(String(InLine));
      ResetValue();
      break;
    default:
      InLine[Position++] = InChar;
  }
}
 
void ProcessCommand(String InLine) {
  //Serial.println("InLine: " + InLine);
  if (InLine.startsWith("+IPD,")) {
    x = !x;
  }

  int sIndex=InLine.indexOf("?ledID=");
  if (sIndex != -1) {
    sIndex+=7;
    int eIndex=sIndex;
    while(InLine[eIndex]!=' '){eIndex++;}
    html="Led ID: "+InLine.substring(sIndex,eIndex);
    ResetValue();
  }
}

void ResetValue(){
  Position=0;
  while(Position<MAX_BUFFER){
    InLine[Position++]=' ';
  }
  Position=0;
}
 
String SendCommand(String lenh, const int thoigian, boolean debug) {
  String chuoigiatri = "";
  esp8266.print(lenh); // send the read character to the esp8266
  long int time = millis();
  while ((time + thoigian) > millis()) {
    while (esp8266.available()) {
      // The esp has data so display its output to the serial window 
      char c = (char)esp8266.read(); // read the next character.
      chuoigiatri += c;
    }
  }
  if (debug) {
    Serial.print(chuoigiatri);
  }
  return chuoigiatri;
}
