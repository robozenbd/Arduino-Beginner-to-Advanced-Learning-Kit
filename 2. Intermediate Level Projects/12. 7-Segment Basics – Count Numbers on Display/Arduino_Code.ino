// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
const int a = 2;  // Segment 'a'
const int b = 3;  // Segment 'b'
const int c = 4;  // Segment 'c'
const int d = 5;  // Segment 'd'
const int e = 6;  // Segment 'e'
const int f = 8;  // Segment 'f'
const int g = 7;  // Segment 'g'

// Define pin for push button input
const int buttonPin = 10;  // Push button connected to digital pin 10

// A flag to check if a button press was detected
bool bPress = false;

// Variables to keep track of button press state
int buttonPushCounter = 0;   // How many times the button was pressed
int buttonState = 0;         // Current state of the button (pressed or not)
int lastButtonState = 0;     // Previous state of the button (used for detecting state change)

void setup() {
  // Set all 7-segment segment pins as OUTPUT
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  // Set the button pin as INPUT_PULLUP (internal pull-up resistor used)
  // This means: when button is not pressed, pin reads HIGH; when pressed, it reads LOW
  pinMode(buttonPin, INPUT_PULLUP);

  // Start serial communication for debugging
  Serial.begin(9600);

  // Display the initial digit (0)
  displayDigit(buttonPushCounter);
}

void loop() {
  // Read the current state of the button (HIGH or LOW)
  buttonState = digitalRead(buttonPin);

  // Check if button state changed from last loop
  if (buttonState != lastButtonState) {
    // Button was just pressed (state changed from HIGH to LOW)
    if (buttonState == LOW) {
      bPress = true;  // Mark that a press happened
      buttonPushCounter++;  // Increment the counter

      // If counter goes beyond 9, wrap it back to 0
      if (buttonPushCounter > 9) {
        buttonPushCounter = 0;
      }

      Serial.println("on");  // Debug message
    } else {
      // Button was released (state went from LOW to HIGH)
      Serial.println("off");  // Debug message
    }

    // Small delay to avoid button bouncing (false triggers)
    delay(50);
  }

  // Store the current state as the last state for the next loop
  lastButtonState = buttonState;

  // If a valid press happened, update the display
  if (bPress) {
    turnOff();  // Turn off all segments before displaying new number
    displayDigit(buttonPushCounter);  // Show new digit
    bPress = false;  // Reset the press flag
  }
}

// Function to turn ON the correct segments to show a digit (0–9)
void displayDigit(int digit) {
  // Segment 'a' is ON for all except digits 1 and 4
  if (digit != 1 && digit != 4)
    digitalWrite(a, HIGH);

  // Segment 'b' is OFF for digits 5 and 6
  if (digit != 5 && digit != 6)
    digitalWrite(b, HIGH);

  // Segment 'c' is OFF only for digit 2
  if (digit != 2)
    digitalWrite(c, HIGH);

  // Segment 'd' is ON for all except 1, 4, and 7
  if (digit != 1 && digit != 4 && digit != 7)
    digitalWrite(d, HIGH);

  // Segment 'e' is ON for 2, 6, 8, and 0
  if (digit == 2 || digit == 6 || digit == 8 || digit == 0)
    digitalWrite(e, HIGH);

  // Segment 'f' is OFF for 1, 2, 3, and 7
  if (digit != 1 && digit != 2 && digit != 3 && digit != 7)
    digitalWrite(f, HIGH);

  // Segment 'g' is ON for all except 0, 1, and 7
  if (digit != 0 && digit != 1 && digit != 7)
    digitalWrite(g, HIGH);
}

// Function to turn OFF all segments before displaying a new digit
void turnOff() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}