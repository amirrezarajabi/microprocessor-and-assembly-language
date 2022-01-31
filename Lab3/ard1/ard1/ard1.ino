//                                            code part 1
#include <LiquidCrystal.h>
#define RS 13
#define  E 12
#define D4 8
#define D5 9
#define D6 10
#define D7 11

LiquidCrystal lcd( RS, E, D4, D5, D6, D7 );

byte Y = 0;
byte X = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateScreen();
  updateCoordinate();
}

void updateScreen (){
  lcd.clear();
  lcd.setCursor( Y, X );
  lcd.print("amirreza");
}

void updateCoordinate (){
  Y++;
  if (Y == 8)
  {
    Y = 0;
    X = 1 - X;
  }
  delay(100);
}
