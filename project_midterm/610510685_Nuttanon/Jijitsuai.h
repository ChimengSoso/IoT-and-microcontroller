// import mapping for easier create the song
#include "map.h"

byte BPM = 150;
short int MaxNote = 396;
short int MaxMap = 16*58;

// SONG[] = {note+time, note+time,........}
byte SONG[] = { 
  DS5+I, DS5+I, F5+I, FS5+I, DS5+IX, STOP+II,
  DS5+I, DS5+I, DS5+I, FS5+I, FS5+I, F5+I, CS5+IX, STOP+II,
  DS5+I, DS5+I, DS5+I, F5+I, F5+I, FS5+I,DS5+IX, STOP+II,
  DS5+I, DS5+I, DS5+I, FS5+I, FS5+I, F5+I, CS5+IX, STOP+II,
  CS5+I, DS5+I, CS5+I, B4+I, AS4+I, GS4+I, GS4+IX, STOP+II,
  FS4+I, GS4+I, FS4+I, GS4+I, FS4+I, AS4+O1, AS4+I, AS4+IX, STOP+II,
  AS4+I, AS4+I, AS4+I, GS4+O1, FS4+I, FS4+I, FS4+I, GS4+O1, AS4+O1X, STOP+O1X,
  DS5+I, DS5+I, F5+I, FS5+I, DS5+IX, STOP+II,
  DS5+I, DS5+I, DS5+I, FS5+I, FS5+I, F5+I, CS5+IX, STOP+II,
  DS5+I, DS5+I, DS5+I, F5+I, F5+I, FS5+I,DS5+IX, STOP+II,
  DS5+I, DS5+I, CS5+I, DS5+I, CS5+I, AS5+I, AS5+O1X, STOP+O1,
  AS5+I, GS5+O1X, FS5+I, FS5+O1,STOP+I,
  AS5+I, GS5+O1X, FS5+I, FS5+O1,
  DS5+I, AS5+I, GS5+O1X, FS5+I, F5+O1X, GS5+I, FS5+O1X, STOP+O2, STOP+I,
  FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, F4+I, F4+I, DS4+I, CS4+I, STOP+I,
  CS4+I, CS4+I, CS4+I, FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, FS4+I, F4+I, F4+I, FS4+I, F4+I, STOP+I, 
  DS4+I, DS4+I, F4+I, FS4+I, DS4+I, DS4+I, DS4+I, AS4+I, AS4+I, AS4+I, AS4+I, GS4+I, FS4+I, F4+I, FS4+I, STOP+I,
  DS4+I, DS4+I, F4+I, FS4+I, DS4+I, DS4+I, DS4+I, AS4+I, AS4+I, AS4+I, AS4+I, GS4+I, FS4+I, F4+I, GS4+O1, STOP+O1,
  AS3+I, AS4+I, AS4+I, AS4+I, AS4+I, AS4+I, AS4+I, AS4+I, B4+I, CS5+I, GS4+I, STOP+I, 
  GS4+I, GS4+I, GS4+I, AS4+I, GS4+I, GS4+I, DS4+I, FS4+I, DS4+I, FS4+I, DS4+I, FS4+I, DS4+I, F4+I, F4+I, FS4+I, F4+O1, STOP+I, 
  DS4+I, F4+I, FS4+I, FS4+I, F4+I, FS4+I, F4+I, FS4+I, FS4+I, FS4+I, CS4+I, CS4+I, GS4+I, STOP+I, FS4+I, STOP+I, 
  FS4+I, FS4+I, AS4+I, DS4+I, FS4+I, DS4+I, FS4+I, FS4+I, FS4+I, FS4+I, GS4+I, GS4+I, F4+I, STOP+I, FS4+I, STOP+O1, 
  FS4+II, FS4+II, GS4+I, FS4+I, GS4+I, FS4+I, GS4+I, FS4+I, GS4+I, FS4+I, GS4+I, FS4+I, GS4+I, AS4+I, AS4+O1, STOP+I, 
  FS4+II, FS4+II, GS4+I, FS4+I, GS4+I, FS4+I, GS4+I, FS4+I, GS4+I, GS4+I, STOP+I, FS4+I, GS4+I, AS4+I, AS4+O1, STOP+I,
  CS4+II, CS4+II, AS4+I, AS4+I, AS4+I, AS4+I, GS4+I, FS4+I, STOP+I, 
  CS4+I, AS4+I, AS4+I, AS4+I, AS4+I, GS4+I, FS4+I, STOP+I, 
  FS4+I, CS5+I, CS5+I, CS5+I, CS5+I, CS5+I, AS4+I, AS4+I, AS4+I, DS5+O1, CS5+O1, CS5+O2, 
  //=================================
  /*AS4*/STOP+O2, STOP+I, 
  //=================================
  DS5+I, DS5+I, F5+I, FS5+I, DS5+I, STOP+I,
  DS5+I, DS5+I, DS5+I, FS5+I, FS5+I, F5+I, CS5+I, STOP+I, 
  DS5+I, DS5+I, DS5+I, F5+I, F5+I, FS5+I, DS5+I, STOP+I, 
  DS5+I, DS5+I, DS5+I, FS5+I, FS5+I, F5+I, CS5+I, STOP+I, 
  CS5+I, DS5+I, CS5+I, B4+I, AS4+I, GS4+I, GS4+I, STOP+I,
  FS4+I, GS4+I, FS4+I, GS4+I, FS4+I, AS4+O1, AS4+I, AS4+I, STOP+I, 
  AS4+I, AS4+I, AS4+I, GS4+O1, FS4+I, FS4+I, FS4+I, GS4+O1, AS4+O1X, STOP+O1X,
  DS5+I, DS5+I, F5+I, FS5+I, DS5+I, STOP+I, 
  DS5+I, DS5+I, DS5+I, FS5+I, FS5+I, F5+I, CS5+I, STOP+I, 
  DS5+I, DS5+I, DS5+I, F5+I, F5+I, FS5+I, DS5+I, STOP+I, 
  DS5+I, DS5+I, CS5+I, DS5+I, CS5+I, AS5+I, AS5+O1X, STOP+O1,
  AS5+I, GS5+O1X, FS5+I, FS5+I, STOP+O1, 
  AS5+I, GS5+O1X, FS5+I, FS5+I, STOP+I, 
  DS5+I, AS5+I, GS5+O1X, 
  FS5+I, F5+O1X,
  GS5+I, FS5+O4, 
  STOP+II, STOP+II, STOP+II, STOP+II, STOP+II, 
};

//IOMAP[] = {button, button, button, ......} 
/* read button code in maping.xlsx*/ 

byte IOMAP[]= {
  0,2,2,2,2,0,2,2,2,2,
  2,2,2,0,2,2,2,2,2,2,
  2,0,2,2,2,2,2,2,2,0,
  0,4,4,4,4,4,4,4,0,4,
  4,4,4,2,2,2,2,2,0,2,
  //50
  2,2,4,4,4,4,4,0,0,2,
  2,2,2,2,2,0,0,2,2,2,
  2,2,2,2,0,2,2,2,2,0,
  0,0,0,2,2,2,2,2,2,2,
  0,0,1,1,1,1,0,1,2,2,
  
  2,0,8,8,8,1,2,2,2,0,
  8,8,8,0,2,2,2,2,0,8,
  8,8,4,4,4,4,0,0,0,0,
  0,0,4,4,4,4,4,4,4,4,
  4,0,8,8,8,8,0,4,4,4,
  
  4,4,4,4,4,8,8,4,8,8,
  8,0,0,4,4,4,4,4,0,2,
  2,2,2,2,2,0,0,0,0,4,
  4,4,4,4,4,4,4,4,4,0,
  2,2,2,2,0,0,2,2,2,2,

  
  2,2,0,1,1,1,1,1,1,1,
  0,0,2,2,2,2,2,2,0,0,
  8,8,8,8,0,8,8,0,2,2,
  2,2,2,2,2,8,8,8,2,4,
  4,4,4,2,2,2,2,2,2,2,
  
  2,0,4,4,4,4,4,0,0,4,
  4,4,4,4,4,4,4,0,4,0,
  4,0,2,2,0,4,4,4,4,4,
  4,4,4,0,4,0,4,0,2,2,
  0,2,2,2,2,2,2,8,8,0,
  
  2,2,2,2,2,8,8,8,1,1,
  1,1,1,0,1,0,2,2,2,2,
  2,2,2,2,2,2,2,2,2,0,
  0,0,0,2,2,2,2,2,0,1,
  2,2,2,2,2,2,0,1,2,2,
  
  2,2,2,2,2,0,4,4,4,4,
  4,4,4,0,8,8,8,8,8,8,
  8,4,4,4,4,4,4,4,0,0,
  8,8,8,8,8,8,0,0,4,4,
  4,4,4,0,0,1,2,2,2,2,
  
  2,0,0,0,0,2,2,2,2,2,
  0,0,0,2,2,2,0,0,0,1,
  1,1,1,1,0,0,0,2,2,2,
  8,8,8,1,0,2,2,0,8,8,
  8,0,2,2,2,4,8,8,8,2,
  
  4,4,4,4,4,4,4,4,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  };
/*byte IOMAP[]= {
  4,4,4,4,4,0,
  4,4,4,4,4,4,4,0,
  4,4,4,4,4,4,4,0,
  4,4,4,4,4,4,4,0,
  8,8,8,8,8,8,8,0,
  8,8,8,8,8,8,8,0,
  2,2,2,2,2,2,2,0,
  4,4,4,4,4,4,4,0,
  0,0,4,4,4,4,4,0,
  4,4,4,4,4,4,4,0,
  4,4,4,4,4,4,4,0,
  4,4,4,4,4,4,4,0,
  2,2,2,0,8,8,8,0,
  2,2,2,0,8,8,8,0,
  2,2,2,0,8,8,8,0,
  4,4,4,4,
  
};*/
