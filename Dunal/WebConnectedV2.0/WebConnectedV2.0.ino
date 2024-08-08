#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

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

    // Parse the JSON response
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print("Failed to parse JSON: ");
      Serial.println(error.f_str());
      return;
    }

    // Extract and print the required values from the JSON
    const char* time1 = doc["time1"];
    const char* time2 = doc["time2"];
    const char* time3 = doc["time3"];
    const char* topStr = doc["top"];
    const char* bottomStr = doc["bottom"];
    const char* pumpStatusStr = doc["pump_status"];

    int top = atoi(topStr);  // Convert to integer
    int bottom = atoi(bottomStr);  // Convert to integer
    int pumpStatus = atoi(pumpStatusStr);  // Convert to integer

    Serial.print("time1: ");
    Serial.println(time1);
    Serial.print("time2: ");
    Serial.println(time2);
    Serial.print("time3: ");
    Serial.println(time3);
    Serial.print("top: ");
    Serial.println(top);
    Serial.print("bottom: ");
    Serial.println(bottom);
    Serial.print("pump_status: ");
    Serial.println(pumpStatus);

    // Control LED based on pump status
    if (pumpStatus == 0) {
      digitalWrite(ledPin, LOW); // Turn LED off
    } else if (pumpStatus == 1) {
      digitalWrite(ledPin, HIGH); // Turn LED on
    }
  }

  delay(200); // Wait before the next request
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