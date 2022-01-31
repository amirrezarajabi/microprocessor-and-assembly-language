//                                            code part 1
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'C','0','=', '+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  // put your setup code here, to run once:
  for(int i = 2; i < 11; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if(key){
    int keyNumber = key - '0';
    state(LOW, 9);
    state(HIGH, keyNumber);
  }
}

void state(int o, int n){
  for(int i = 2; i < n + 2; i++){
    digitalWrite(i, o);
  }
}
