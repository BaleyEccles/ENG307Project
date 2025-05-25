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
const int servoPin = 6;

/*
// THINGS
*/

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int PWMSpeed = 255;
int servoAngle = 0;
float temperature = 0;
int pressureTop = 0;
int pressureBottom = 0;

enum displayState1 {
  DISPLAY_1, DISPLAY_2, DISPLAY_3
};

displayState1 displayState = DISPLAY_1;

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
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print(line1);    // print message at (0, 0)
  lcd.setCursor(0, 1); // move cursor to   (0, 1)
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

// returns 0 when pressed case 1 w:hen not pressed
int readButton1()
{
  return digitalRead(buttonPin1);
}

int readButton2()
{
  return digitalRead(buttonPin2);
}

// angle is in ragne 0-90
// 0    0% pinched
// 90 100% pinched
void setServoAngle(int angle)
{
  servo.write(angle);
}

/*
// Button Interrupts
*/

void buttonPressed1()
{
  switch(displayState)
    {
    case DISPLAY_1: {
      displayState = DISPLAY_2;
      break;
    }
    case DISPLAY_2: {
      displayState = DISPLAY_3;
      break;
    }
    case DISPLAY_3: {
      displayState = DISPLAY_1;
      break;
    }
    default: {
      displayState = DISPLAY_1;
      break;
    }
    }
}

void buttonPressed2()
{
  switch(PWMSpeed)
    {
    case 255: {
      PWMSpeed = 0;
      break;
    }
    case 0: {
      PWMSpeed = 255;
      break;
    }
    default: {
      PWMSpeed = 255;
      break;
    }
    }
}

/*
// MAIN FUNCTIONS
*/

void manageDisplay() {
  switch(displayState)
    {
    case DISPLAY_1: {
      displayMessage("Pressure top " + pressureTop, "Pressure bottom " + pressureBottom);
      break;
    }
    case DISPLAY_2: {
      displayMessage("Servo angle " + servoAngle, "Duty cycle " + String(100.0f*(float)PWMSpeed/255.0f));
      break;
    }
    case DISPLAY_3: {
      displayMessage("Temperature " + String(temperature), ":)");
      break;
    }
    default: {
      displayMessage("ERROR:", "THIS CODE SHOULD BE UNREACHABLE");
      break;
    }
    }
 
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
  servo.attach(servoPin);
  setServoAngle(90);

  // Interrupt on buttons
  attachInterrupt(digitalPinToInterrupt(buttonPin1), buttonPressed1, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPin2), buttonPressed2, FALLING);
}


/*
// MAIN LOOP
*/


void loop()
{
  
  pressureTop = readPressure1();
  pressureBottom = readPressure2();
  temperature = getTemperature();
  manageDisplay();
  PWM(PWMSpeed);
  setServoAngle(servoAngle);  

  
  if (pressureBottom > 20 || pressureTop > 20) {
    servoAngle = 0;
   } else {
    servoAngle = 90;
   }
  delay(250);   

  // Debug stuff
  Serial.print("RUNNING\n");

}
