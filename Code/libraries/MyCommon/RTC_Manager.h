/*-----------------------------------------------------------------------------------------




  ------------------------------------------------------------------------------------------*/

#include <Wire.h>
#include <RTClib.h>

bool RTCPresent = false;
bool powerLoss = false;

RTC_DS3231 rtc;
DateTime now = rtc.now();

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
