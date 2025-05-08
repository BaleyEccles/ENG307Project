#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Either 0x27 or 0x3F
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Test Message");
}

void loop() {

}
