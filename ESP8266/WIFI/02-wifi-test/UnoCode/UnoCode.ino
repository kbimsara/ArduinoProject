// Arduino Uno Code

const int ledPin = 13; // LED connected to digital pin 13

void setup() {
  Serial.begin(9600);   // Initialize serial communication
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      digitalWrite(ledPin, HIGH); // Turn the LED on
    } else if (command == '0') {
      digitalWrite(ledPin, LOW); // Turn the LED off
    }
  }
}
