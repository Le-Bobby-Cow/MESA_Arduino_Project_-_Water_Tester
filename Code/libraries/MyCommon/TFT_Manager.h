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

void setupLCD() {
  tft.init();
  touch.setCal(3584, 659, 3386, 640, 320, 240, 1);

  tft.setTextColor(0);
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
      if (recording) {

      } else {

      }
      tft.fillRect();
      tft.drawRect(60, 10, 120, 110, );
      tft.drawRect(190, 10, 120, 110);
      tft.drawRect(60, 120, 120, 110);
      tft.drawRect(190, 120, 120, 110);

      tft.drawRect(60, 110, 120, 10);
      tft.drawRect(190, 110, 120, 10);
      tft.drawRect(60, 220, 120, 10);
      tft.drawRect(190, 220, 120, 10);

      tft.setTextSize(8);
      tft.drawString("pH: " + pHVal, 62, 119);
      tft.drawString("EC (ppm): " + ECVal, 192, 119);
      tft.drawString("Temp (C): " + TempVal, 62, 229);
      tft.drawString("Turb. (NTU): " + TurbVal, 192, 229);

      for (int i = 0; i < arrLengths - 1; i++) {
        tft.drawLine(60 + i * 2, 10 + ((100 / maxpH) * (maxpH - pHVals[i])), 60 + (1 + i) * 2, 10 + ((100 / maxpH) * (maxpH - pHVals[i + 1])), TFT_RED);
      }
      for (int i = 0; i < arrLengths - 1; i++) {
        tft.drawLine(190 + i * 2, 10 + ((100 / maxEC) * (maxEC - ECVals[i])), 190 + (1 + i) * 2, 10 + ((100 / maxEC) * (maxEC - ECVals[i + 1])), TFT_RED);
      }
      for (int i = 0; i < arrLengths - 1; i++) {
        tft.drawLine(60 + i * 2, 120 + ((100 / maxTemp) * (maxTemp - TempVals[i])), 60 + (1 + i) * 2, 120 + ((100 / maxTemp) * (maxTemp - TempVals[i + 1])), TFT_RED);
      }
      for (int i = 0; i < arrLengths - 1; i++) {
        tft.drawLine(190 + i * 2, 120 + ((100 / maxTurb) * (maxTurb - TurbVals[i])), 190 + (1 + i) * 2, 120 + ((100 / maxTurb) * (maxTurb - TurbVals[i + 1])), TFT_RED);
      }
      break;
    case clockPage:

      break;
  }
