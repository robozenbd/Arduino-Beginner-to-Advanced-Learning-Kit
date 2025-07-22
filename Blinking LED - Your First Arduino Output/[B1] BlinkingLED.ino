// Set the pin where the LED is connected
int ledPin = 13;  // LED is connected to digital pin 13

void setup() {
  // Set the LED pin as output so Arduino can control it
    pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn the LED on
    digitalWrite(ledPin, HIGH);
  delay(1000);  // Wait for 1 second (1000 milliseconds)

  // Turn the LED off
    digitalWrite(ledPin, LOW);
  delay(1000);  // Wait for 1 second again
}
