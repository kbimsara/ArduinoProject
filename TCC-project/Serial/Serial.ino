void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(1);
  // pinMode(13, OUTPUT);
  // pinMode(12, OUTPUT);
  // pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  char controlSignal;
  while (!Serial.available());

  controlSignal = Serial.read();
  if(controlSignal == '1') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(controlSignal == '2') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(controlSignal == '3') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(controlSignal == '4') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(controlSignal == '5') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
