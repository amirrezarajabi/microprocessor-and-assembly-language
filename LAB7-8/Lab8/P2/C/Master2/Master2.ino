#include <SPI.h>

#define MESSAGE0   "Amirreza\n"
#define MESSAGE1   "Hi Amirreza:)\n"

#define SS0 45
#define SS1 46

void setup() {
  Serial.begin(9600);
  Serial.println("MASTER...");

  pinMode(SS0, OUTPUT);
  digitalWrite(SS0, HIGH);

  pinMode(SS1, OUTPUT);
  digitalWrite(SS1, HIGH);
  
  SPI.begin();
}

void sender(const char *message) {
  for (const char *p = message ; char c = *p; p++) {
    SPI.transfer(c);
    Serial.print(c);
    delay(5);
  }
  Serial.println();
}

void loop() {
  digitalWrite(SS0, LOW);
  sender(MESSAGE0);
  digitalWrite(SS0, HIGH);
  delay(100);

  digitalWrite(SS1, LOW);
  sender(MESSAGE1);
  digitalWrite(SS1, HIGH);
  delay(100);
}
