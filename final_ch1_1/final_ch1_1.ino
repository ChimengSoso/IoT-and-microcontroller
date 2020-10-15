int inputPin = 5;
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
}

void loop() {
  val = digitalRead(inputPin);

  Serial.println(val);
  delay(1000);
  
}
