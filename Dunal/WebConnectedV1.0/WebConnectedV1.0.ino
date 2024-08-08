#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "SLT_FIBRE";        // Replace with your network SSID
const char* password = "Dunal   258";  // Replace with your network password

const char* serverUrl = "https://dunal.kbxwebx-test.top/dataHandler.php";  // Your URL
const int ledPin = 2;                                                      // GPIO pin where the LED is connected

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  // Send GET request and process response
  String response = sendRequest();
  if (response.length() > 0) {
    Serial.println("Response from server: " + response);

    // Control LED based on server response
    // if (response.indexOf("ON") >= 0) {
    //     digitalWrite(ledPin, HIGH); // Turn LED on
    // } else if (response.indexOf("OFF") >= 0) {
    //     digitalWrite(ledPin, LOW); // Turn LED off
    // }
    digitalWrite(ledPin, LOW);

    // If the received data is LED_is_off, we set LOW the LED pin
    if (response == "LED_is_off") {
      digitalWrite(ledPin, HIGH);
    }
    // If the received data is LED_is_on, we set HIGH the LED pin
    else if (response == "LED_is_on") {
      digitalWrite(ledPin, LOW);
    }
  }

  // delay(200); // Wait for before next request
}

String sendRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();  // Disable SSL/TLS certificate verification

    HTTPClient http;
    http.begin(client, serverUrl);  // Specify the URL

    int httpResponseCode = http.GET();  // Send the request

    String payload = "";
    if (httpResponseCode > 0) {
      payload = http.getString();        // Get the response
      Serial.println(httpResponseCode);  // Print HTTP return code
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }
    http.end();      // Free resources
    return payload;  // Return the response
  }
  return "";  // Return empty string if not connected
}