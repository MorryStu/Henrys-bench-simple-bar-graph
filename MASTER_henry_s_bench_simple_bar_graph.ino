// Henry's Bench
//  Basic Bargraph Tutorial

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9
Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;




// Color Pallette

#define BACKCOLOR 0x18E3
#define BARCOLOR 0x0620
#define SCALECOLOR 0xFFFF

//Analog Measurement Declarations
const int analogIn = A0;
int RawValue = 0;
int LastPercent = 0;
 

void setup() {
  
  Serial.begin(9600);
  Serial.println("RA8875 start");

  //Initialize the display using 'RA8875_480x80', 'RA8875_480x128', 'RA8875_480x272' or 'RA8875_800x480'
  if (!tft.begin(RA8875_800x480))
  {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

  Serial.println("Found RA8875");

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.textMode();

  tft.fillScreen(RA8875_BLACK);
    drawScale(); 
}

void loop(){  
    int newPercent;
    RawValue = analogRead(analogIn);
    newPercent = int((RawValue/1024.0)* 400.0);
    
    if (newPercent != LastPercent){
      drawBar(newPercent);     
    }
     
}

void drawScale(){  
  tft.drawFastVLine(55, 50,400, SCALECOLOR ); // Vertical Scale Line 
  tft.drawFastHLine(20, 50, 35, SCALECOLOR); // Minor Division
  tft.drawFastHLine(40, 100, 15, SCALECOLOR); // Minor Division 
  tft.drawFastHLine(20, 150, 35, SCALECOLOR); // Major Division
  tft.drawFastHLine(40, 200, 15, SCALECOLOR); // Minor Division
  tft.drawFastHLine(20, 250, 35, SCALECOLOR); // Major Division
  tft.drawFastHLine(40, 300, 15, SCALECOLOR); // Minor Division
  tft.drawFastHLine(20, 350, 35, SCALECOLOR);  // Major Division
  tft.drawFastHLine(40, 400, 15, SCALECOLOR); // Minor Division
  tft.drawFastHLine(20, 450, 35, SCALECOLOR); // Minor Division
}


void drawBar (int nPer){

  if(nPer < LastPercent){
    tft.fillRect(61, 50 + (400-LastPercent), 30, LastPercent - nPer,  BACKCOLOR);     
  }
  else{
    tft.fillRect(61, 50 + (400-nPer), 30, nPer - LastPercent,  BARCOLOR);
  }    
  LastPercent = nPer;  
  delay (500);
}
