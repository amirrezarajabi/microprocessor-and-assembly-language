#include <SPI.h>

#define SST 45
#define SSL 46
#define TP A8
#define LP A1
int LPV;
uint8_t mLPV;
int TPV;
uint8_t mTPV;


void setup() {
  Serial.begin(9600);
  Serial.println("MASTER...");

  pinMode(SST, OUTPUT);
  digitalWrite(SST, HIGH);
  pinMode(SSL, OUTPUT);
  digitalWrite(SSL, HIGH);
  pinMode(TP, INPUT);
  pinMode(LP, INPUT);
  SPI.begin();
}

void loop() {
  delay(1000);
  LPV = analogRead(LP);
  mLPV = LPV;
  digitalWrite(SSL, LOW);
  SPI.transfer (mLPV);
  Serial.print("Light: ");
  Serial.print(mLPV);
  Serial.println("%");
  delay(5);
  digitalWrite(SSL, HIGH);
  delay(1000);
  TPV = analogRead(TP);
  mTPV = map(TPV, 0, 1023, 0, 500);
  digitalWrite(SST, LOW);
  SPI.transfer (mTPV);
  Serial.print("Temp: ");
  Serial.print(mTPV);
  Serial.println(" C");
  delay(5);
  digitalWrite(SST, HIGH);
  Serial.println();
}
