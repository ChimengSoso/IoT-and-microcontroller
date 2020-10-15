int stastus;
int LED1=2;
int LED2=3;
int LED3=4;
int LED4=5;
int LED5=6;
int LED6=7;
int LED7=8;
int LED8=9;
int LED9=10;

boolean LEDStatus=false;
void setup() {

pinMode(A0, INPUT); 
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
pinMode(LED5, OUTPUT);
pinMode(LED6, OUTPUT);
pinMode(LED7, OUTPUT);
pinMode(LED8, OUTPUT);
//pinMode(A0, OUTPUT); //กำหนด Pin 13 เป็น OUTPUT

 

 

  //เปิดใช้งาน comport

 

  Serial.begin(9600);

 

}

 

// Loop การทำงานโปรแกรม

 

void loop() {

 

  // อ่านค่าเสียงจาก analog pin 0 หรือ A0 

 

  int sensorValue = analogRead(A0); //ประกาศตัวแปร เพื่อรับว่า ที่อ่านมาได้
  Serial.println(sensorValue); // แสดงค่าที่อ่านได้ผ่าน Serial moniter 
  
  delay(50);        // หน่วงเวลาเพื่อกลับไปอ่านใหม่ 1 วินาที
  if( sensorValue >= 700 && sensorValue < 1024)
  {
    digitalWrite(LED1, HIGH);
    delay(10);
    digitalWrite(LED2, HIGH);
    delay(10);
    digitalWrite(LED3, HIGH);
    delay(10);
    digitalWrite(LED3,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED1,LOW);
  }
  else if( sensorValue >= 600 && sensorValue < 700)
  {
    digitalWrite(LED1, HIGH);
    delay(10);
    digitalWrite(LED2, HIGH);
    delay(10);
    digitalWrite(LED3, HIGH);
    delay(10);
    digitalWrite(LED4, HIGH);
    delay(10);
    digitalWrite(LED5, HIGH);
    delay(10);
    digitalWrite(LED6, HIGH);
    delay(10);
    digitalWrite(LED6,LOW);
    digitalWrite(LED5,LOW);
    digitalWrite(LED4,LOW);
  }
  else if(sensorValue >= 100 && sensorValue < 650 )
  {
    digitalWrite(LED1, HIGH);
    delay(10);
    digitalWrite(LED2, HIGH);
    delay(10);
    digitalWrite(LED3, HIGH);
    delay(10);
    digitalWrite(LED4, HIGH);
    delay(10);
    digitalWrite(LED5, HIGH);
    delay(10);
    digitalWrite(LED6, HIGH);
    digitalWrite(LED7, HIGH);
    delay(10);
    digitalWrite(LED8, HIGH);
    delay(10);
    digitalWrite(LED9, HIGH);
    delay(10);
    digitalWrite(LED9,LOW);
    digitalWrite(LED8,LOW);
    digitalWrite(LED7,LOW);
  }
  /*else
  {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(LED5,LOW);
    digitalWrite(LED6,LOW);
    digitalWrite(LED7,LOW);
    digitalWrite(LED8,LOW);
    digitalWrite(LED9,LOW);
  }*/
  
 
  
  
 

if (sensorValue<=100) // ระดับเสียงที่อ่านได้ถ้าเบาค่า analog ที่อ่านได้จะมาก

{

 stastus=!stastus; // ถ้า ON อยู่ให้ OFF ถ้า OFF อยู่ให้ ON

 digitalWrite(13, stastus); // PIN 13 ทำงาน

 delay(500);

}

 

}

 
