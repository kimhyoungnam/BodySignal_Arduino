#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
 
int blueTx=2;   //Tx (보내는핀 설정)
int blueRx=3;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString=""; //받는 문자열
 
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mySerial.begin(9600); //블루투스 시리얼 개방
  pinMode(13, OUTPUT);  //Pin 13을 OUTPUT으로 설정 (LED ON/OFF)
}
 
void loop() {
  while(mySerial.available())  //mySerial 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString+=myChar;   //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
 
      if(myString=="on")  //myString 값이 'on' 이라면
      {
        digitalWrite(13, HIGH); //LED ON
      } else {
        digitalWrite(13, LOW);  //LED OFF
      }
      
    myString="";  //myString 변수값 초기화
  }

  
    u8g.firstPage();

    do{

        u8g.setFont(u8g_font_unifont);

        u8g.setPrintPos(0,10);

        u8g.print("Hello, zagidie");

        u8g.drawStr(0,30, "Hello, cheerleader!!fuck");

    }while(u8g.nextPage());
}



