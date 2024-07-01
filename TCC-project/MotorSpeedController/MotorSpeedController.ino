
// int enA=5;
int in1=2;
int in2=3;

void setup() {
  // Motor A
  // pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}
void moveClockwise(int spd){
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  // analogWrite(enA, spd);
}

void loop() {
  moveClockwise(200);
  delay(1000);
}

