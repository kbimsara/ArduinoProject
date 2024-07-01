int enA = 5;
int in1 = 3;
int in2 = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(1);
  // pinMode(13, OUTPUT);
  // pinMode(12, OUTPUT);
  // pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void moveClockwise(int spd) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, spd);
}

void loop() {
  // put your main code here, to run repeatedly:
  char controlSignal;
  while (!Serial.available())
    ;

  controlSignal = Serial.read();
  if (controlSignal == '0') moveClockwise(0);
  if (controlSignal == '1') moveClockwise(60);
  if (controlSignal == '2') moveClockwise(80);
  if (controlSignal == '3') moveClockwise(125);
  if (controlSignal == '4') moveClockwise(170);
  if (controlSignal == '5') moveClockwise(225);
}
