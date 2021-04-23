
/*-----------------------------------------------------------------------------------------
   Arduino MESA Project 2020-2021

   Water Monitor Project
   - Monitors Various Conditions in Water for determineation of:
    - Safety
    - Quality
    - Conditions

   Integrated Modules:
   - SD Card Mod.
   - RTC Mod.
   - pH Probe
   - EC Probe
   - Temperature Probe
   - Turbidity Probe

  -----------------------------------------------------------------------------------------
*/

//TFT
#include "TFT_ILI9341.h"
#include "TFT_Touch.h"
#include <SPI.h>

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

int MenuState = 3;
#define bootPage 0
#define mainMenuPage 1
#define filePage 2
#define metersPage 3
#define clockPage 4

const int arrLengths = 60;
float pHVal, ECVal, TempVal, TurbVal;
float pHVals[arrLengths];
float ECVals[arrLengths];
float TempVals[arrLengths];
float TurbVals[arrLengths];

float maxpH, maxEC, maxTemp, maxTurb = 1;

float analogConstant;

bool recording = false;

void setup() {
//  Serial.begin(9600);
  analogConstant = (3.37 / 5.0) / (float(analogRead(A15)) / float(analogRead(A14)));
  int temp1 = analogRead(A15);
  int temp2 = analogRead(A14);
//  Serial.println(temp1);
//  Serial.println(temp2);
//  Serial.println(analogConstant,8);
  setupEC();
  setuppH();
  setupRTC();
  setupSD();
  setupLCD();
  setupTemp();
  setupTurb();
  TFTdisplay();
}

void loop() {
  switch (MenuState) {
    case bootPage:

      break;
    case mainMenuPage:

      break;
    case filePage:

      break;
    case metersPage:
      readSensors();
      TFTdisplay();
//      Serial.println(analogConstant, 8);
      float temp = (float(analogRead(A15)) * 5.0 / 1024.0) * analogConstant;
      float temp2 = analogRead(A15);
//      Serial.println(temp, 8);
//      Serial.println(temp2, 8);
//      Serial.println("update");
      break;
    case clockPage:

      break;
  }
  delay(100);
}

void readSensors() {
  analogConstant = (3.37 / 5.0) / (float(analogRead(A15)) / float(analogRead(A14)));
  pHVal = calculatepH();
  ECVal = generateTDS();
  TempVal = generateTemperatureC();
  TurbVal = calculateTurbidity();

  if (pHVal > maxpH) {
    maxpH = 5 * ceil(pHVal / 5);
  }
  if (ECVal > maxEC) {
    maxEC = 100 * ceil(ECVal / 100);
  }
  if (TempVal > maxTemp) {
    maxTemp = 10 * ceil(TempVal / 10);
  }
  if (TurbVal > maxTurb) {
    maxTurb = 100 * ceil(TurbVal / 100);
  }

  constrain(pHVal, 0, maxpH);
  constrain(ECVal, 0, maxEC);
  constrain(TempVal, 0, maxTemp);
  constrain(TurbVal, 0, maxTurb);



  for (int i = arrLengths - 1; i > 0; i--) {
    pHVals[i] = pHVals[i - 1];
    ECVals[i] = ECVals[i - 1];
    TempVals[i] = TempVals[i - 1];
    TurbVals[i] = TurbVals[i - 1];
  }
  pHVals[0] = pHVal;
  ECVals[0] = ECVal;
  TempVals[0] = TempVal;
  TurbVals[0] = TurbVal;

  for (int i = 0; i < arrLengths; i++) {
    float maxpHTemp;
    float maxECTemp;
    float maxTempTemp;
    float maxTurbTemp;

    if (pHVals[i] > maxpHTemp) {
      maxpHTemp = pHVals[i];
    }
    if (ECVals[i] > maxECTemp) {
      maxECTemp = ECVals[i];
    }
    if (TempVals[i] > maxTempTemp) {
      maxTempTemp = TempVals[i];
    }
    if (TurbVals[i] > maxTurbTemp) {
      maxTurbTemp = TurbVals[i];
    }

    maxpH = 5 * ceil(maxpHTemp / 5);
    maxEC = 100 * ceil(maxECTemp / 100);
    maxTemp = 10 * ceil(maxTempTemp / 10);
    maxTurb = 100 * ceil(maxTurbTemp / 100);
  }
}
