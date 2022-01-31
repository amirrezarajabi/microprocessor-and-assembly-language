#include <LiquidCrystal.h>
#include <Keypad.h>

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

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd( RS, E, D4, D5, D6, D7 );

char MAP[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char TURN[2] = {'Y', 'G'};
int turn = 0;
int isDone = 0;
int restart = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20, 4);
  lcd.clear();
  Serial.begin(9600);
  printMap('Y');
}

void loop() {
  // put your main code here, to run repeatedly:
  
  char c = keypad.getKey();
  if(c){
    if (isDone){
      if(c == 'O'){
        resetMap();
        printMap('Y');
        isDone = 0;
        turn = 0;
        Serial.print('O');
      }
    } else if (isDone == 0 && (c >= '1' && c <= '9')  && turn == 1){
      if(checkEmpty(c - '0')){
        Do(1, c-'0');
        Serial.print(c);
        printMap('Y');
        int win = checkWinner();
        if ((win != -1 && len() < 9) || (win == -1 && len() == 9)){
          printResult(win);
          turn = 0;
          isDone = 1;
        } else {
          turn = 1 - turn;
        }
      }
    }
  }



  if (Serial.available() > 0){
    char cc = Serial.read();
    if(cc == 'O'){
      resetMap();
      printMap('Y');
      isDone = 0;
      turn = 0;
    }
    else if(cc >= '1' && cc <= '9'){
      Do(0, cc-'0');
      printMap('G');
      int win = checkWinner();
      if ((win != -1 && len() < 9) || (win == -1 && len() == 9)){
        printResult(win);
        turn = 0;
        isDone = 1;
      } else {
        turn = 1 - turn;
      }
    }
  }
}

void printTurn(char turn){
  lcd.setCursor(8,0);
  lcd.print(String(turn));
  lcd.print("-Turn");
}

void printMap(char turn) {
  lcd.clear();
  printTurn(turn);
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, i + 1);
    lcd.print("|");
    lcd.print((String)MAP[i][0]);
    lcd.print("|");
    lcd.print((String)MAP[i][1]);
    lcd.print("|");
    lcd.print((String)MAP[i][2]);
    lcd.print("|");
  }
}

void resetMap(){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      MAP[i][j] = ' ';
    }
  }
}

int X(int i){
  return (i - 1) / 3;
}

int Y(int i){
  return (i - 1) % 3;
}

int checkEmpty(int i){
  if (MAP[X(i)][Y(i)] != ' '){
    return 0;
  }
  return 1;
}

void Do(int turn, int i){
  MAP[X(i)][Y(i)] = TURN[turn];
}

int checkWinner(){
   if(MAP[0][0] == MAP[0][1] && MAP[0][0] == MAP[0][2] and MAP[0][0] != ' '){
    return whoIsWinner(MAP[0][0]);
   }
   if(MAP[1][0] == MAP[1][1] && MAP[1][0] == MAP[1][2] and MAP[1][0] != ' '){
    return whoIsWinner(MAP[1][0]);
   }
   if(MAP[2][0] == MAP[2][1] && MAP[2][0] == MAP[2][2] and MAP[2][0] != ' '){
    return whoIsWinner(MAP[2][0]);
   }
   if(MAP[0][0] == MAP[1][0] && MAP[0][0] == MAP[2][0] and MAP[0][0] != ' '){
    return whoIsWinner(MAP[0][0]);
   }
   if(MAP[0][1] == MAP[1][1] && MAP[0][1] == MAP[2][1] and MAP[0][1] != ' '){
    return whoIsWinner(MAP[0][1]);
   }
   if(MAP[0][2] == MAP[1][2] && MAP[0][2] == MAP[2][2] and MAP[0][2] != ' '){
    return whoIsWinner(MAP[0][2]);
   }
   if(MAP[0][0] == MAP[1][1] && MAP[0][0] == MAP[2][2] and MAP[0][0] != ' '){
    return whoIsWinner(MAP[0][0]);
   }
   if(MAP[0][2] == MAP[1][1] && MAP[0][2] == MAP[2][0] and MAP[0][2] != ' '){
    return whoIsWinner(MAP[0][2]);
   }
   return -1;
}

int whoIsWinner(char winner){
  if(winner == TURN[1]){
    return 1;
  }
  if (winner == TURN[0]){
    return 0;
  }
  return -1;
}

void printResult(int winner){
  lcd.clear();
  lcd.setCursor(8, 0);
  if (winner == -1){
    lcd.print("Draw");  
  }
  else {
    lcd.print(TURN[winner]);
    lcd.print(" is winner");
  }
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, i + 1);
    lcd.print("|");
    lcd.print((String)MAP[i][0]);
    lcd.print("|");
    lcd.print((String)MAP[i][1]);
    lcd.print("|");
    lcd.print((String)MAP[i][2]);
    lcd.print("|");
  }
}

int len(){
  int x = 0;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if(MAP[i][j] == ' '){
        x = x + 1;
      }
    }
  }
  return 9 - x;
}
