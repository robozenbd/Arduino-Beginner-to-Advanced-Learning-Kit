// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
const int trigPin = 9;     // Connect the Trig pin of the ultrasonic sensor to pin 9
const int echoPin = 10;    // Connect the Echo pin of the ultrasonic sensor to pin 10
const int ledPin = 13;      // Connect an LED to pin 7

void setup() {
  pinMode(trigPin, OUTPUT);   // Set the trigPin as OUTPUT (we will send signal from it)
  pinMode(echoPin, INPUT);    // Set the echoPin as INPUT (it will receive the signal)
  pinMode(ledPin, OUTPUT);    // Set the ledPin as OUTPUT (to turn LED on or off)
  Serial.begin(9600);         // Start the Serial Monitor to show distance
}

void loop() {
  // Send a short pulse from trigPin to start measuring distance
  digitalWrite(trigPin, LOW);          // Make sure trigPin is LOW
  delayMicroseconds(2);                // Wait for 2 microseconds
  digitalWrite(trigPin, HIGH);         // Send HIGH pulse for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);          // Turn trigPin LOW again

  // Measure the time it takes for the echo to return
  long duration = pulseIn(echoPin, HIGH);  // Time for the sound to bounce back

  // Convert the time into distance in centimeters
  int distance = duration * 0.034 / 2;     // Formula to calculate distance

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if the object is closer than 10 cm
  if (distance < 10) {
    digitalWrite(ledPin, HIGH);  // If yes, turn ON the LED
  } else {
    digitalWrite(ledPin, LOW);   // If not, turn OFF the LED
  }

  delay(500);  // Wait for half a second before the next measurement
}