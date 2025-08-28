// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
int flameSensor = 2;    // Flame sensor connected to pin 2
int buzzer = 9;         // Buzzer connected to pin 9

void setup() {
  pinMode(flameSensor, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(buzzer, OUTPUT);             // Set buzzer as output
}

void loop() {
  int flameDetected = digitalRead(flameSensor);  // Read sensor value

  // LOW = Flame detected, HIGH = No flame
  if (flameDetected == LOW) {
    digitalWrite(buzzer, HIGH);  // Flame detected → buzzer ON
  } else {
    digitalWrite(buzzer, LOW);   // No flame → buzzer OFF
}
}