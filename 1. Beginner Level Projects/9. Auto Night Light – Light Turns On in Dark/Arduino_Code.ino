// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
int ldrPin = 2;       // LDR sensor connected to digital pin 2
int ledPin = 13;      // LED connected to pin 13

void setup() {
  pinMode(ldrPin, INPUT);      // Use normal input (not pull-up)
  pinMode(ledPin, OUTPUT);     // Set LED pin as output
}

void loop() {
  int lightState = digitalRead(ldrPin);  // Read the LDR sensor value

  // HIGH means it's light → turn ON LED
  if (lightState == HIGH) {
    digitalWrite(ledPin, HIGH);  // Turn ON LED in light
  } else {
    digitalWrite(ledPin, LOW);   // Turn OFF LED in dark
  }

  delay(100);  // Small delay to avoid flickering
}
