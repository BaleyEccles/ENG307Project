#include <Wire.h>
#include <LiquidCrystal_I2C.h>


const int pressurePin1 = A1;
const int pressurePin2 = A2;
const int PWMPin = 5;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  pinMode(PWMPin, OUTPUT);
}

void loop()
{
  int pressureValue1 = analogRead(pressurePin1);
  int pressureValue2 = analogRead(pressurePin2);
  String p1 = String(pressureValue1);
  String p2 = String(pressureValue2);
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("p1 " + p1);        // print message at (0, 0)
  lcd.setCursor(0, 1);         // move cursor to   (0, 1)
  lcd.print("p2 " + p2);
  delay(250);                 // display the above for two seconds
  Serial.print("RUNNING :P ");
  analogWrite(PWMPin, 255);
}
