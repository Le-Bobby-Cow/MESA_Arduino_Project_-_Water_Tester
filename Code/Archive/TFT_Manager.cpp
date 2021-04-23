/*-----------------------------------------------------------------------------------------




  ------------------------------------------------------------------------------------------*/
#include <Arduino.h>

#include "TFT_ILI9341.h" //TFT Display Library
#include "TFT_Touch.h" //Touch Functionality Library
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

extern int MenuState;
#define bootPage 0
#define mainMenuPage 1
#define filePage 2
#define metersPage 3
#define clockPage 4

extern const int arrLengths = 60;

extern float pHVal, ECVal, TempVal, TurbVal;
extern float pHVals[arrLengths];
extern float ECVals[arrLengths];
extern float TempVals[arrLengths];
extern float TurbVals[arrLengths];

extern float maxpH, maxEC, maxTemp, maxTurb;

extern bool recording;

int color = TFT_WHITE;
unsigned int colors[10] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_BLACK, TFT_CYAN, TFT_YELLOW, TFT_WHITE, TFT_MAGENTA, TFT_BLACK, TFT_BLACK};

void setupLCD() {
  tft.init();
  touch.setCal(3584, 659, 3386, 640, 320, 240, 1);

  tft.setTextColor(TFT_BLACK);
  tft.setRotation(1);
  touch.setRotation(1);
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  Serial.println("success");
  //tft.setTextColor(TFT_GREEN);
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
  tft.fillScreen(TFT_BLACK);
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
      tft.fillRect(60, 10, 120, 110, TFT_WHITE);
      tft.fillRect(190, 10, 120, 110, TFT_WHITE);
      tft.fillRect(60, 120, 120, 110, TFT_WHITE);
      tft.fillRect(190, 120, 120, 110, TFT_WHITE);

      tft.drawRect(60, 110, 120, 10, TFT_BLACK);
      tft.drawRect(190, 110, 120, 10, TFT_BLACK);
      tft.drawRect(60, 220, 120, 10, TFT_BLACK);
      tft.drawRect(190, 220, 120, 10, TFT_BLACK);

      tft.setTextSize(8);
      tft.setCursor(62, 119);
      tft.println("pH: " + String(pHVal, 2));
      tft.setCursor(192, 119);
      tft.println("EC (ppm): " + String(ECVal, 2));
      tft.setCursor(62, 229);
      tft.println("Temp (C): " + String(TempVal, 1));
      tft.setCursor(192, 229);
      tft.println("Turb. (NTU): " + String(TurbVal, 0));

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
}
