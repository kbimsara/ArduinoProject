#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int old_speed = 0;
int new_speed = 0;
float temp = 0;
String speadType = "";
String incomingData = "";

//motor output
int enA = 5;
int in1 = 3;
int in2 = 2;
int rate[6] = { 0, 60, 80, 125, 170, 225 };

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.display();
}

void moveClockwise(int spd) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, spd);
}

void loop() {

  if (Serial.available() > 0) {
    char received = Serial.read();  //data from python file

    switch (received) {
      case '0':
        new_speed = 0;
        break;
      case '1':
        new_speed = 1;
        break;
      case '2':
        new_speed = 2;
        break;
      case '3':
        new_speed = 3;
        break;
      case '4':
        new_speed = 4;
        break;
      case '5':
        new_speed = 5;
        break;
    }
    if (new_speed != old_speed) {
      showText(new_speed);
      // delay(500);
    }
  }

  moveClockwise(rate[new_speed]);
  
  showTempText();
  showText(new_speed);
}

void showTempText() {
  getTemp();
  display.fillRect(0, 0, SCREEN_WIDTH, 16, WHITE);  // Draw a white rectangle as the yellow line equivalent
  display.setTextColor(BLACK);                      // Draw black text on white background
  display.setCursor(2, 4);                          // xpos, ypos
  display.println("Temperature: " + String(temp) + "`C");
  display.display();  // must run this method to display
}

//get temp using temp sensor
void getTemp() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  temp = voltage * 100;
}

void showText(int speed) {
  display.fillRect(0, 17, SCREEN_WIDTH, 16, BLACK);  // Draw a black rectangle to clear the previous text area
  display.setTextColor(WHITE);                       // Draw white text
  display.setCursor(2, 17);

  if (new_speed > 0) {  // xpos, ypos
    if (new_speed > old_speed) {
      speadType = "Increased";
      old_speed = new_speed;
      // delay(500);
    } else if (old_speed == new_speed) {  // Use '==' for comparison
      delay(500);
      speadType = "stabled";
    } else {
      speadType = "Decreasing";
      old_speed = new_speed;
    }
  } else {
    speadType = "Off";
  }
  // The following condition is always true, so it can be removed
  display.println("State : " + speadType);
  display.display();  // must run this method to display

  int sp = speed * 20;
  loader(sp);
}


void loader(int progress) {
  // Clear the display buffer except for the temperature and speed sections
  display.fillRect(0, 33, SCREEN_WIDTH, SCREEN_HEIGHT - 33, BLACK);

  // Calculate progress bar dimensions
  int barWidth = SCREEN_WIDTH - 4;
  int barHeight = 10;
  int xPos = 2;
  int yPos = ((SCREEN_HEIGHT - barHeight) / 2 + 16) - 7;  // Adjusted to fit below the speed section and move up by 7 pixels

  // Draw the outline of the progress bar
  display.drawRect(xPos - 1, yPos - 1, barWidth + 2, barHeight + 2, SSD1306_WHITE);

  // Calculate the filled bar width based on progress
  int filledWidth = map(progress, 0, 100, 0, barWidth);
  display.fillRect(xPos, yPos, filledWidth, barHeight, SSD1306_WHITE);

  // Print the percentage text centered
  String progressText = "Speed: " + String(progress) + "%";
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(progressText, 0, yPos + barHeight + 2, &x1, &y1, &w, &h);  // Adjusted text position by moving up 7 pixels
  display.setCursor((SCREEN_WIDTH - w) / 2, yPos + barHeight + 2);                 // Center horizontally and move up by 7 pixels
  display.print(progressText);

  // Update the display with the new content
  display.display();
}