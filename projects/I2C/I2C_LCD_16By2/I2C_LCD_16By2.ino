#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x27(or 0x3F. Use I2C_Scanner for sure) for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup()
{
  lcd.init(); // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
}

void loop()
{
  lcd.print("Hello, world!");
}



