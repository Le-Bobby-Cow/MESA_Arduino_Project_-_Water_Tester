/*-----------------------------------------------------------------------------------------
 *
 *
 *
 *
 ------------------------------------------------------------------------------------------*/

#include <OneWire.h>
#include <DallasTemperature.h>

#define TemperatureBusPin A4

OneWire oneWire(TemperatureBusPin);
DallasTemperature sensors(&oneWire);

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
