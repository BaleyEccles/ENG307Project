
#define temperaturePin = A3;

void setup() {
  Serial.begin(9600); // 9600 baud, for serial comms
}

void loop() {
  int temperatureValue = analogRead(temperaturePin);
  
  Serial.print("Value: ");
  Serial.println(temperatureValue);
  delay(500);
}
