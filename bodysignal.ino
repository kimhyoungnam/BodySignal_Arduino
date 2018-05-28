#include "DM_G_I2C.h" 
#include <SPI.h> 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <IR_Thermometer_Sensor_MLX90614.h>

#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
 
#define BT_RXD 2
#define BT_TXD 3

SoftwareSerial bluetooth(BT_RXD, BT_TXD);
PulseSensorPlayground pulseSensor;
IR_Thermometer_Sensor_MLX90614 MLX90614 = IR_Thermometer_Sensor_MLX90614();

const int PIN_INPUT = A3;
const int RED_PIN = 11;
const int BLUE_PIN = 9;
String myString=""; //받는 문자열

void setup() {
 // 1) 시리얼 통신 설정 - 컴퓨터를 통해 진행 상태 확이 할 수 있음 : 시리얼 모니터 하기 위한 설정
  Serial.begin(9600);
  bluetooth.begin(9600);         
 // 2) OLED 초기설정 하기  
  OLED_SETUP();
  //sensor
  pulseSensor.analogInput(PIN_INPUT);
  pulseSensor.begin();
  MLX90614.begin();
  
  //led
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

int is_first = 1;
char buf[256] ;

void loop() {
// Pixel Size : 128_32 Display Size - Pixel
// Color : BLACK 0, WHITE 1, INVERSE 2
  delay(20);
// 주변온도,물체의온도,BPM
  bluetooth.print(MLX90614.GetAmbientTemp_Celsius());    bluetooth.print(',');
  bluetooth.print(MLX90614.GetObjectTemp_Celsius());     bluetooth.print(',');
  bluetooth.print(pulseSensor.getBeatsPerMinute());       bluetooth.println();
   
  is_first++;
  
  if (bluetooth.available()) {
    Serial.write(bluetooth.read());
    while (bluetooth.available()){
    char myChar = (char)bluetooth.read();
    myString+=myChar;   //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);         }   //수신 문자열 끊김 방지
     if(!myString.equals("")){  //myString 값이 있다면
          if(myString=="break")   {//myString 값이 'on' 이라면
        digitalWrite(10, HIGH); //LED ON
      }  else{
        digitalWrite(10, LOW);  //LED OFF
      }
    myString="";  //myString 변수값 초기화
   }
  }
  
 

  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
  
 if(is_first == 50){
       digitalWrite(RED_PIN,LOW);
       digitalWrite(BLUE_PIN,LOW); 
  double temp = MLX90614.GetObjectTemp_Celsius()+1;
  if(temp < 37){
    sprintf(buf, "Cel.  %d.%d",(int) temp, ((int)(temp*10))%10);
  }else{
    sprintf(buf, "Cel.!!%d.%d",(int) temp, ((int)(temp*10))%10);
  //led수정
    digitalWrite(RED_PIN,HIGH);
    digitalWrite(BLUE_PIN,LOW);  
    delay(500);
    digitalWrite(RED_PIN,LOW);
    digitalWrite(BLUE_PIN,HIGH);  
    delay(500);
    }
    OLED_Display(2,0,0,buf);
    
    //맥박
    int pulse = pulseSensor.getBeatsPerMinute()-40;
    if(pulse >= 60 && pulse <= 150){
    sprintf(buf, "BPM.  %d", (pulseSensor.getBeatsPerMinute()-40));
    }else{
       sprintf(buf, "BPM.!!%d",(pulseSensor.getBeatsPerMinute()-40)); 
        //led수정
       digitalWrite(RED_PIN,HIGH);
       digitalWrite(BLUE_PIN,LOW);  
       delay(500);
       digitalWrite(RED_PIN,LOW);
       digitalWrite(BLUE_PIN,HIGH);  
       delay(500);
    }
    OLED_Display_add(2,0,15,buf);
    is_first = 0;
 
 }
}


