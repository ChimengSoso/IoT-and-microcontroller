const int IR = 0;
const int Pump = 8;
int distance  ;

void setup() {
  Serial.begin(9600);
  pinMode(Pump, OUTPUT);
  pinMode(IR, INPUT);
}

void loop() {
  distance = analogRead(IR);
  Serial.println(distance);
  if (distance >= 100){
    digitalWrite(Pump,HIGH);    
    Serial.println("on");
  }
  else{
    digitalWrite(Pump,LOW);    
    Serial.println("off");
  }
  delay(1000);
}
