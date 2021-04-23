/*-----------------------------------------------------------------------------------------




  ------------------------------------------------------------------------------------------*/
#define SensorPin A0

float voltage = 0;
float sensorValue = 0;

void setupTurb() {
}

float readTurbidity() {
  sensorValue = float(analogRead(SensorPin)) * analogConstant;
  return sensorValue;
}

float calculateTurbidity() {
  float NTU;
  voltage = readTurbidity() * (5.0 / 1024.0);
  NTU = (-1120.4 * (sq(voltage))) + (5742.3 * voltage) - 4352.9;
  return NTU; //constrain(NTU, 0.0, 3000.0);
}
