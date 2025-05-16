#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo myservo;  // create servo object to control a servo

// twelve servo objects can be created on most boards
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

int pos = 0;    // variable to store the servo position
void setup() {
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop() {

  for (int i = 0; i < 1; i++) {
    myservo.write(i);              // tell servo to go to position in variable 'pos'

    lcd.clear();                 // clear display
    lcd.setCursor(0, 0);         // move cursor to   (0, 0)
    String val = String(i);
    lcd.print("pos " + val);        // print message at (0, 0
    delay(100);                       // waits 15ms for the servo to reach the position
  }

    

  //Serial.print("RUNNING :P ");
}
