// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
int soundSensor = 2;       // Sound sensor connected to pin 2
int led = 13;              // LED connected to pin 13 (built-in LED)
int state = LOW;           // To track current LED state (ON or OFF)
int lastSound = LOW;       // To track previous sound state

void setup() {
  pinMode(soundSensor, INPUT);   // Set sound sensor pin as input
  pinMode(led, OUTPUT);          // Set LED pin as output
}

void loop() {
  int currentSound = digitalRead(soundSensor);  // Read current sound input

  // If sound just changed from LOW to HIGH (clap detected)
  if (currentSound == HIGH && lastSound == LOW) {
    state = !state;                   // Toggle LED state (ON → OFF or OFF → ON)
    digitalWrite(led, state);         // Update LED according to state
    delay(200);                       // Small delay to avoid multiple triggers (debouncing)
  }

  lastSound = currentSound;          // Store current state for next loop
}