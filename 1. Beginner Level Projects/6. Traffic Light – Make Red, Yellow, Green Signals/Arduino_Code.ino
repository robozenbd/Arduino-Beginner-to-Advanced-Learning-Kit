// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
int redLED = 2;     // Red LED connected to pin 2
int yellowLED = 3;  // Yellow LED connected to pin 3
int greenLED = 4;   // Green LED connected to pin 4

void setup() {
  // Set all LED pins as OUTPUT
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  // Turn ON Red LED for 5 seconds
  digitalWrite(redLED, HIGH);
  delay(5000);              // Wait for 5 seconds
  digitalWrite(redLED, LOW);

  // Turn ON Yellow LED for 3 seconds
  digitalWrite(yellowLED, HIGH);
  delay(3000);              // Wait for 3 seconds
  digitalWrite(yellowLED, LOW);

  // Turn ON Green LED for 8 seconds
  digitalWrite(greenLED, HIGH);
  delay(8000);              // Wait for 8 seconds
  digitalWrite(greenLED, LOW);
}