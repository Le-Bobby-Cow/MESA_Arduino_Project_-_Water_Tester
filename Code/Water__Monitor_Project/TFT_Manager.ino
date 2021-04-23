/*-----------------------------------------------------------------------------------------




  ------------------------------------------------------------------------------------------*/


//extern int MenuState;
//#define bootPage 0
//#define mainMenuPage 1
//#define filePage 2
//#define metersPage 3
//#define clockPage 4
//
////extern const int arrLengths = 60;
//
//extern float pHVal, ECVal, TempVal, TurbVal;
//extern float pHVals[arrLengths];
//extern float ECVals[arrLengths];
//extern float TempVals[arrLengths];
//extern float TurbVals[arrLengths];
//
//extern float maxpH, maxEC, maxTemp, maxTurb;
//
//extern bool recording;

int color = TFT_WHITE;
#define TFT_GREY 0x5AEB
unsigned int colors[10] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_BLACK, TFT_CYAN, TFT_YELLOW, TFT_WHITE, TFT_MAGENTA, TFT_BLACK, TFT_BLACK};

void setupLCD() {
  tft.init();
  touch.setCal(3584, 659, 3386, 640, 320, 240, 1);

  tft.setTextColor(TFT_BLACK);
  tft.setRotation(1);
  touch.setRotation(1);
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);

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

void clearDisplay() {
  tft.fillScreen(TFT_BLACK);
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
      tft.fillRect(60, 0, 120, 110, TFT_WHITE);
      tft.fillRect(190, 0, 120, 110, TFT_WHITE);
      tft.fillRect(60, 110, 120, 110, TFT_WHITE);
      tft.fillRect(190, 110, 120, 110, TFT_WHITE);

      tft.drawRect(60, 100, 120, 10, TFT_BLACK);
      tft.drawRect(190, 100, 120, 10, TFT_BLACK);
      tft.drawRect(60, 210, 120, 10, TFT_BLACK);
      tft.drawRect(190, 210, 120, 10, TFT_BLACK);

      tft.setTextSize(1);
      tft.setCursor(62, 101);
      tft.println("pH: " + String(pHVal, 2));
      tft.setCursor(192, 101);
      tft.println("EC (ppm): " + String(ECVal, 2));
      tft.setCursor(62, 211);
      tft.println("Temp (C): " + String(TempVal, 1));
      tft.setCursor(192, 211);
      tft.println("Turb. (NTU): " + String(TurbVal, 0));

      for (int i = 0; i < arrLengths - 1; i++) {
        tft.drawLine(60 + i * 2, ((100 / maxpH) * (maxpH - pHVals[i])), 60 + (1 + i) * 2, ((100 / maxpH) * (maxpH - pHVals[i + 1])), TFT_MAGENTA);
        tft.drawLine(61 + i * 2, ((100 / maxpH) * (maxpH - pHVals[i])), 61 + (1 + i) * 2, ((100 / maxpH) * (maxpH - pHVals[i + 1])), TFT_RED);
        tft.drawLine(59 + i * 2, ((100 / maxpH) * (maxpH - pHVals[i])), 59 + (1 + i) * 2, ((100 / maxpH) * (maxpH - pHVals[i + 1])), TFT_RED);
      }
      for (int i = 0; i < arrLengths - 1; i++) {
        tft.drawLine(190 + i * 2, ((100 / maxEC) * (maxEC - ECVals[i])), 190 + (1 + i) * 2, ((100 / maxEC) * (maxEC - ECVals[i + 1])), TFT_BLACK);
        tft.drawLine(191 + i * 2, ((100 / maxEC) * (maxEC - ECVals[i])), 191 + (1 + i) * 2, ((100 / maxEC) * (maxEC - ECVals[i + 1])), TFT_GREY);
        tft.drawLine(189 + i * 2, ((100 / maxEC) * (maxEC - ECVals[i])), 189 + (1 + i) * 2, ((100 / maxEC) * (maxEC - ECVals[i + 1])), TFT_GREY);
      }
      for (int i = 0; i < arrLengths - 1; i++) {
        tft.drawLine(60 + i * 2, 110 + ((100 / maxTemp) * (maxTemp - TempVals[i])), 60 + (1 + i) * 2, 110 + ((100 / maxTemp) * (maxTemp - TempVals[i + 1])), TFT_BLACK);
        tft.drawLine(61 + i * 2, 110 + ((100 / maxTemp) * (maxTemp - TempVals[i])), 61 + (1 + i) * 2, 110 + ((100 / maxTemp) * (maxTemp - TempVals[i + 1])), TFT_GREY);
        tft.drawLine(59 + i * 2, 110 + ((100 / maxTemp) * (maxTemp - TempVals[i])), 59 + (1 + i) * 2, 110 + ((100 / maxTemp) * (maxTemp - TempVals[i + 1])), TFT_GREY);
      }
      for (int i = 0; i < arrLengths - 1; i++) {
        tft.drawLine(190 + i * 2, 110 + ((100 / maxTurb) * (maxTurb - TurbVals[i])), 190 + (1 + i) * 2, 110 + ((100 / maxTurb) * (maxTurb - TurbVals[i + 1])), TFT_BLACK);
        tft.drawLine(191 + i * 2, 110 + ((100 / maxTurb) * (maxTurb - TurbVals[i])), 191 + (1 + i) * 2, 110 + ((100 / maxTurb) * (maxTurb - TurbVals[i + 1])), TFT_GREY);
        tft.drawLine(189 + i * 2, 110 + ((100 / maxTurb) * (maxTurb - TurbVals[i])), 189 + (1 + i) * 2, 110 + ((100 / maxTurb) * (maxTurb - TurbVals[i + 1])), TFT_GREY);
      }
      break;
    case clockPage:

      break;
  }
}
