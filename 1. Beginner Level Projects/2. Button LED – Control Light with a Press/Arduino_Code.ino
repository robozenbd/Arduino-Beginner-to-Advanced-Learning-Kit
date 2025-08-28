// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers using variables
int ledPin = 13;       // LED is connected to digital pin 13
int buttonPin = 2;     // Push button is connected to digital pin 2

void setup() {
  // Set pin modes
  pinMode(ledPin, OUTPUT);         // Set LED pin as OUTPUT
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as INPUT with internal pull-up resistor
}

void loop() {
  // Read the current state of the button
  int buttonState = digitalRead(buttonPin);  // Will be LOW when button is pressed

  // Check if button is pressed
  if (buttonState == LOW) {           // If button is pressed (LOW)
    digitalWrite(ledPin, HIGH);       // Turn ON the LED
  } else {
    digitalWrite(ledPin, LOW);        // Otherwise, turn OFF the LED
  }
}
