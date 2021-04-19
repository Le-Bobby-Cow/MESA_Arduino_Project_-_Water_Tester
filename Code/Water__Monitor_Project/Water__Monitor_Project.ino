
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
#include <TFT_Manager.h>
#include <EC_Sensor.h>
#include <PH_Sensor.h>
#include <Temp_Sensor.h>
#include <Turbidity_Sensor.h>
#include <RTC_Manager.h>
#include <SD_Manager.h>

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

}
