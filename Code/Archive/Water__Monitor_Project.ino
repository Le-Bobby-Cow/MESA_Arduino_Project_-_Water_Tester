
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
#include "FuncList.h"
#include "TFT_Manager.h"
#include "EC_Sensor.h"
#include "PH_Sensor.h"
#include "Temp_Sensor.h"
#include "Turbidity_Sensor.h"
#include "RTC_Manager.h"
#include "SD_Manager.h"

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

bool recording = false;


void setup() {
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
      break;
    case clockPage:

      break;
  }
  delay(100);
}

void readSensors() {
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
}
