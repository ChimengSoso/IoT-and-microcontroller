#include <Servo.h> // import to connect to servo
#include <time.h> // import time to use time() to psuedo random number
#include <stdlib.h> //import standard library

const int S1 = 10; //pin9 connects to servo no.1 (move horizontally)
const int S2 = 9
; //pin10 servo no.2 (move vertically) 
const int PIR1 = 5; // PIR sensor no.1 captures motion at 0-120 degree
const int PIR2 = 3; // PIR sensor no.2 captures motion at 121-240 degree
Servo servo1; //object servo no.1
Servo servo2; //object servo no.2

void setup() {
  Serial.begin(9600);
  servo1.attach(S1);
  servo2.attach(S2);
  pinMode(PIR1,INPUT);
  pinMode(PIR2,INPUT);
  randomSeed(analogRead(0));
}

void loop() {
  getCatPos();
  delay(1000);
}
int getCatPos(){
  bool p1 = false, p2 = false;
  if (digitalRead(PIR1) == HIGH){
    p1 = true;
  }
  if (digitalRead(PIR2) == HIGH){
    p2 = true;
  }
  calculateLaser(p1,p2);
} 

int calculateLaser(bool p1, bool p2){
  int horizontal, vertical;
  Serial.print("p1 = ");
  Serial.print(p1);
  Serial.print(" p2 = ");
  Serial.print(p2);
  Serial.print("\n");
  if ((p1 == true) && (p2 == false)) {
    horizontal = random(0, 90);
  }
  else if ((p1 == false) && (p2 == true)){
    horizontal = random(91, 180);
  }
  else{
    horizontal = random(0, 180);
  }
  
  vertical = random(40, 80);
  moveLaser(horizontal, vertical);
}

void moveLaser(int h, int v){
//  Serial.print("h = ");
//  Serial.print(h);
//  Serial.print(" v = ");
//  Serial.print(v);
//  Serial.print("\n");
  servo1.write(h);
  servo2.write(v);
}
