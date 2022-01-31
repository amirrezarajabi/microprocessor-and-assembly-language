#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h>

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
  {'G','0','=', '+'}
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

const byte LED_P[4] = {4, 5, 6, 7};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd( RS, E, D4, D5, D6, D7 );

byte times[4] = {3, 2, 4, 2};
byte timeChange ;
int state ; 
int level ;
String str ;
bool active ;
long tic ;
long toc ;
float level_time ;
float remain_time;
float total_time ;

void SAVE_STATE();
void LOAD_STATE();
void UPDATE();
void CALCULATE_TIME();
void eeprom_write(uint16_t memory_address, uint8_t* data, int _size);
void eeprom_read(uint16_t memory_address, uint8_t* data, int _size);

void setup() {

  Serial.begin(9600);
  Wire.begin();
  pinMode(LED_P[0], OUTPUT);
  pinMode(LED_P[1], OUTPUT);
  pinMode(LED_P[2], OUTPUT);
  pinMode(LED_P[3], OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  str = "";
  state = 2 ;
  remain_time = times[0]; 
  level = 0 ;
  tic = millis();
  toc = millis();
  level_time = 3;
  active = false ;

  LOAD_STATE();

}


void loop() {
  char ch = keypad.getKey();
  if (ch) {
    // states : 0->finished , 1->paused , 2->idle , 3->active ,  4->change
    if (state==2 && (ch<='4' && ch>='1')) { 
      state = 4; //change time 
      str="";
      timeChange = ch -'0';
    } else if (state==2 && ch=='=') { 
      state = 3;
      active = true;
      tic = millis();
      level = 0;
      level_time = times[0];
    } else if (state==0 && ch=='=') { 
      state = 2;
      for (int i = 0; i < 4; i++)
        digitalWrite(LED_P[i], LOW);
    } else if (state==1 && ch=='=') { 
      state = 3;
      level_time = remain_time;
      active = true;
      tic = millis();
    } else if (state==4 && ch=='-') { 
      state = 2;
      times[timeChange-1] = str.toInt();
    } else if (state==3 && ch=='=') { 
      state = 1; 
      level_time = remain_time;
      active = false;
    } else if (state==4) { 
      str += ch;
    }
  }
  
  UPDATE();
  CALCULATE_TIME();
}

void CALCULATE_TIME(){
  long now = millis(); 
  if ((now - toc) > 200) {
    SAVE_STATE();
    toc = now;
  }
 
  if (active) {
    remain_time = ((float)level_time-((float)(millis()-tic)/1000));
      total_time = remain_time;
      for (int i = level+1 ; i < 4; i++){
        total_time += times[i];
      }
    if (remain_time <= 0) {
      level = (level+1)%4;
      tic = millis();
      level_time = times[level];
      remain_time = 0;
      if (level==0) {
        for (int i = 0; i < 4; i++)
          digitalWrite(LED_P[i], HIGH);
        active = false;
        state = 0;
      }
    }
  }
   delay(50);
}

void UPDATE(){

  lcd.clear();
  lcd.setCursor(0, 0);
  
  for (int i = 0; i < 4; i++)
    digitalWrite(LED_P[i], LOW);
    
  if (state==0) {
    for (int i = 0; i < 4; i++)
      digitalWrite(LED_P[i], HIGH);
  } else if (state==1 || state==3 ) {  
      digitalWrite(LED_P[level], HIGH);
      if (state==3) { 
        active = true;
      } 
  }
  
  if(state==0){
    lcd.print("FINISHED...");
  } else if (state==1){
    lcd.print("PAUSED...");
    lcd.setCursor(0, 1);
    lcd.print("total time:" +(String) total_time);
  } else if (state==3){
    lcd.print("ACTIVE...");
    lcd.setCursor(0, 1);
    lcd.print("total time:" +(String) total_time);
  } else if (state==2){
    lcd.print("IDLE...");
  } else if (state==4){
    lcd.print("CHANGE...");
    lcd.setCursor(0, 1);
    lcd.print("enter time :" + str);
  }

}

void SAVE_STATE(){
  uint8_t wr_data[8] = {0};
  for (int i = 0; i < 4; i++){
    wr_data[i] = (uint8_t) times[i];
  }
  wr_data[4] = (uint8_t) state;
  wr_data[5] = (uint8_t) level;
  wr_data[6] = (uint8_t) remain_time;
  eeprom_write(40, wr_data, 8);
}

void LOAD_STATE(){
  uint8_t re_data[8] = {0};
  eeprom_read(40, re_data, 8);
  if (re_data[0] != 255){
    for (int i = 0; i < 3; i++){
      times[i] = re_data[i];
    }
    state = re_data[4];
    level = re_data[5];
    remain_time = re_data[6];
    level_time =  times[level]; 
    total_time = remain_time;
    for (int i = level+1 ; i < 4; i++){
      total_time += times[i];
    }
    UPDATE();
  }
}

void eeprom_write(uint16_t memory_address, uint8_t* data, int _size) {
  Wire.beginTransmission(0b1010000);
  Wire.write((uint8_t)((memory_address & 0xFF00) >> 8));
  Wire.write((uint8_t)((memory_address & 0x00FF) >> 0));
  for (int i = 0; i < _size; i++) {
    Wire.write(data[i]);
  }
  Wire.endTransmission();
  delay(200);
}

void eeprom_read(uint16_t memory_address, uint8_t* data, int _size) {
  Wire.beginTransmission(0b1010000);
  Wire.write((uint8_t)((memory_address & 0xFF00) >> 8));
  Wire.write((uint8_t)((memory_address & 0x00FF) >> 0));
  Wire.endTransmission();
  Wire.requestFrom(0b1010000, _size);
  for (int i = 0; i < _size; i++) {
    data[i] = Wire.read();
  }
}
