/*-----------------------------------------------------------------------------------------




  ------------------------------------------------------------------------------------------*/
#include <Arduino.h>
#define SensorPin A1

void setupEC() {
}

float readECRaw() {
  float rawValue;
  rawValue = analogRead(SensorPin);
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
