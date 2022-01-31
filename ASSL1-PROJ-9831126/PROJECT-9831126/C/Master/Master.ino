#include <SPI.h>

#define SS0 47
#define SS1 46
#define SS2 45
#define SS3 44

int PINs[4] = {SS0, SS1, SS2, SS3};

char M[100];
int index = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 0; i < 4; i++){
    pinMode(PINs[i], OUTPUT);
    digitalWrite(PINs[i], HIGH);
  }
  SPI.begin();
}

void sendData(int i){
  digitalWrite(PINs[i], LOW);
  SPI.transfer(M[i]);
  digitalWrite(PINs[i], HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '-') {
      index = 0;
      for (int i = 0; i < 4; i++)
        sendData(i);
    }
    else {
      M[index] = c;
      index++;
    }
  }
}
