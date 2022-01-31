#include <Servo.h>

String temp = "";
Servo servo;
int val;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(2);
  val = 180;
  servo.writeMicroseconds(1500);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) {
    char digit = Serial.read();
    if (digit == 13){
      val -= temp.toInt();
      int x = map(val, 0, 360, 1000, 2000);
      Serial.print(val);
      servo.writeMicroseconds(x);
      temp = "";
    }else{
      temp += digit;
    }
  }
}
