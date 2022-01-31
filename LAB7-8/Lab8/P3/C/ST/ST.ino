#include <SPI.h>

#define MISO 50
#define MOSI 51
#define SCK 52
#define SS 53
int value;
volatile boolean isFinished = false;

void setup() {
  Serial.begin(9600);
  Serial.println("SLAVE Temperature...");

  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT_PULLUP);

  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

void loop() {
  if (isFinished) {
    Serial.print("Temprature: ");
    Serial.print(value);
    Serial.println(" C");
    isFinished = false;
  }
}

ISR (SPI_STC_vect)
{
  byte number = SPDR;
  value = (uint8_t)number;
  isFinished = true;
}
