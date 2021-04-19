/*-----------------------------------------------------------------------------------------
 * 
 * 
 * 
 * 
 ------------------------------------------------------------------------------------------*/

#include <TFT_ILI9341.h> //TFT Display Library
#include <TFT_Touch.h> //Touch Functionality Library
#include <SPI.h> //SPI Protocol Library

#define DOUT 44
#define DIN  45
#define DCS  46
#define DCLK 47
//CS   -  42
//RST  -  48
//DC   -  49
//MOSI -  51
//SCK  -  52

TFT_ILI9341 tft = TFT_ILI9341();
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT);

int color = TFT_WHITE;

void setupLCD() {
  
}

void TFTdisplay() {
  
}
