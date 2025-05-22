#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
// PIN DEFINITIONS
*/

const int pressurePin1 = A1;
const int pressurePin2 = A2;
const int temperaturePin = A3;
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int PWMPin = 5;

/*
// THINGS
*/

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

/*
// ABSTRACTIONS
*/

// Value between 0-255
void PWM(int value)
{
  analogWrite(PWMPin, value);
}

void displayMessage(String line1, String line2)
{
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print(line1);        // print message at (0, 0)
  lcd.setCursor(0, 1);         // move cursor to   (0, 1)
  lcd.print(line2);
}

int readPressure1()
{
  return analogRead(pressurePin1);
}

int readPressure2()
{
  return analogRead(pressurePin2);
}

int getTemperature()
{
  // TODO: Need to convert to actual temperature, instead of voltage
  return analogRead(temperaturePin);
}

// returns 0 when pressed, 1 when not pressed
int readButton1()
{
  return digitalRead(buttonPin1);
}

int readButton2()
{
  return digitalRead(buttonPin2);
}

// angle is in ragne 0-360
void setServoAngle(int angle)
{
  myServo.write(angle);
}

/*
// SETUP
*/

void setup()
{
  // Serial communications
  Serial.begin(9600);

  // LCD
  lcd.init();
  lcd.backlight();

  // PWM
  pinMode(PWMPin, OUTPUT);

  // Buttons
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  // Servo
  myServo.attach(6);
}

/*
// MAIN LOOP
*/

void loop()
{

  String p1 = String(readPressure1());
  String p2 = String(readPressure2());

  displayMessage("p1 " + p1, "p2 " + p2);
  
  delay(250);
  Serial.print("RUNNING");

  // PWM
  PWM(255);
}
