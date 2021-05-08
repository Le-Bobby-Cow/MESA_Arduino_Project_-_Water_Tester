/*-----------------------------------------------------------------------------------------
  Manager for the Electrical Conductivity Probe

  Sensor Connected to Pin A1 of Arduino

  ------------------------------------------------------------------------------------------*/
#define SensorPin A1

float offset = 0;

void setupEC() {
}

float readECRaw() {
  float rawValue;
  rawValue = float(analogRead(SensorPin)) * analogConstant;
  return rawValue;
}

float generateEC() {
  float voltage;
  voltage = readECRaw() * analogConstant * (5.0 / 1024.0);
  return voltage;
}

float generateTDS() {
  float TDS;
  float voltage = generateEC();
  TDS = ((133.42 * (pow(voltage, 3)) - (255.86 * sq(voltage)) + (857.39 * voltage)) * 0.5) - offset;
  return TDS;//constrain(TDS, 0.0, 5000.0);
}
