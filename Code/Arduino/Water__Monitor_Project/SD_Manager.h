/*-----------------------------------------------------------------------------------------
 * 
 * 
 * 
 * 
 ------------------------------------------------------------------------------------------*/

#include <SD.h>
#include <SPI.h>

#define CSPin 42

bool SDCardPresent = false; 

File loggingFile;

void setupSD() {
  if(!SD.begin(CSPin)){
    SDCardPresent = false;
  } else {
    SDCardPresent = true;
  }
}

void logData(String data) {
   
}
