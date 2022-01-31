#include <Keypad.h>
#include <Servo.h>

Servo servo;

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

String num = "";

void setup() {
  // put your setup code here, to run once:
  servo.attach(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  char dig = keypad.getKey();
  if(dig && isDigit(dig)){
    num += dig;
  }else if(dig){
    set();
  }
}

void set(){
  int numToInt = num.toInt();
  if(numToInt >= 0 && numToInt <= 360){
    numToInt = map(numToInt, 0, 360, 1000, 2000);
    servo.writeMicroseconds(numToInt);
  }
  num = "";
}
