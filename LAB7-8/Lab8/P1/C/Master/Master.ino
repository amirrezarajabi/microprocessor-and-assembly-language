#include <SPI.h>

#define MESSAGE   "AMIRREZA: 9831126:)\n"

#define SS 46

void setup() {
  Serial.begin(9600);
  Serial.println("MASTER...");
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
  SPI.begin();
}

void loop() {
  digitalWrite(SS, LOW);
  delay(10);

  for (const char *p = MESSAGE ; char c = *p; p++) {
    SPI.transfer(c);
    Serial.print(c);
    delay(5);
  }
  Serial.println();

  digitalWrite(SS, HIGH);

  delay(1000);
}
