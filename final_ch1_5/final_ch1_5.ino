#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(D4);
}

void loop() {
  int pos;
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }

  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}
