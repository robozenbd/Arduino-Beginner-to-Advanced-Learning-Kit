// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers

int ledPins[] = {2, 3, 4, 5, 6}; // Store LED pin numbers in an array
int delayTime = 100;             // Wait time between turning LEDs on/off (in milliseconds)

void setup() {
  // Set all pins in the ledPins array as OUTPUT pins
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Turn LEDs on one by one from left to right
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);  // Switch ON the current LED
    delay(delayTime);                 // Wait for a short time
    digitalWrite(ledPins[i], LOW);   // Switch OFF the current LED
  }

  // Turn LEDs on one by one from right to left (except the last one)
  for (int i = 3; i > 0; i--) {
    digitalWrite(ledPins[i], HIGH);  // Switch ON the current LED
    delay(delayTime);                 // Wait for a short time
    digitalWrite(ledPins[i], LOW);   // Switch OFF the current LED
}
}