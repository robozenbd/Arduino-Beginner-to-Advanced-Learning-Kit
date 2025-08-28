// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
const int vrxPin = A0;     // The joystick's X pin is connected to analog pin A0
const int ledPin = 11;     // The LED is connected to pin 11 (a PWM pin)

void setup() {
    pinMode(ledPin, OUTPUT); // Set the LED pin as an output
}

void loop() {
    int xValue = analogRead(vrxPin);  // Read the X-axis value from the joystick (0 to 1023)

  // Convert the joystick value to a brightness level (0 to 80)
    int brightness = map(xValue, 0, 1023, 0, 80);

  // Set the LED brightness using PWM
    analogWrite(ledPin, brightness);
}