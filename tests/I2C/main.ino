#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Either 0x27 or 0x3F
const int LCD_ADDR = 0x27;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setup() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Test Message");
}

void loop() {

}
