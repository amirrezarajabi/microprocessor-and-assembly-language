//                                            code part 2
#include <LiquidCrystal.h>
#include <Keypad.h>


#define RS 13
#define  E 12
#define D4 8
#define D5 9
#define D6 10
#define D7 11

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'*','0','=', '+'}
};

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd( RS, E, D4, D5, D6, D7 );

byte Y = 0;
byte X = 0;
String password = "";

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if(key){
    if(key == '*'){
      lcd.setCursor(0, 1);
      if(password == "9831126"){
        lcd.print("correct password");
      }else{
        lcd.print("wrong password");
      }
      password = "";
    }else{
      lcd.setCursor(0, 0);
      password = password + key;
      lcd.clear();
      lcd.print(password);
    }
  }
}
