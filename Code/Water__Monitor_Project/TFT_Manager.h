/*-----------------------------------------------------------------------------------------




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
unsigned int colors[10] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_BLACK, TFT_CYAN, TFT_YELLOW, TFT_WHITE, TFT_MAGENTA, TFT_BLACK, TFT_BLACK};

int MenuState = 0;
#define bootPage 0
#define mainMenuPage 1
#define filePage 2
#define metersPage 3
#define clockPage 4

void setupLCD() {
  tft.init();
  touch.setCal(3584, 659, 3386, 640, 320, 240, 1);

  tft.setRotation(1);
  touch.setRotation(1);
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
}

void readTouch() {
  int X_RawData;
  int Y_RawData;
  int X_Coord;
  int Y_Coord;

  if (touch.Pressed()) {
    X_Coord = touch.X();
    Y_Coord = touch.Y();
    switch (MenuState) {
      case bootPage:

        break;
      case mainMenuPage:

        break;
      case filePage:

        break;
      case metersPage:

        break;
      case clockPage:

        break;
    }
  }
}

void TFTdisplay() {
  switch (MenuState) {
    case bootPage:

      break;
    case mainMenuPage:

      break;
    case filePage:

      break;
    case metersPage:

      break;
    case clockPage:

      break;
  }
