// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

// Declare the pin numbers
#include <Wire.h>                  // Include I2C communication library
#include <LiquidCrystal_I2C.h>     // Include LCD library for I2C

LiquidCrystal_I2C lcd(0x27,16,2);  // Create LCD object, address 0x27, 16 columns and 2 rows

const int buttonPin = 2;            // Define Arduino pin 2 connected to push button
int buttonState = HIGH;             // Variable to store current button state, default HIGH (not pressed)
int lastButtonState = HIGH;         // Variable to store previous button state, start as HIGH
int counter = 0;                    // Variable to count how many times button is pressed

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor enabled
  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on LCD backlight for visibility

  lcd.setCursor(0,0);               // Set cursor to first row, first column
  lcd.print("Button Count:");       // Print label on LCD
  lcd.setCursor(0,1);               // Move cursor to second row, first column
  lcd.print(counter);               // Display initial count (0)
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Read current state of the button (HIGH or LOW)

  // Check if button was just pressed (changed from HIGH to LOW)
if (lastButtonState == HIGH && buttonState == LOW) {
    counter++;                          // Increase count by 1 on each press
    lcd.setCursor(0,1);                 // Go to second row, first column
    lcd.print("       ");               // Clear previous number by printing spaces
    lcd.setCursor(0,1);                 // Reset cursor to same position
    lcd.print(counter);                 // Print updated count
}

  lastButtonState = buttonState;       // Save current button state for next loop check
  delay(50);                           // Small delay for button debounce (avoid false multiple presses)
}