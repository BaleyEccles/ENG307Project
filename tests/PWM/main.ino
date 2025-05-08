
#define PWMPin 5;

void setup() {
  pinMode(PWMPin, OUTPUT);
}

void loop() {

  for (int amount = 0; amount <= 255; amount++) {
    analogWrite(PWMPin, amount);
    delay(10);
  }
  
  for (int amount = 255; amount >= 0; amount--) {
    analogWrite(PWMPin, amount);
    delay(10);
  }
}
