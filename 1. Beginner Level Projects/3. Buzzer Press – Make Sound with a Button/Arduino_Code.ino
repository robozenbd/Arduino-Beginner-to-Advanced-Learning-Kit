// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
int buzzerPin = 9;       // Buzzer is connected to digital pin 9
int buttonPin = 2;       // Button is connected to digital pin 2

void setup() {
  // Set the pin modes
  pinMode(buzzerPin, OUTPUT);          // Set buzzer pin as OUTPUT (so we can turn it on/off)
  pinMode(buttonPin, INPUT_PULLUP);    // Set button pin as INPUT with internal pull-up resistor
}

void loop() {
  // Read the current state of the button
  int buttonState = digitalRead(buttonPin);  // LOW when pressed, HIGH when not pressed

  // Check if the button is pressed
  if (buttonState == LOW) {                // Button is pressed
    digitalWrite(buzzerPin, HIGH);         // Turn ON the buzzer
  } else {
    digitalWrite(buzzerPin, LOW);          // Turn OFF the buzzer
  }
}
