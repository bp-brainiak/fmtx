#include <U8glib.h>
#include <math.h> 
#include <FMTX.h>

U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
int channel=0;
float fm_freq = 90;  // Here set the default FM frequency
int reading=0;
int last_reading=0;
int Current_reading=0;
int mapping_reading=000;

void setup() {
  pinMode(A0,INPUT);
  fmtx_init(fm_freq, USA);
  // put your setup code here, to run once:
  Serial.begin(9600);
  u8g.setRot180();
  u8g.setColorIndex(1); // pixel on !
  u8g.firstPage(); 
    do{
      set_screen(1);
    }
  while(u8g.nextPage() );
  delay(1000);
//....................
  u8g.firstPage(); 
  do{
    set_screen(0);
  }
  while(u8g.nextPage());
  delay(1000);
  Clear();
   //..........
  u8g.firstPage(); 
  do{
    intro();
  }
  while(u8g.nextPage());
  delay(2500);
  u8g.firstPage(); 
  Serial.println("xx");
  do{
    intro2();
  }
  while(u8g.nextPage());
  delay(2500); 
  Clear();  
  Serial.println("xxx");
}
void loop(){ 
  reading=analogRead(A0);  
  mapping_reading=map(reading,0,1023,87,108);
  mapping_reading=constrain(mapping_reading,87,108);
  if( mapping_reading!= Current_reading)
  {
    Clear();
    Analog_pin_read();  
    u8g.firstPage(); 
    do{
      number(channel);
    }
    while(u8g.nextPage() );
    delay(100);
  }
}


// Reading Any Tunning change here.
void Analog_pin_read(){
   channel=mapping_reading;
   Current_reading=channel;
   fmtx_set_freq(channel);
  
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void set_screen(int i){
  u8g.setColorIndex(i); // pixel on !
  for (int x_axis=0;x_axis<84;x_axis++){
    for (int y_axis=0;y_axis<44;y_axis++){
      u8g.drawPixel(x_axis,y_axis);
    }
  }
}


void Clear(void){
  u8g .setFont(u8g_font_04b_03);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}
void intro(void){
  u8g.setColorIndex(1);
  u8g.drawFrame(0,0,83,47);
  u8g .setFont(u8g_font_osr18);
  u8g.drawStr( 5, 25, "FM Tx ");
  u8g .setFont(u8g_font_tpss);
  u8g.drawStr( 5, 40, " System");
}
void intro2(void){
  u8g.setColorIndex(1);
  u8g.drawFrame(0,0,83,47);
  u8g .setFont(u8g_font_04b_03);
  u8g.drawStr( 2, 7, "Build Your FM station! ");
  u8g.drawStr( 2, 15, "Change the Freq");
  u8g.drawStr( 2, 26, "From Poten");
  u8g.drawStr( 2, 38, "www.genotronex.com");
}
//change frequency value On lcd here
void number(int value){
  u8g.setColorIndex(1);
  u8g.drawFrame(0,0,83,47);
  u8g .setFont(u8g_font_unifont);
  u8g.drawStr( 5, 15, "Frequency ");
  u8g .setFont(u8g_font_osr18);
  u8g.setPrintPos(10,45);
  u8g.println(value,DEC);
  u8g .setFont(u8g_font_unifont);
  u8g.drawStr( 45, 38, "MHz ");
}

