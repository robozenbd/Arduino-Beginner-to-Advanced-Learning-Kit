// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers using variables
int ledPin = 13;  // Declare a variable for LED pin

void setup() {
  pinMode(ledPin, OUTPUT);  // Set the LED pin as OUTPUT
}

void loop() {
  digitalWrite(ledPin, HIGH); // Turn ON the LED
  delay(1000);                // Wait for 1 second

  digitalWrite(ledPin, LOW);  // Turn OFF the LED
  delay(1000);                // Wait for 1 second
}