#define Pin 52

void setup() {
  // put your setup code here, to run once:
  pinMode(Pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  changePin();
}

void changePin(){
  digitalWrite(Pin, HIGH);
  delay(1000);
  digitalWrite(Pin, LOW);
  delay(1000);
}
