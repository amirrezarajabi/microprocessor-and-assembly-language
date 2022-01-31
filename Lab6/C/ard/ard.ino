#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

#define RS 13
#define  E 12
#define D4 11
#define D5 10
#define D6 9
#define D7 8

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','8','9', 'S'},
  {'4','5','6', 'D'},
  {'1','2','3', '-'},
  {'O','0','=', '+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

#define SERVO 7

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd( RS, E, D4, D5, D6, D7 );
Servo servo;

#define MOTOR 6
#define ENABLE 5
#define SP_UP 3
#define SP_DOWN 2
#define SL_UP 1
#define SL_DOWN 0
boolean IS_ON = false;
int T_SP=0;
String S_SP = "";
int T_SL=0;
String S_SL = "";
int STATE = 0;
int P_U = 0;
int P_D = 0;
int L_U = 0;
int L_D = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(SP_UP, INPUT);
  pinMode(SP_DOWN, INPUT);
  pinMode(SL_UP, INPUT);
  pinMode(SL_DOWN, INPUT);
  lcd.begin(20, 4);
  lcd.clear();
  servo.attach(SERVO);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key=keypad.getKey();
  if(key){
    if(key == 'O'){
      if(IS_ON){
        IS_ON = false; 
        analogWrite(MOTOR, 0);
        digitalWrite(ENABLE, HIGH);
        WRITE_LCD_OFF();
      }else{
        IS_ON = true;
        digitalWrite(ENABLE, LOW);
        delay(100);
        analogWrite(MOTOR, T_SP);
        WRITE_LCD();
      }
    }
    else if(key == 'S' && IS_ON){
      S_SP = "";
      STATE = 0;
    }
    else if(key == 'D' && IS_ON){
      S_SL = "";
      STATE = 1;
    }
    else if(key == '=' && IS_ON){
      if(STATE == 0){
        int sp = S_SP.toInt();
        S_SP = "";
        WRITE_LCD();
        if(sp >= 0 && sp <= 255){
          T_SP = sp;
        }
        analogWrite(MOTOR, T_SP);
        WRITE_LCD();
        delay(200);
      }else{
        int sl = S_SL.toInt();
        S_SL = "";
        if(sl >= 0 && sl <= 90){
          T_SL = sl;
        }
        WRITE_LCD();
        servo.writeMicroseconds(int(1500+((500*float(T_SL))/90)));
        delay(200);
      }
    }
    else if(IS_ON){
      if(key != '-' || key != '+'){
        if(STATE == 1){
          S_SL = S_SL + key;
        }else{
          S_SP = S_SP + key;
        }
      }
    }
  }
  
  if (digitalRead(SL_DOWN) == LOW && IS_ON) {
    T_SL -= 5;
    WRITE_LCD();
    servo.writeMicroseconds(int(1500+((500*float(T_SL))/90)));
    delay(200);
  }
  if (digitalRead(SL_UP) == LOW && IS_ON) {
    T_SL += 5;
    WRITE_LCD();
    servo.writeMicroseconds(int(1500+((500*float(T_SL))/90)));
    delay(200);
  }
  if (digitalRead(SP_DOWN) == LOW && IS_ON) {
    T_SP -= 10;
    if(T_SP < 0){
      T_SP = 0;
    }
    WRITE_LCD();
    analogWrite(MOTOR, T_SP);
    delay(200);
  }
  if (digitalRead(SP_UP) == LOW && IS_ON) {
    T_SP += 10;
    WRITE_LCD();
    analogWrite(MOTOR, T_SP);
    delay(200);
  }
}

void WRITE_LCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SPEED:");
  lcd.setCursor(0, 1);
  lcd.print(T_SP);
  lcd.setCursor(0, 2);
  lcd.print("DEGREE:");
  lcd.setCursor(0, 3);
  lcd.print(T_SL);
}
void WRITE_LCD_OFF() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OFF");
}
