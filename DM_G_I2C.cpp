
// ##1. 라이브러리 추가
#include "Arduino.h"
#include "DM_G_I2C.h"
#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>

// ##2. 초기 설정
#define OLED_RESET 4 
#define NUMFLAKES 10 
#define XPOS 0 
#define YPOS 1 
#define DELTAY 2
Adafruit_SSD1306 display(OLED_RESET); 





String ver = "1.1";

void initial_serial_print(){
  Serial.println("---------------------------------------");
  Serial.println("DeviceMart : http://www.devicemart.co.kr/");
  Serial.println("Maker. David Gwak : myksj1105@hanmail.net");
  Serial.print("DM_G_I2C.h - DeviceMart & David Gwak Copyright - library ver");
  Serial.println(ver);
  Serial.println("---------------------------------------");
  
}


 void G_I2C_Scanner() {

  byte error, address;
  int nDevices;  
  initial_serial_print();

  Serial.println("I2C Scanning - Waiting.");
  
  Serial.println("---------------------------------------");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
      Serial.print("0");
      Serial.print(address,HEX);
      
      nDevices++;
            
      Serial.print(" : ");      
      Serial.print(nDevices);
      Serial.println(" Device");



    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
      Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done");


  Serial.println("---------------------------------------");
  Serial.print("In conclusion : ");
  Serial.print(nDevices);
  Serial.println("EA device find");  
  Serial.println("Thanks.");
  Serial.println("---------------------------------------");
     
  delay(5000);           
  
 }

//*************************************************************************************//
// OLED - I2C
//*************************************************************************************//

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void OLED_Display_Image(int delay_time, unsigned char PROGMEM Data[]){
   testdrawbitmap(Data, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
 delay(delay_time);
 
}


void OLED_SETUP(){

  //OLED 초기 설정
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); display.clearDisplay();
  OLED_Display(2,0,0,"BodySignal"); OLED_Display_add(2,0,15,"WAITING...");
  delay(1500);

}

void OLED_Display(int Fontsize,int oled_x_set,int oled_y_set, String message){
display.clearDisplay();  display.setTextColor(WHITE); 
display.setTextSize(Fontsize);  display.setCursor(oled_x_set,oled_y_set);     display.println(message);
display.display();  


}

void OLED_Display_add(int Fontsize,int oled_x_set,int oled_y_set, String message){
 display.setTextColor(WHITE); 
display.setTextSize(Fontsize);  display.setCursor(oled_x_set,oled_y_set);     display.println(message);
display.display();  
}

void OLED_Display_Font2_RIGHT_up(int delaytime, String message){
display.setTextColor(WHITE); display.setTextSize(2);  
for (int i=0; i < message.length(); i++){display.setCursor(12*i,0); display.println(String(message.charAt(i)));display.display(); delay(delaytime);
}}

void OLED_Display_Font2_RIGHT_do(int delaytime, String message){
display.setTextColor(WHITE); display.setTextSize(2);  
for (int i=0; i < message.length(); i++){display.setCursor(12*i,15); display.println(String(message.charAt(i)));display.display(); delay(delaytime);
}}

void OLED_Display_Font2_RIGHT_with(int delaytime, String message1, String message2){
display.setTextColor(WHITE); display.setTextSize(2);  
int length_size = 0;
if( message1.length() > message2.length() ){ length_size = message1.length(); }else{length_size = message2.length();}

for (int i=0; i < length_size; i++){display.setCursor(12*i,0); display.println(String(message1.charAt(i)));display.setCursor(12*i,15); display.println(String(message2.charAt(i)));display.display(); delay(delaytime);
}}


void OLED_Display_clear_white_h(){
 display.clearDisplay();
 for(int k=0; k < 32; k++){  for(int i=0; i < 128; i++){
 display.drawPixel(i, k, 1); } display.display();  } delay(100);
}

void OLED_Display_clear_white_w(){
 display.clearDisplay();
 for(int i=0; i < 128; i++){ for(int k=0; k < 32; k++) {
 display.drawPixel(i, k, 1); } display.display();  } delay(100);
}


void OLED_Display_clear(){
display.clearDisplay();   
}

void OLED_Display_display(){
display.display();    
}

void OLED_Display_clear_display(){
display.clearDisplay();  display.display();    
}



void OLED_Display_dot(int x, int y, int State){
   display.drawPixel(x, y, State); 
}


void OLED_Display_Full_Inverse_w(){
 for(int i=0; i < 128; i++){ for(int k=0; k < 32; k++) {
 display.drawPixel(i, k, 2); } display.display();  } delay(100);
}

void OLED_Display_Full_Inverse_h(){
 display.clearDisplay();
 for(int k=0; k < 32; k++){  for(int i=0; i < 128; i++){
 display.drawPixel(i, k, 2); } display.display();  } delay(100);
}



void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }



 for(int i=0; i <10; i++){
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }

 }

}
