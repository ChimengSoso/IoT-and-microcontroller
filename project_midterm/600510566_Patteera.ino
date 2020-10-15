
// ledPin1
int mosion = 13;
int val = 0;
int LED[] = {3, 5, 6, 9, 10, 11};



void setup() {

  pinMode(mosion, INPUT);
  for (int i = 0; i < 6; i++) {
    pinMode(LED[i], OUTPUT);
  }

  Serial.begin(9600);

}

void loop() {
  val = digitalRead(mosion);
  Serial.print("val=");
  Serial.println(val);

  if (val == 0) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 256; i++)
        analogWrite(LED[i], j);
      delay(500);
    }
    for (int i = 0; i < 6; i++) {
      for (int j = 255; j > 0; i++) {
        analogWrite(LED[i], j);
        delay(500);
      }
    }

  }
  else {
    for (int i = 0; i < 6; i++) {
      digitalWrite(LED[i], LOW);
    }
  }
  delay(100);
}
