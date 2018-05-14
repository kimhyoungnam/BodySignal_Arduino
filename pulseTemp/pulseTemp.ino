
#include "U8glib.h"
#include <Wire.h>
#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

int blueTx=2;   //Tx (보내는핀 설정)
int blueRx=3;   //Rx (받는핀 설정)

int x=0;
int lastx=0;
int lasty=0;
int LastTime=0;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;
 
#define UpperThreshold 550
#define LowerThreshold 500

SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언

void firstStart(void){
     u8g.setFont(u8g_font_unifont);
     u8g.drawStr(0,30, "Body-Signal");
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin(); 
  u8g.firstPage();   
  do {
   firstStart();
  } while( u8g.nextPage() );
  
}
 
void loop() {
  
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
  
  String strTemp = String("");
  strTemp += (int)(mlx.readObjectTempC());
  char temp[10];
  strTemp.toCharArray(temp, 5);
  temp[2] = 0x27;
  temp[3] = 'C';
  temp[4] = 0x00;
  
  // pulse 
   int value=analogRead(0);
   
  if(value>UpperThreshold)
  {
    if(BeatComplete)
    {
      BPM=millis()-LastTime;
      BPM=int(60/(float(BPM)/1000));
      BPMTiming=false;
      BeatComplete=false;
    }
    if(BPMTiming==false)
    {
      LastTime=millis();
      BPMTiming=true;
    }
  }
  strTemp += BPM;
  char pulse[13];
  strTemp.toCharArray(pulse, 7);
   pulse[2] = 0x27;
   pulse[3] = 'B';
   pulse[4] = 'P';
   pulse[5] = 'M';
   pulse[6] = 0x00;
    
  draw(temp,pulse); //oled 에 온도 출력 함수 호출
  sendTemp(mlx.readObjectTempC());
  delay(1000);
}
 
void draw(char* strTemp,char* strPulse) {  //체온 oled에 표기 
  // picture loop  
  u8g.firstPage();  
  
  do {
    // show text
    u8g.setFont(u8g_font_courB14);
    u8g.setFontRefHeightExtendedText();
    u8g.setDefaultForegroundColor();
    u8g.setFontPosTop();
   // u8g.drawStr(5, 12, "Temperature");
    u8g.drawStr(40, 40, strTemp);
    u8g.drawStr(50, 40,strPulse);
  } while( u8g.nextPage() );

}
void sendTemp(int temp){
  mySerial.print("Temparature:");
  mySerial.print(temp);
}




