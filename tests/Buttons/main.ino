
#define buttonPin1 = 2;
#define buttonPin2 = 3;

void setup() {
  Serial.begin(9600); // 9600 baud, for serial comms
  
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  
  Serial.print("Button State 1: ");
  Serial.println(buttonState1);
  Serial.print("Button State 2: ");
  Serial.println(buttonState2);
  
  delay(500);
}
