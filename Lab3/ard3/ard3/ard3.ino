//                                            code part 3
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
  {'c','0','=', '+'}
};

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd( RS, E, D4, D5, D6, D7 );

String num1, num2;
char theOperator;
boolean operatorCheck = false;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() {
//  lcd.clear();

  char key = keypad.getKey();
  if (key){
    lcd.print(key);
    if (key == 'c')
    {
      num1 = "";
      num2 = "";
      operatorCheck = false;
      lcd.clear();
      lcd.setCursor(0, 0);
    }
    else if (key == '=')
    {
      int n1 = num1.toInt();
      int n2 = num2.toInt();
      lcd.setCursor(0, 1);
      if(theOperator == '+'){
          lcd.print(n1 + n2);
      }
      if(theOperator == '-'){
          lcd.print(n1 - n2);
      }
      if(theOperator == '*'){
          lcd.print(n1 * n2);
      }
      if(theOperator == '/'){
          lcd.print((float)n1 / n2);
      }
    }
    else if (! operatorCheck && (key == '+' || key == '-' || key == '*' || key == '/'))
    {
      theOperator = key;
      operatorCheck = true;
    }
    else if (! operatorCheck)
    {
      num1 += key;
    }
    else
    {
      num2 += key;
    }
  }
}
