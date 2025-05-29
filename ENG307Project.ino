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
  DEBUG_MESSAGE("SET PWM TO " + (String)value + "\n");
  analogWrite(PWMPin, value);
}

void displayMessage(String line1, String line2)
{
  DEBUG_MESSAGE("DISPLAY MESSAGE \"" + line1 + "\" ON LINE 1\n");
  DEBUG_MESSAGE("DISPLAY MESSAGE \"" + line2 + "\" ON LINE 2\n");
  lcd.clear();         // clear display
  lcd.setCursor(0, 0); // move cursor to   (0, 0)
  lcd.print(line1);    // print message at (0, 0)
  lcd.setCursor(0, 1); // move cursor to   (0, 1)
  lcd.print(line2);
}

int readPressureTop()
{
  int pressure1 = analogRead(pressurePin1);
  DEBUG_MESSAGE("READ PRESSURE TOP: " + (String)pressure1 + "\n");
  return pressure1;
}

int readPressureBottom()
{
  int pressure2 = analogRead(pressurePin2);
  DEBUG_MESSAGE("READ PRESSURE BOTTOM: " + (String)pressure2 + "\n");
  return pressure2;
}

int getTemperature()
{
  
  const float Vmax = 5.0f;
  const float R1 = 68e3;

  const float R2min = 30e3;
  const float R2max = 150e3;
  
  int pinValue = analogRead(temperaturePin);
  float pinVoltage = ((float)pinValue/1023.0f)*Vmax;
  float R2 = R1 * (Vmax / pinVoltage - 1);
  float temperature = 30.0 - (30.0 - 5.0) * (R2 - R2min) / (R2max - R2min);

  DEBUG_MESSAGE("READ TEMPERATURE: " + (String)temperature + "\n");
  return temperature;
}

// returns 0 when pressed case 1 w:hen not pressed
int readButton1()
{
  int button1 = digitalRead(buttonPin1);
  DEBUG_MESSAGE("READ BUTTON 1: " + (String)button1 + "\n");
  return button1;
}

int readButton2()
{
  int button2 = digitalRead(buttonPin2);
  DEBUG_MESSAGE("READ BUTTON 2: " + (String)button2 + "\n");
  return button2;
}

// angle is in ragne 0-90
// 0    0% pinched
// 90 100% pinched
void setServoAngle(int angle)
{
  DEBUG_MESSAGE("SET SERVO ANGLE TO: " + (String)angle + "\n");
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
  
  pressureTop = readPressureTop();
  pressureBottom = readPressureBottom();
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
