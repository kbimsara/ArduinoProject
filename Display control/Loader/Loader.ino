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
  static int progress = 0;

  // Clear the display buffer
  display.clearDisplay();

  // Calculate progress bar dimensions
  int barWidth = SCREEN_WIDTH - 4;
  int barHeight = 10;
  int xPos = 2;
  int yPos = (SCREEN_HEIGHT - barHeight) / 2;

  // Draw the outline of the progress bar
  display.drawRect(xPos - 1, yPos - 1, barWidth + 2, barHeight + 2, SSD1306_WHITE);

  // Calculate the filled bar width based on progress
  int filledWidth = map(progress, 0, 100, 0, barWidth);
  display.fillRect(xPos, yPos, filledWidth, barHeight, SSD1306_WHITE);

  // Print the percentage text
  display.setCursor((SCREEN_WIDTH - 6 * 3) / 2, yPos + barHeight + 4); // Center horizontally
  display.print(progress);
  display.print("%");

  // Update the display with the new content
  display.display();

  // Increment progress (for demonstration, replace with actual loading logic)
  progress++;
  if (progress > 100) {
    progress = 0; // Reset progress
    delay(1000); // Delay before restarting
  }

  // Delay to control the speed of the animation
  delay(100); // Adjust this delay to control animation speed
}
