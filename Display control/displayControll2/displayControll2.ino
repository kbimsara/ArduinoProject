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
  // The message to display
  const char* message = "Animating Text";

  // Display each letter one by one
  for (int i = 0; i < strlen(message); i++) {
    display.clearDisplay(); // Clear the display buffer

    // Display the partial message
    display.setCursor(0, 10); // Adjust the vertical position as needed
    for (int j = 0; j <= i; j++) {
      display.print(message[j]);
    }

    display.display(); // Update the display
    delay(200); // Delay to control the speed of the animation
  }

  // Pause before restarting the animation
  delay(1000);
}
