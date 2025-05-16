const int pressurePin1 = A1;
const int pressurePin2 = A2;

void setup() {
  Serial.begin(9600); // 9600 baud, for serial comms
}

void loop() {
  int pressureValue1 = analogRead(pressurePin1);
  int pressureValue2 = analogRead(pressurePin2);
  
  Serial.print("Pressure 1: ");
  Serial.println(pressureValue1);
  Serial.print("Pressure 2: ");
  Serial.println(pressureValue2);
  delay(500);
}
