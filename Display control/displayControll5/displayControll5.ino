#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

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

// Create an instance of the RTC
RTC_DS3231 rtc;

void setup() {
  // Initialize the display with the SPI interface
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Loop forever if initialization fails
  }
  display.clearDisplay();
  display.setTextSize(2); // Set text size to 2
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.display();

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    while (1);
  }

  // Check if the RTC lost power and if so, set the time
  if (rtc.lostPower()) {
    Serial.println(F("RTC lost power, setting the time!"));
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Uncomment the following line to set the date & time manually
    // rtc.adjust(DateTime(2024, 6, 19, 15, 0, 0));
  }
}

void loop() {
  // Get the current time
  DateTime now = rtc.now();

  // Clear the display buffer
  display.clearDisplay();

  // Format the time as HH:MM:SS
  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  // Set cursor to the middle of the screen
  display.setCursor((SCREEN_WIDTH - 6 * 6) / 2, (SCREEN_HEIGHT - 16) / 2);

  // Print the time
  display.print(timeStr);

  // Update the display
  display.display();

  // Delay for a short period before updating the display again
  delay(1000);
}
