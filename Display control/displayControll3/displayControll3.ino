#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Declaration for SSD1306 display connected using software SPI:
#define OLED_MOSI   9
#define OLED_CLK    10
#define OLED_DC     11
#define OLED_CS     12
#define OLED_RESET  13

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an instance of the display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  // Initialize the display with the SPI interface
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Loop forever if initialization fails
  }
  display.clearDisplay();
  display.setTextSize(1); // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0); // Start at top-left corner
  display.display();
}

void loop() {
  static int x = 0;
  static int y = 0;
  static int dx = 1;
  static int dy = 1;
  String text = "ARDUINO";

  // Clear the display buffer
  display.clearDisplay();

  // Set cursor to current position
  display.setCursor(x, y);
  
  // Print the text
  display.print(text);

  // Update the display with the new position
  display.display();

  // Update the position for the next frame
  x += dx;
  y += dy;

  // Calculate the width of the text
  int16_t textWidth = text.length() * 6; // Assuming each character is 6 pixels wide for text size 1
  int16_t textHeight = 8; // Assuming the height of the text is 8 pixels for text size 1

  // Bounce the text off the edges of the display
  if (x < 0 || x + textWidth > SCREEN_WIDTH) {
    dx = -dx;
  }
  if (y < 0 || y + textHeight > SCREEN_HEIGHT) {
    dy = -dy;
  }

  // Delay to control the speed of the animation
  delay(25);
}
