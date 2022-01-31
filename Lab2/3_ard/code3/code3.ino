//                                            code part 3
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
byte input = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 2; i < 11; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    input = Serial.parseInt();
    if(input > 9){
      Serial.println("Invalid Number");
    }else{
      state(LOW, 9);
      state(HIGH, input);
    }
  }
}

void state(int o, int n){
  for(int i = 2; i < n + 2; i++){
    digitalWrite(i, o);
  }
}
