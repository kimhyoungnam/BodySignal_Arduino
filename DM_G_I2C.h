

 #include <Wire.h>
void G_I2C_Scanner();
void initial_serial_print();
void OLED_SETUP();
void OLED_Display(int Fontsize,int oled_x_set,int oled_y_set, String message);
void OLED_Display_add(int Fontsize,int oled_x_set,int oled_y_set, String message);

void OLED_Display_Font2_RIGHT_up(int delaytime, String message);
void OLED_Display_Font2_RIGHT_do(int delaytime, String message);
void OLED_Display_Font2_RIGHT_with(int delaytime, String message1, String message2);


void OLED_Display_clear();
void OLED_Display_clear_display();
void OLED_Display_display();

void OLED_Display_clear_white_h();
void OLED_Display_clear_white_w();
void OLED_Display_Full_Inverse_w();
void OLED_Display_Full_Inverse_h();


void OLED_Display_dot(int x, int y, int State);

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h);

void OLED_Display_Image(int delay_time,unsigned char PROGMEM Data[]);
