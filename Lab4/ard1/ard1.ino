#include <Servo.h>

Servo servo;
int turn;
int ind;

void setup() {
  // put your setup code here, to run once:
  servo.attach(2);
  servo.writeMicroseconds(1500);
  turn = 1500;
  ind = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.writeMicroseconds(turn);
  update();
  delay(50);
}

void update(){
  turn += ind * 10;
  if (turn >= 2000){
    ind = -1;
    turn = 2000;
  }else if (turn <= 1500){
    ind = 1;
    turn = 1500;
  }
}
