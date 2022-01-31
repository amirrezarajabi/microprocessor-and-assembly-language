#define btnPin0 19
#define btnPin1 20
#define btnPin2 21
#define ledPin0 0
#define ledPin1 1
#define ledPin2 2
#define ledPin3 3
#define ledPin4 4
#define ledPin5 5
#define ledPin6 6
volatile byte bP0 = 0;
volatile byte bP1 = 0;
volatile byte bP2 = 0;

void setup() {
  // put your setup code here, to run once:
  //Inputs
  pinMode(btnPin0, INPUT);
  pinMode(btnPin1, INPUT);
  pinMode(btnPin2, INPUT);
  //Outputs
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(btnPin0), isr0, FALLING);
  attachInterrupt(digitalPinToInterrupt(btnPin1), isr1, FALLING);
  attachInterrupt(digitalPinToInterrupt(btnPin2), isr2, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(bP0 == 1){
    digitalWrite(ledPin0, HIGH);
    delay(200);
    digitalWrite(ledPin1, HIGH);
    delay(200);
    digitalWrite(ledPin2, HIGH);
    delay(200);
    digitalWrite(ledPin3, HIGH);
    delay(200);
    digitalWrite(ledPin4, HIGH);
    delay(200);
    digitalWrite(ledPin5, HIGH);
    delay(200);
    digitalWrite(ledPin6, HIGH);
    bP0 = 0;
  }
  else if(bP1 == 1){
    int i = 0;
    while(i < strlen("amirreza")){
      pulse();
      i++;
    }
    state(HIGH);
    bP1 = 0;
  }
  else if(bP2 == 1){
    state(LOW);
    bP2 = 0;
  }
}
void isr0(){
  bP0 = 1;
}
void isr1(){
  bP1 = 1;
}
void isr2(){  
  bP2 = 1;
}
void state(int o){
  digitalWrite(ledPin0, o);
  digitalWrite(ledPin1, o);
  digitalWrite(ledPin2, o);
  digitalWrite(ledPin3, o);
  digitalWrite(ledPin4, o);
  digitalWrite(ledPin5, o);
  digitalWrite(ledPin6, o);
}
void pulse(){
  state(HIGH);
  delay(200);
  state(LOW);
  delay(200);
}
