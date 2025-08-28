#include <Servo.h>

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 8;

// Servo motor pin
const int servoPin = 7;

// Create servo object
Servo myServo;

// Distance threshold (cm)
const int thresholdDistance = 10;

void setup() {
  // Start serial monitor for debugging
  Serial.begin(9600);

  // Set ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo to pin
  myServo.attach(servoPin);
  myServo.write(0);  // Close dustbin initially
}

void loop() {
  long duration;
  int distance;

  // Send pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Check distance and control servo
  if (distance <= thresholdDistance) {
    myServo.write(90);  // Open dustbin
  } else {
    myServo.write(0);   // Close dustbin
  }

  delay(200); // Small delay for stability
}
