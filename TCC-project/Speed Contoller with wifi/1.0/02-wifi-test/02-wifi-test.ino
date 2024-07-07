
#include <ESP8266WiFi.h>

const char* ssid = "HUNTER";
const char* password = "0724229199";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);  // Initialize serial communication with Arduino
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP: ");
  String ip = WiFi.localIP().toString();
  Serial.println(ip);
  server.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client Connected");
    while (client.connected()) {
      if (client.available()) {
        char command = client.read();
        Serial.write(command);  // Send command to Arduino
        client.print("Command received: ");
        client.println(command);
      }
      digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED on
    }
    client.stop();
    Serial.println("Client Disconnected");
  }
}
