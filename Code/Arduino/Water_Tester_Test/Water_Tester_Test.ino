
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
#include <Wire.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TFT_ILI9341.h> //TFT Display Library
#include <TFT_Touch.h> //Touch Functionality Library

#define TemperatureBusPin A4

#define SensorPin A0

float voltage = 0;
float sensorValue = 0;

OneWire oneWire(TemperatureBusPin);
DallasTemperature sensors(&oneWire);

int MenuState = 3;
#define bootPage 0
#define mainMenuPage 1
#define filePage 2
#define metersPage 3
#define clockPage 4

#define SensorPinEC A1

#define SensorPinpH A2
#define Offset 0.00
#define samplingInterval 20
#define numReadings 10

#define CSPin 42

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
unsigned int colors[10] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_BLACK, TFT_CYAN, TFT_YELLOW, TFT_WHITE, TFT_MAGENTA, TFT_BLACK, TFT_BLACK};

bool SDCardPresent = false;

File loggingFile;

float pHArray[numReadings];

const int arrLengths = 60;
float pHVal, ECVal, TempVal, TurbVal;
float pHVals[arrLengths];
float ECVals[arrLengths];
float TempVals[arrLengths];
float TurbVals[arrLengths];

float maxpH, maxEC, maxTemp, maxTurb = 1;

bool recording = false;

bool RTCPresent = false;
bool powerLoss = false;

RTC_DS3231 rtc;
DateTime now = rtc.now();


void setup() {
  Serial.begin(9600);
Serial.println("beans");
  //setupEC();
  //setuppH();
  //setupRTC();
  //setupSD();
  setupLCD();
  //setupTemp();
  //setupTurb();
Serial.println("success");
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



//

float readECRaw() {
  float rawValue;
  rawValue = analogRead(SensorPinEC);
  return rawValue;
}

float generateEC() {
  float voltage;
  voltage = readECRaw() * (5.0 / 1024.0);
  return voltage;
}

float generateTDS() {
  float TDS;
  float voltage = generateEC();
  TDS = (133.42 / (pow(voltage, 3)) - (255.86 * sq(voltage)) + (857.39 * voltage)) * 0.5;
  return TDS;
}


//

void setuppH() {
}

float averageArr() {
  float avgVal = 0;
  for (int i = 0; i < numReadings; i++) {
    avgVal += pHArray[i];
  }
  avgVal = avgVal / numReadings;
  return avgVal;
}

float readpH() {
  float voltage;
  for (int i = 0; i < numReadings; i++) {
    pHArray[i] = analogRead(SensorPinpH);
    delay(samplingInterval);
  }
  voltage = averageArr() * (5.0 / 1024);
  return voltage;
}

float calculatepH() {
  float pHValue;
  pHValue = (3.5 * readpH()) + Offset;
  return pHValue;
}



//

void setupRTC() {
  if (!rtc.begin()) {
    RTCPresent = false;
  } else {
    RTCPresent = true;
  }

  if (!rtc.lostPower()) {
    powerLoss = false;
  } else {
    powerLoss = true;
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void setRTC(int yyyy, int mo, int d, int h, int mi) {
  rtc.adjust(DateTime(yyyy, mo, d, h, mi , 0));
}

String logTime() {
  String logPhrase = "";
  logPhrase = (String(now.month()) + "/") + (String(now.day()) + "/") + (String(now.year()) + "  ") + (String(now.hour()) + ":") + (String(now.minute()) + ":") + String(now.second());
  return logPhrase;
}



//

void setupSD() {
  if (!SD.begin(CSPin)) {
    SDCardPresent = false;
  } else {
    SDCardPresent = true;
  }
}

void logData(String data) {}


//

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


//

void setupTemp() {
  sensors.begin();
}

void readTemperatures() {
  sensors.requestTemperatures();
}

float generateTemperatureC() {
  return sensors.getTempCByIndex(0);
}

float generateTemperatureF() {
  return ((sensors.getTempCByIndex(0)) * 9.0 / 5.0) + 32.0;
}


//

void setupTurb() {
}

float readTurbidity() {
  sensorValue = analogRead(SensorPin);
  return sensorValue;
}

float calculateTurbidity() {
  float NTU;
  voltage = readTurbidity() * (5.0 / 1024.0);
  NTU = (-1120.4 * (sq(voltage))) + (5742.3 * voltage) - 4352.9;
  return NTU;
}
