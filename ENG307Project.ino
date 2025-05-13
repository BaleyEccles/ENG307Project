#include <Arduino.h>

unsigned char i = 0;

void setup()
{
  pinMode(3,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(3,HIGH);
  delay(500);
  digitalWrite(3,LOW);
  delay(500);
  Serial.println(i++);
}
