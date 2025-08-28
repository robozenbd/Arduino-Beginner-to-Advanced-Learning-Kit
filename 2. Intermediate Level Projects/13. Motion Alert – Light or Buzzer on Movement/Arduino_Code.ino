// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
const int pirPin = 2;        // PIR sensor output connected to pin 2
const int buzzerPin = 9;     // Buzzer connected to pin 9

void setup() {
  pinMode(pirPin, INPUT);        // Set sensor pin as input
  pinMode(buzzerPin, OUTPUT);    // Set buzzer pin as output

  digitalWrite(buzzerPin, LOW);  // Start with buzzer off
}

void loop() {
  int motion = digitalRead(pirPin);  // Read PIR sensor signal

  if (motion == HIGH) {
    digitalWrite(buzzerPin, HIGH);   // Motion detected → buzzer ON
  } 
  else {
    digitalWrite(buzzerPin, LOW);    // No motion → buzzer OFF
  }

  delay(100);  // Wait a little to avoid false triggers
}