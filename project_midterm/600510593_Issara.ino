#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  
#define DHTPIN 7     
#define DHTTYPE DHT22   
const int MOTOR=9;
const int BUTTON_drop=2; 
const int BUTTON_add=4; 
const int BUTTON_set=5; 
float Humidity;  
float Temperature; 
int Temperature_set = 25;
int rpm;
int fan1;
int fan2;
int Temperature_max = 60;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE); 

void setup()
{
  pinMode (MOTOR, OUTPUT);
  pinMode (BUTTON_drop, INPUT);
  pinMode (BUTTON_add, INPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  lcd.backlight();
}

void loop()
{
     if (digitalRead(BUTTON_set) == HIGH)
    {Temperature_set =  (25);}
    
    if (digitalRead(BUTTON_drop) == HIGH)
    {Temperature_set =  (Temperature_set - 1);}
    
    if (digitalRead(BUTTON_add) == HIGH)
    {Temperature_set =  (Temperature_set + 1);}
    Serial.println("Temperature_set = ");
    Serial.println(Temperature_set);
    
    lcd.setCursor(0, 0);
    lcd.print("Tempset=");
    lcd.print(Temperature_set);
    
    Humidity = dht.readHumidity();
    Temperature= dht.readTemperature();
    Serial.print(" %, Temp: ");
    Serial.print(Temperature);
    Serial.println(" Celsius");
    delay(1000); 
    
    lcd.setCursor(0, 1);
    lcd.print("Temp=");
    lcd.print(Temperature);         
    
    if (Temperature < Temperature_set) {
    analogWrite(MOTOR, 0);
    Serial.println(" 0 ");
    rpm=0;  }

    if (Temperature >= Temperature_set) {
    fan1=map(Temperature, Temperature_set, Temperature_max, 100, 500);
    fan2=map(fan1, 100, 500, 0, 100);
    analogWrite(MOTOR, fan1);
   
    rpm=fan2;  }

    
    lcd.setCursor(11, 1);
    lcd.print(rpm);
    lcd.print("%");
}
