/*-----------------------------------------------------------------------------------------




  ------------------------------------------------------------------------------------------*/
#include <SD.h>

bool SDCardPresent = false;

File loggingFile;

void setupSD() {
  if (!SD.begin(40)) {
    SDCardPresent = false;
//    Serial.println("NoCard");
  } else {
    SDCardPresent = true;
//    Serial.println("Card");
  }
}

void logData(String data) {}
