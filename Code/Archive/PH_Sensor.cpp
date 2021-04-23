/*-----------------------------------------------------------------------------------------




  ------------------------------------------------------------------------------------------*/
#include <Arduino.h>

#define SensorPin A2
#define Offset 0.00
#define samplingInterval 20
#define numReadings 10

float pHArray[numReadings];

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
    pHArray[i] = analogRead(SensorPin);
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
