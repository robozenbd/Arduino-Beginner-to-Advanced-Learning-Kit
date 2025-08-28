// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
int buzzerPin = 9;  // Buzzer connected to pin 9

void setup() {
  // No setup needed
}

void loop() {
  tone(buzzerPin, 500);    // Play 500 Hz tone (Melody 1)
  delay(1000);             // Wait 1 second

  tone(buzzerPin, 750);    // Play 750 Hz tone (Melody 2)
  delay(1000);             // Wait 1 second

  tone(buzzerPin, 1000);   // Play 1000 Hz tone (Melody 3)
  delay(1000);             // Wait 1 second

  tone(buzzerPin, 1250);   // Play 1250 Hz tone (Melody 4)
  delay(1000);             // Wait 1 second

  tone(buzzerPin, 1500);   // Play 1500 Hz tone (Melody 5)
  delay(1000);             // Wait 1 second

  noTone(buzzerPin);       // Stop playing tone
  delay(1000);             // Wait 1 second before repeating
}