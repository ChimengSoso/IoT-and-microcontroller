#include <LiquidCrystal_I2C.h>

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD

#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int analogValue = analogRead(A0);
int sensorPin = 0;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  // set up the LCD's number of columns and rows:
  
  lcd.begin();
  lcd.clear();
  // initialize the serial communications:
  lcd.backlight();
  lcd.print("Analog reading = ");
  lcd.setCursor(0, 1);
  lcd.print(analogValue);    

  delay(1000);


  
}

void loop() {
  // reads the input on analog pin A0 (value between 0 and 1023)
  int analogValue = analogRead(A0);


  int reading = analogRead(sensorPin);

// converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
 voltage /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");
 
 delay(1000); 

 
  

  Serial.print("Analog reading = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 40) {
    Serial.println(" - Dark"),digitalWrite(9, HIGH);
  } else if (analogValue < 400) {
    Serial.println(" - Dim"),digitalWrite(10, HIGH);
  } else if (analogValue < 600) {
    Serial.println(" - Light"),digitalWrite(11, HIGH);
  } else if (analogValue < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  delay(500);
}
