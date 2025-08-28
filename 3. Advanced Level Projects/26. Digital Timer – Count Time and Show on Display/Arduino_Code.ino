// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

#include <Wire.h>                  // Include library for I2C communication (used by LCD)
#include <LiquidCrystal_I2C.h>     // Include library for I2C LCD display

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Create LCD object with address 0x27, 16 columns and 2 rows

const int joyPin = A0;             // Joystick vertical (Y-axis) analog input pin
const int buttonPin = 2;           // Joystick button digital input pin
const int buzzerPin = 8;           // Buzzer output pin

int timerOptions[] = {20, 40, 60}; // Array of timer durations in seconds
int selectedIndex = 0;             // Index to track which timer is selected

bool isRunning = false;            // Flag to check if timer is running
bool isPaused = false;             // Flag to check if timer is paused

unsigned long previousMillis = 0;  // Store the last time the timer was updated
int remainingSeconds = 0;          // Remaining seconds for countdown

void setup() {
  lcd.init();                    // Initialize the LCD screen
  lcd.backlight();                // Turn on the LCD backlight
  pinMode(buttonPin, INPUT_PULLUP);  // Configure joystick button as input with internal pull-up resistor
  pinMode(buzzerPin, OUTPUT);        // Configure buzzer as output
  lcd.setCursor(0, 0);               // Set cursor to first row, first column
  lcd.print("Select Time:");         // Show initial message to select timer
}

void loop() {
  if (!isRunning) {  // If timer is NOT running, allow selecting timer option
    lcd.setCursor(0, 1);            // Move cursor to second row
    lcd.print(">> ");               // Display arrow to indicate selection
    lcd.print(timerOptions[selectedIndex]);  // Show selected timer duration
    lcd.print(" Sec (JSTK)");       // Show unit and hint for joystick use

    int joyVal = analogRead(joyPin);  // Read joystick vertical position

    if (joyVal < 400) {  // If joystick moved UP (value less than 400)
      selectedIndex = (selectedIndex + 1) % 3;  // Move selection up (looping between 0,1,2)
      delay(300);             // Small delay to avoid rapid changes
    } 
    else if (joyVal > 600) {  // If joystick moved DOWN (value greater than 600)
      selectedIndex = (selectedIndex + 2) % 3;  // Move selection down (looping between 0,1,2)
      delay(300);             // Small delay to avoid rapid changes
    }

    if (digitalRead(buttonPin) == LOW) {  // If joystick button pressed
      remainingSeconds = timerOptions[selectedIndex];  // Set timer to selected seconds
      isRunning = true;      // Mark timer as running
      isPaused = false;      // Timer starts unpaused
      lcd.clear();           // Clear the LCD screen
      lcd.setCursor(0, 0);   
      lcd.print("Timer Running...");  // Show timer running message
      previousMillis = millis();      // Record current time
      delay(300);                     // Debounce delay for button press
    }
  } 
  else {  // Timer is running
    if (digitalRead(buttonPin) == LOW) {  // If button pressed while timer running
      isPaused = !isPaused;     // Toggle pause/resume state
      lcd.clear();              // Clear LCD screen
      lcd.setCursor(0, 0);      
      if (isPaused) {
        lcd.print("Timer Paused");  // Show paused message
      } else {
        lcd.print("Timer Running..."); // Show running message
        previousMillis = millis();     // Reset timer reference to avoid jump
      }
      delay(300);  // Debounce delay for button press
    }

    if (!isPaused) {  // If timer is NOT paused
      unsigned long currentMillis = millis();  // Get current time
      if (currentMillis - previousMillis >= 1000 && remainingSeconds > 0) {  // If 1 second passed and time left
        previousMillis = currentMillis;  // Update last timer update time
        remainingSeconds--;               // Decrease remaining time by 1 second

        lcd.setCursor(0, 1);             // Move cursor to second row
        lcd.print("Time Left: ");        // Show label
        lcd.print(remainingSeconds);    // Show remaining seconds
        lcd.print("s   ");               // Add spaces to clear leftover chars
      }

      if (remainingSeconds <= 0) {  // If timer reached zero
        isRunning = false;           // Stop the timer
        lcd.clear();                 // Clear LCD screen
        lcd.setCursor(0, 0);         
        lcd.print("Time's Up!");     // Show time up message
        beepBuzzer();                // Call buzzer beep function
        delay(1000);                 // Wait 1 second before reset
        lcd.clear();                 // Clear LCD again
        lcd.setCursor(0, 0);
        lcd.print("Select Time:");   // Show initial message again
      }
    }
  }
}

void beepBuzzer() {
  unsigned long startTime = millis();       // Record the start time
  while (millis() - startTime < 5000) {     // Loop for 5 seconds total
    digitalWrite(buzzerPin, HIGH);           // Turn buzzer ON
    delay(300);                              // Wait 300 milliseconds
    digitalWrite(buzzerPin, LOW);            // Turn buzzer OFF
    delay(300);                              // Wait 300 milliseconds
  }
}