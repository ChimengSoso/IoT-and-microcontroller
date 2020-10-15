int fadevalue = 1023;

void setup() {
  pinMode(D1, OUTPUT);
}

void loop() {
  analogWrite(D1, fadevalue);
  
  if (fadevalue > 0)
    fadevalue--;
  else {
    fadevalue = 1023;
    delay(100);  
  }
  
  delay(5);
}
