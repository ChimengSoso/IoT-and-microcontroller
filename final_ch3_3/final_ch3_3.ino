#include "FS.h"

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  SPIFFS.format();
  if (SPIFFS.exists("/config.txt")) {
    Serial.println("found");
  } else {
    Serial.println("not found");
  }
  File f = SPIFFS.open("/config.txt", "w");
  if (!f) {
    Serial.println("file open failed");
  }
  Serial.println("--Write file--");
  for (int i = 1; i <= 10; i++) {
    f.println(i);
    Serial.println(i);
  }
  f.close();
  Serial.println("--Read file--");
  File fr = SPIFFS.open("/config.txt", "r");
  if (!fr) {
    Serial.println("file open failed");
  }
  while (fr.available()) {
    String v = fr.readStringUntil('\n');
    int value = v.toInt();
    Serial.println(value);
  }
  fr.close();
  if (SPIFFS.exists("/config.txt")) {
    Serial.println("found");
  } else {
    Serial.println("not found");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
