#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

LiquidCrystal_I2C lcd(0x3f, 16, 2);

const int POT = 0;
const int MOTOR = 6;
const int SPEAKER = 9;
const int IR = 1;

const int R = 3;
const int G = 5;
const int B = 10;

byte p0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte p1[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};

byte p2[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};

byte p3[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};

byte p4[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};

byte p5[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte arrow[8] = {
  B00000,
  B00111,
  B00011,
  B00101,
  B01000,
  B10000,
  B00000,
  B00000
};

byte collisionAvoid[8] = {
  B11100,
  B10000,
  B10000,
  B11100,
  B00111,
  B00101,
  B00111,
  B00101
};

byte caDis1[8] = {
  B00000,
  B10000,
  B01000,
  B00100,
  B00100,
  B01000,
  B10000,
  B00000
};

byte caDis2[8] = {
  B01000,
  B10100,
  B01010,
  B00101,
  B00101,
  B01010,
  B10100,
  B01000
};

int pot_val = 0;
int rpm = 0;
int rpmScale = 0;
int distance = 0;
int distanceScale = 0;
int speedMeter = 0;
int distScale = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, p0);
  lcd.createChar(1, p1);
  lcd.createChar(2, p2);
  lcd.createChar(3, p3);
  lcd.createChar(4, p5);
  lcd.createChar(6, collisionAvoid);
  lcd.createChar(9, caDis1);
  lcd.createChar(10, caDis2);
  lcd.setCursor(0, 0);
  lcd.print("SPD:  ");
  lcd.setCursor(8, 0);
  lcd.write(6);
  lcd.print(":");
  startUp();

  pinMode(MOTOR, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
  for (int i = 0; i <= 255; i++) {
    rgb(0, i, 0);
    delay(5);
  }
  for (int i = 0; i <= 10; i++) {
    lcd.setCursor(10 + (i / 2), 0);
    if (i % 2 == 0) {
      lcd.write(7);
    } else {
      lcd.write(8);
    }
    delay(10);
  }
  lcd.setCursor(4, 0);
  lcd.print("  ");
}

void loop() {
  distance = analogRead(IR); //Read IR Sensor
  distance = map(distance, 50, 500, 0, 255); //scale it to LED range
  distance = constrain(distance, 0, 255);
  distScale = map(distance, 0, 150, 0, 10);
  Serial.print(rpmScale);
  Serial.print("\t");
  Serial.println(distance);
  if (distance >= 180 && rpmScale > 10) {
    slowDown();
  }

  pot_val = analogRead(POT);
  rpm = map(pot_val, 0, 1023, 0, 255);
  rpmScale = map(pot_val, 0, 1023, 0, 80);
  analogWrite(MOTOR, rpm);
  lcd.setCursor(0, 1);
  lcd.setCursor(rpmScale / 5, 1);
  lcd.write(rpmScale % 5);

  lcd.setCursor(4, 0);
  speedMeter = rpmScale;
  lcd.print(speedMeter);

  lcd.setCursor(10 + (distScale / 2), 0);
  if (distScale % 2 == 0) {
    lcd.write(9);
  } else {
    lcd.write(10);
  }
  lcd.print("       ");
  //Serial.println(rpm);
}

void slowDown() {
  for (int i = 0; i < 8; i++) {
    tone(SPEAKER, 4186, 100);
    delay(100);
    if (i % 2 == 0) {
      rgb(255, 0, 0);
    } else {
      rgb(0, 0, 0);
    }
  }
  rgb(255, 0, 0);
  for (int i = rpmScale; i > 0; i--) {
    int rpmTemp = map(i, 0, 80, 0, 255);
    lcd.setCursor(4, 0);
    if (speedMeter == 1) {
      lcd.print(speedMeter - 1);
    } else {
      lcd.print(speedMeter);
    }
    if (speedMeter < 10) {
      lcd.setCursor(5, 0);
      lcd.print(" ");
    }
    lcd.setCursor(0, 1);
    lcd.setCursor(i / 5, 1);
    lcd.write(i % 5);
    analogWrite(MOTOR, rpmTemp);
    speedMeter--;
    delay(10);
  }
  lcd.setCursor(0, 1);
  lcd.print("               ");
  while (rpmScale > 0) {
    pot_val = analogRead(POT);
    rpmScale = map(pot_val, 0, 1023, 0, 80);
  }
  rgb(0, 255, 0);
  tone(SPEAKER, 4186, 500);
  delay(500);
}

void rgb(int r, int g, int b) {
  analogWrite(R, r);
  analogWrite(G, g);
  analogWrite(B, b);
}

void startUp() {
  // Screen Start
  for (int i = 0; i <= 80; i++) {
    lcd.setCursor(4, 0);
    lcd.print(i);
    lcd.setCursor(i / 5, 1);
    lcd.write(i % 5);
    delay(5);
  }
  for (int i = 80; i >= 0; i--) {
    lcd.setCursor(4, 0);
    lcd.print(i);
    lcd.setCursor(i / 5, 1);
    lcd.write(i % 5);
    delay(5);
  }
  // CA Start
  for (int i = 0; i <= 10; i++) {
    lcd.setCursor(10 + (i / 2), 0);
    if (i % 2 == 0 && i != 10) {
      lcd.write(9);
    } else {
      lcd.write(10);
    }
    delay(10);
  }

  // RGB Start
  int rgbState = 0;
  for (int i = 0; i <= 255; i++) {
    rgb(i, 0, 0);
    delay(2);
  }
  for (int i = 0; i <= 255; i++) {
    rgb(0, i, 0);
    delay(2);
  }
  for (int i = 0; i <= 255; i++) {
    rgb(0, 0, i);
    delay(2);
  }
}
