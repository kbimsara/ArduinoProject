#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// OLED display pins
#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const int enA = 5;
const int in1 = 3;
const int in2 = 2;
const int ledPin = 13;
const int rate[6] = {0, 60, 80, 125, 170, 225};
const int TEMP_SENSOR_PIN = A0;
const float VOLTAGE_REFERENCE = 5.0;
const int ADC_MAX = 1023;

int oldSpeed = 0;
int newSpeed = 0;
float temperature = 0;
String speedType = "";
String incomingData = "";
String ip = "Disconnected";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_RESET)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.display();
}

void loop() {
  showIPText(ip);

  if (Serial.available() > 0) {
    incomingData = Serial.readStringUntil('\n');
    processIncomingData(incomingData);
  }

  showTemperature();
  showSpeed(newSpeed);
}

void processIncomingData(String data) {
  if (data.startsWith("IP:")) {
    ip = data.substring(4);
  } else {
    char received = data.charAt(0);
    switch (received) {
      case '0': newSpeed = 0; break;
      case '1': newSpeed = 1; break;
      case '2': newSpeed = 2; break;
      case '3': newSpeed = 3; break;
      case '4': newSpeed = 4; break;
      case '5': newSpeed = 5; break;
    }

    if (newSpeed != oldSpeed) {
      oldSpeed = newSpeed;
      moveMotorClockwise(newSpeed);
    }
  }
}

void moveMotorClockwise(int speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, rate[speed]);
}

void showTemperature() {
  temperature = readTemperature();
  display.fillRect(0, 0, SCREEN_WIDTH, 16, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(2, 4);
  display.println("Temperature: " + String(temperature) + "C");
  display.display();
}

float readTemperature() {
  int sensorValue = analogRead(TEMP_SENSOR_PIN);
  float voltage = sensorValue * (VOLTAGE_REFERENCE / ADC_MAX);
  return voltage * 100;
}

void showIPText(String ip) {
  display.fillRect(0, 17, SCREEN_WIDTH, 13, BLACK);
  display.setTextColor(WHITE);
  display.setCursor(2, 17);
  display.println("IP : " + ip);
  display.display();
}

void showSpeed(int speed) {
  display.fillRect(0, 30, SCREEN_WIDTH, 10, BLACK);
  display.setTextColor(WHITE);
  display.setCursor(2, 30);

  if (speed > 0) {  // xpos, ypos
    if (speed > oldSpeed) {
      speedType = "Increased";
      delay(300);
    } else if (oldSpeed == speed) {
      speedType = "Stabled";
      delay(300);
    } else {
      speedType = "Decreasing";
      delay(300);
    }
  } else {
    speedType = "Off";
  }

  display.println("State : " + speedType);
  display.display();

  int progress = speed * 20;
  displayProgressBar(progress);
}

void displayProgressBar(int progress) {
  display.fillRect(0, 40, SCREEN_WIDTH, SCREEN_HEIGHT - 33, BLACK);
  int barWidth = SCREEN_WIDTH - 4;
  int barHeight = 10;
  int xPos = 2;
  int yPos = ((SCREEN_HEIGHT - barHeight) / 2 + 16) + 1;

  display.drawRect(xPos - 1, yPos - 1, barWidth + 2, barHeight + 2, SSD1306_WHITE);
  int filledWidth = map(progress, 0, 100, 0, barWidth);
  display.fillRect(xPos, yPos, filledWidth, barHeight, SSD1306_WHITE);

  String progressText = "Speed: " + String(progress) + "%";
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(progressText, 0, yPos + barHeight + 2, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, yPos + barHeight + 2);
  display.print(progressText);

  display.display();
}
