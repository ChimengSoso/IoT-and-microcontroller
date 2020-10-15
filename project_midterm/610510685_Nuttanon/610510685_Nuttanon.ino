/*  if you want to read everything 
download .zip here: https://drive.google.com/file/d/1L6Pq2a4wQ8NO7SR4rh33i-oF3oXJ9U8l/view?usp=sharing*/

#include "Jijitsuai.h" //import note & input map
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


/*init hardware*/
const byte BUTTON4=2;
const byte BUTTON3=4;
const byte BUTTON2=7;
const byte BUTTON1=8;
const byte BLED=3;
const byte GLED=5;
const byte RLED=6;
const byte MAJOR_SPEAKER=9;
const byte MINOR_SPEAKER=10;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

/*init display*/
byte bufferA[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
byte bufferB[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
byte insertIndex = 0;

byte allOne[] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B00000,
  B11111,
  B11111,
  B11111,
};
byte rightOne[] ={
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
};
byte leftOne[] ={
  B00000,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
};
byte allZero[] ={
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

void setup() {
  Serial.begin(9600);
  // init hardware
  pinMode(BUTTON4, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);

  // init display
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  //create display pattern
  lcd.createChar(0, allZero);
  lcd.createChar(1, rightOne);
  lcd.createChar(2, leftOne);
  lcd.createChar(3, allOne);
  // print welcome msg
  lcd.setCursor(0, 0);
  lcd.print("   Welcome to   ");
  lcd.setCursor(0, 1);
  lcd.print("The IRG Project");
  delay(3000);
  
}

void loop() {
  // init display 
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  
  // print instruction msg  
  lcd.setCursor(0, 0);
  lcd.print("Pls rotate LCD &");
  lcd.setCursor(0, 1);
  lcd.print("Press any button");

  
  // wait user respond to start game
  while (true) {
    if ((digitalRead(BUTTON1)==HIGH)||(digitalRead(BUTTON2)==HIGH)||(digitalRead(BUTTON3)==HIGH)||(digitalRead(BUTTON4)==HIGH)) {
      lcd.clear();
      break;
      }
  }
  
  
  // play LOOP
  int songIndex=0;
  int displayMapIndex=0;
  int checkMapIndex=0;
  byte lcdSkipms = 0;
  byte inputSkipms = 31;
  byte soundSkipms = 30;
  short int note = 0;
  short int times = 0;
  short int dlay = 0;
  int Clock = 0;
  float score = 0;
  bool bt1 = false;
  bool bt2 = false;
  bool bt3 = false;
  bool bt4 = false;
  bool reset = false;
  byte curSor = 15;
  int maxScore=0;
  while (songIndex<=MaxNote) {
    
    // sound player =======================
    if (soundSkipms <=0) {
      // get note
      note = SONG[songIndex]%16;
      // get time
      times = SONG[songIndex]/16;
      //maping note
      switch (note) {
        case 0: 
          note=233;
          break;
         case 1:
          note=277;
          break;
         case 2:
          note=311;
          break;
         case 3:
          note=349;
          break;
         case 4:
          note=370;
          break;
         case 5:
          note=415;
          break;
         case 6:
          note=466;
          break;
         case 7:
          note=494;
          break;
         case 8:
          note=554;
          break;
         case 9:
          note=622;
          break;
         case 10:
          note=698;
          break;
         case 11:
          note=740;
          break;
         case 12:
          note=831;
          break;
         case 13:
          note=932;
          break;
         case 15:
          note=0;
          break;
      }
      //maping time
      switch(times) {
        case 0:
          times=16;
          break;
        case 1:
          times=8;
          break;
        case 2:
          times=4;
          break;
        case 3:
          times=2;
          break;
        case 4:
          times=1;
          break;
        case 5:
          times=24;
          break;
        case 6:
          times=12;
          break;
        case 7:
          times=6;
          break;
        case 8:
          times=3;
          break;
      }
      //space between note 
      noTone(MAJOR_SPEAKER);
      delay(10);
      
      // play the note
      if (note == 15) {
        noTone(MAJOR_SPEAKER);
      }
      else {
        tone(MAJOR_SPEAKER, note, 5000); // play note until new note coming
        dlay++;
      }
      
      // setdelay(how long of that note)
      soundSkipms=times*1;
      // update note index
      songIndex++;
      
    }
    // MONOR SOUND =================
    /* comming soon*/
    
    // LCD =========================
    if (lcdSkipms <=0) {
      // read input map and store input in buffer
      switch (IOMAP[displayMapIndex]) {
        case 0:
          bufferA[insertIndex]=0;
          bufferB[insertIndex]=0;
          break;
        case 1:
          bufferA[insertIndex]=0;
          bufferB[insertIndex]=1;
          break;
        case 2:
          bufferA[insertIndex]=0;
          bufferB[insertIndex]=2;
          break;
        case 3:
          bufferA[insertIndex]=0;
          bufferB[insertIndex]=3;  
          break;
        case 4:
          bufferA[insertIndex]=1;
          bufferB[insertIndex]=0;   
          break;
        case 5:
          bufferA[insertIndex]=1;
          bufferB[insertIndex]=1;   
          break;
        case 6:
          bufferA[insertIndex]=1;
          bufferB[insertIndex]=2;
          break;
        case 7:
          bufferA[insertIndex]=1;
          bufferB[insertIndex]=3;  
          break;
        case 8:
          bufferA[insertIndex]=2;
          bufferB[insertIndex]=0;  
          break;
        case 9:
          bufferA[insertIndex]=2;
          bufferB[insertIndex]=1;   
          break;
        case 10:
          bufferA[insertIndex]=2;
          bufferB[insertIndex]=2;  
          break;
        case 11:
          bufferA[insertIndex]=2;
          bufferB[insertIndex]=3;   
          break;
        case 12:
          bufferA[insertIndex]=3;
          bufferB[insertIndex]=0;   
          break;
        case 13:
          bufferA[insertIndex]=3;
          bufferB[insertIndex]=1;    
          break;
        case 14:
          bufferA[insertIndex]=3;
          bufferB[insertIndex]=2;    
          break;
        case 15:
          bufferA[insertIndex]=3;
          bufferB[insertIndex]=3;    
          break;
      }

      // update input map index
      displayMapIndex++;
      
      // print from buffer
      for (int bfIndex=0; bfIndex<16; bfIndex++) {  
        // upper row of LCD
        lcd.setCursor(bfIndex, 0);
        switch (bufferA[(bfIndex+insertIndex+1)%16]){
          case 0:
            lcd.write(0);
            //lcd.print("00");
            break;
          case 1:
            lcd.write(1);
            //lcd.print("01");
            break;
          case 2:
            lcd.write(2);
            //lcd.print("10");
            break;
          case 3:
            lcd.write(3);
            //lcd.print("11");
            break;
        }
        // lower row of LCD
        lcd.setCursor(bfIndex, 1);
        switch (bufferB[(bfIndex+insertIndex+1)%16]) {
          case 0:
            lcd.write(0);
            //lcd.print("00");
            break;
          case 1:
            lcd.write(1);
            //lcd.print("01");
            break;
          case 2:
            lcd.write(2);
            //lcd.print("10");
            break;
          case 3:
            lcd.write(3);
            //lcd.print("11");
            break;
        }
      }
      // update skip (it look like fps) 
      lcdSkipms = 2; 

      // buffer insert index
      if (insertIndex <15)insertIndex++;
      else insertIndex=0;
    }
    
    // input managed ================
    if (inputSkipms <=0) {
      // define button state
      if (digitalRead(BUTTON1)==HIGH)bt1=true;
      else bt1=false;
      if (digitalRead(BUTTON2)==HIGH)bt2=true;
      else bt2=false;
      if (digitalRead(BUTTON3)==HIGH)bt3=true;
      else bt3=false;
      if (digitalRead(BUTTON4)==HIGH)bt4=true;
      else bt4=false;
      
      // read scoremap and assign maxScore  
      maxScore++;
      switch (IOMAP[checkMapIndex]) {
        // if no input it note count as maxScore
        case 0:
        maxScore--;
          break;
        // give score and set color of LED 
        case 8:
          if (bt1) {
            analogWrite(GLED, 5);
            score++;
          }
          else{
            analogWrite(RLED, 5);
          }
          break;
        case 4:
          if (bt2) {
            analogWrite(GLED, 5);
            score++;
          }
          else{
            analogWrite(RLED, 5);
          }
          break;
        case 2:
          if (bt3) {
            analogWrite(GLED, 5);
            score++;
          }
          else{
            analogWrite(RLED, 5);
          }
          break;
        case 1:
          if (bt4) {
            analogWrite(GLED, 5);
            score++;
          }
          else{
            analogWrite(RLED, 5);
          }
          break;
        case 12:
          if ((bt1)&&(bt2)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 10:
          if ((bt1)&&(bt3)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 9:
          if ((bt1)&&(bt4)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 6:
          if ((bt2)&&(bt3)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 5:
          if ((bt2)&&(bt4)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 3:
          if ((bt3)&&(bt4)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 14:
          if ((bt1)&&(bt2)&&(bt3)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 13:
          if ((bt1)&&(bt2)&&(bt4)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 11:
          if ((bt1)&&(bt3)&&(bt4)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 7:
          if ((bt2)&&(bt3)&&(bt4)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        case 15:
          if ((bt1)&&(bt2)&&(bt3)&&(bt4)) {
            analogWrite(GLED, 15);
            score++;
          }
          else{
            analogWrite(RLED, 15);
          }
          break;
        
      }
      // update checkInputMapIndex
      checkMapIndex++;
      // input sensitive
      inputSkipms = 2;

      // To create input map EASY!!!!, I MADE THIS.
      Serial.print(checkMapIndex);
      if (bt1)Serial.println(",1");
      else if (bt2)Serial.println(",2");
      else if (bt3)Serial.println(",3");
      else if (bt4)Serial.println(",4");
      else Serial.println(",0");
      
    }
    
    // update skip, made delay (don't know that clock speed of processor)================
    lcdSkipms--;
    inputSkipms--;
    soundSkipms--;
    Clock++;
    delay(48);//((60000/BPM)/4));
    analogWrite(RLED, 0);
    analogWrite(GLED, 0);
    analogWrite(BLED, 0);
    
  }//end LOOP

  
  // calculate score and print score (debug with Serial)
  Serial.print("Score: ");
  Serial.print(score);
  Serial.print("/");
  Serial.println(maxScore);
  score = score*10000/maxScore;
  Serial.print("Fianl_Score: ");
  Serial.println(score);
  delay(2000);

  // print score in LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Score: ");
  lcd.setCursor(11, 0);
  lcd.print((int)score);
  lcd.setCursor(0, 1);
  lcd.print("Press to Replay");

  
  // wait user respond to restart
  while (true) {
    if ((digitalRead(BUTTON1)==HIGH)||(digitalRead(BUTTON2)==HIGH)||(digitalRead(BUTTON3)==HIGH)||(digitalRead(BUTTON4)==HIGH)) {
      lcd.setCursor(0, 1);
      lcd.print("Restarting......");
      for (int i=0; i<16; i++) {
        bufferA[i] = 0;
        bufferB[i] = 0;
      }
      lcd.createChar(0, allZero);
      lcd.createChar(1, rightOne);
      lcd.createChar(2, leftOne);
      lcd.createChar(3, allOne);
      insertIndex = 0;
      break;
      }
  }

  
  
}
