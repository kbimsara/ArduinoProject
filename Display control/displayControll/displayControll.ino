#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       // download the Adafruit GFX library
#include <Adafruit_SSD1306.h>   // download the Adafruit SSD1306 library

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Comment out above, uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup()
{
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void loop()
{
  display.clearDisplay();
 
  showText();

  showDots();

  showLine();

  showRectangle();

  showFilledRectangle();

  showCircle();

  showFilledCircle();

  showTriangle();

  showBitMap();

  showScrolling();
  delay(2000);
}


void showText()
{
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.clearDisplay();
  display.setCursor(3,3); // xpos, ypos
  display.println("Hello world, begin.!");
  display.display();  // must run this method to display
  // delay(2000);
}

void showDots()
{
  display.drawPixel(10, 15, WHITE);
  display.drawPixel(20, 15, WHITE);
  display.drawPixel(30, 15, WHITE);
  display.display();
  // delay(2000);
}

void showLine()
{
  // syntax: x1,y1, x2,y2, WHITE or BLACK
  display.drawLine(0,0,display.width()-1,0,WHITE);
  display.display();  
  delay(1000);
  display.drawLine(display.width()-1,0,display.width()-1,display.height()-1,WHITE);
  display.display();
  delay(1000);
  display.drawLine(0,display.height()-1,display.width()-1,display.height()-1,WHITE);
  display.display();
  delay(1000);
  display.drawLine(0,0,0,display.height()-1,WHITE);
  display.display();
  delay(2000);
}

void showRectangle()
{
  // syntax: x_start, y_start, width, height, color
  display.drawRect(5, 28, 10, 10, WHITE);
  display.display();
  delay(2000);
}

void showFilledRectangle()
{
  // syntax: x_start, y_start, width, height, color
  display.fillRect(25,28,20,10,WHITE);
  display.display();
  // delay(2000);
}

void showCircle()
{
  // syntax: x_start, y_start, radius, color
  display.drawCircle(65, 28, 10, WHITE);
  display.display();
  // delay(2000);
}

void showFilledCircle()
{
  // syntax: x_start, y_start, radius, color
  display.fillCircle(95,28,10,WHITE);
  display.display();
  // delay(2000);
}

void showTriangle()
{
  // syntax: x1, y1, x2, y2, x3, y3, color
  display.drawTriangle(110,40, 115,20, 120,40, WHITE);
  display.display();
  delay(2000);
}

void showBitMap(void) {
  int y=40;
  for (int x=20;x<130;x++)
  {
    display.drawBitmap(x,y,logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, WHITE);
    display.display();    
    delay(10);
    display.drawBitmap(x,y,logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, BLACK);
  }
  // delay(2000);
}

void showScrolling()
{
  display.setTextSize(2);  // double text size
  for (int x=3;x<124;x++)
  {
    // display bitmap
    display.setTextColor(WHITE);
    display.setCursor(x,49);
    display.print("scroll");
    display.display();
    delay(10);
    // hide bitmap
    display.setTextColor(BLACK);
    display.setCursor(x,49);
    display.print("scroll");
  }
  // delay(2000);

}