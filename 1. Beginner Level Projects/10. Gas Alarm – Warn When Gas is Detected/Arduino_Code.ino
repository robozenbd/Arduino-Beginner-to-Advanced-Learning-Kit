// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
int gasSensor = 2;     // Gas sensor connected to digital pin 2
int buzzer = 9;        // Buzzer connected to digital pin 9

void setup() {
  pinMode(gasSensor, INPUT_PULLUP);   // Enable internal pull-up resistor
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int gasDetected = digitalRead(gasSensor);

  // With pull-up: LOW means sensor active (gas detected)
  if (gasDetected == LOW) {
    digitalWrite(buzzer, HIGH);    // Turn buzzer ON
  } else {
    digitalWrite(buzzer, LOW);     // Turn buzzer OFF
  }

  delay(100);
}
