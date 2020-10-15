#include "FS.h"

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  // SPIFFS.format();
  if (SPIFFS.exists("/config.txt")) {
    Serial.println("found");
  } else {
    Serial.println("not found");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
