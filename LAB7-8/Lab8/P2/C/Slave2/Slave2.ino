#include <SPI.h>

#define MISO 50
#define MOSI 51
#define SCK 52
#define SS 53

volatile int ind = 0;
volatile bool isFinished = false;
char MESSAGE[100];

void setup() {
  Serial.begin(9600);
  Serial.println("SLAVE...");

  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT_PULLUP);

  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

void loop() {
  if (isFinished) {
    Serial.println(MESSAGE);
    ind = 0;
    isFinished = false;
  }
}

ISR (SPI_STC_vect)
{
  byte c = SPDR;
  if (ind < sizeof MESSAGE) {
    MESSAGE[ind++] = c;

    if (c == '\n') {
      isFinished = true;
    }
  }
}
