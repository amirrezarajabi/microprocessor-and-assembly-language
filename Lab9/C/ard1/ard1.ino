#include <Keypad.h>


#include "pitches.h"
#include "theme1.h"
#include "theme2.h"
#include "theme3.h"
#include "theme4.h"

#define PIN 30
#define S_PIN 8

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9', 'S'},
  {'4','5','6', 'D'},
  {'1','2','3', '-'},
  {'G','0','=', '+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  // put your setup code here, to run once:
  pinMode(30, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  char c=keypad.getKey();
  if(c == '1'){
    play(melody1, noteDurations1, sizeof(melody1) / sizeof(int));
  }
  else if(c == '2'){
    play(melody2, noteDurations2,sizeof(melody2) / sizeof(int));
  }
  else if(c == '3'){
    play(melody3, noteDurations3, sizeof(melody3) / sizeof(int));
  }
  else if(c == '4'){
    play(melody4, noteDurations4, sizeof(melody4) / sizeof(int));
  }
}

void play(int *MELODY, int *NOTEDURATION, int len){
  for(int i=0; i < len; i++){
    if(!digitalRead(PIN)){
      break;
    }
    int nD = 250/NOTEDURATION[i];
    tone(S_PIN, MELODY[i], nD);
    delay((int) (nD*1.3));
  }
}
