// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
int relayPin = 8;          // Relay connected to digital pin 8
int buttonPin = 2;         // Push button connected to digital pin 2

int lastButtonState = HIGH; // Stores previous button state (starts HIGH because of INPUT_PULLUP)
bool relayState = false;    // Current relay state: false = OFF, true = ON

void setup() {
  pinMode(relayPin, OUTPUT);            // Set relay pin as output to control relay
  pinMode(buttonPin, INPUT_PULLUP);     // Set button pin as input with internal pull-up resistor
  digitalWrite(relayPin, HIGH);         // Start with relay OFF (relay is active LOW)
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // Read current button state

  // Check if button was just pressed (changed from HIGH to LOW)
    if (buttonState == LOW && lastButtonState == HIGH) {
    relayState = !relayState;                 // Toggle relay state (ON to OFF or OFF to ON)

    // Turn relay ON if relayState is true (LOW activates relay), otherwise turn OFF (HIGH)
    digitalWrite(relayPin, relayState ? LOW : HIGH);

    delay(200);                              // Short delay to debounce the button (avoid multiple toggles)
}

  lastButtonState = buttonState;             // Save current button state for next loop check
}