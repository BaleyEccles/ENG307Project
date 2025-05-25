#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DEBUG_ENABLE

#ifdef DEBUG_ENABLE
void DEBUG_MESSAGE(String msg) {
  Serial.print(msg);  
}
#else
void DEBUG_MESSAGE(String msg) {}
#endif

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
  DEBUG_MESSAGE("BUTTON 1 PRESSED\n");
  switch(displayState)
    {
    case DISPLAY_1: {
      displayState = DISPLAY_2;
      DEBUG_MESSAGE("CHANGED TO DISPLAY STATE 2\n");
      break;
    }
    case DISPLAY_2: {
      DEBUG_MESSAGE("CHANGED TO DISPLAY STATE 3\n");
      displayState = DISPLAY_3;
      break;
    }
    case DISPLAY_3: {
      DEBUG_MESSAGE("CHANGED TO DISPLAY STATE 1\n");
      displayState = DISPLAY_1;
      break;
    }
    default: {
      DEBUG_MESSAGE("CHANGED TO DISPLAY STATE 1 + ERROR\n");
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
      DEBUG_MESSAGE("PWM = 0\n");
      break;
    }
    case 0: {
      PWMSpeed = 255;
      DEBUG_MESSAGE("PWM = 255\n");
      break;
    }
    default: {
      DEBUG_MESSAGE("PWM = 255 + ERROR\n");
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
      DEBUG_MESSAGE("MESSAGE DISPLAYED 1\n");
      break;
    }
    case DISPLAY_2: {
      displayMessage("Servo angle " + servoAngle, "Duty cycle " + String(100.0f*(float)PWMSpeed/255.0f));
      DEBUG_MESSAGE("MESSAGE DISPLAYED 2\n");
      break;
    }
    case DISPLAY_3: {
      displayMessage("Temperature " + String(temperature), ":)");
      DEBUG_MESSAGE("MESSAGE DISPLAYED 3\n");
      break;
    }
    default: {
      displayMessage("ERROR:", "THIS CODE SHOULD BE UNREACHABLE");
      DEBUG_MESSAGE("MESSAGE DISPLAYED ERROR\n");
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
  DEBUG_MESSAGE("SERVO CHANGED TO 0\n");
  } else {
    servoAngle = 90;
  DEBUG_MESSAGE("SERVO CHANGED TO 90\n");
  }
  delay(250);

  // Debug stuff
  DEBUG_MESSAGE("RUNNING\n");

}
