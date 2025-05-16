#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup()
{
  lcd.init();
  lcd.backlight();
}

void loop()
{
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("line 1 ");        // print message at (0, 0)
  lcd.setCursor(0, 1);         // move cursor to   (0, 1)
  lcd.print("line 2");
  delay(2000);                 // display the above for two seconds
  Serial.print("RUNNING :P ");
  
}
