// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

#include <Wire.h>                  // Include library for I2C communication
#include <LiquidCrystal_I2C.h>     // Include library for I2C LCD display

LiquidCrystal_I2C lcd(0x27,16,2);  // Create LCD object at I2C address 0x27, 16 columns and 2 rows

const int gasSensorPin = A0;        // Analog pin connected to gas sensor output
const int buzzerPin = 8;            // Digital pin connected to buzzer

const int gasThreshold = 400;       // Threshold value for dangerous gas level

int previousGasLevel = 0;            // Store previous gas sensor reading to detect trend
unsigned long buzzerTimer = 0;      // Timer to control buzzer beep interval
const unsigned long buzzerInterval = 500; // Buzzer beep interval in milliseconds (0.5 seconds)

void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                  // Turn on LCD backlight
  pinMode(buzzerPin, OUTPUT);       // Set buzzer pin as output
  digitalWrite(buzzerPin, LOW);     // Turn buzzer off initially
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);  // Read current gas sensor value (0-1023)
  lcd.clear();                              // Clear LCD screen before updating

  // Display gas sensor value on first line
  lcd.setCursor(0,0);                       // Set cursor at first row, first column
  lcd.print("GAS LEVEL: ");                       // Print label
  lcd.print(gasLevel);                      // Print gas sensor value

  // Display gas status and trend on second line
  lcd.setCursor(0,1);                       // Move cursor to second row, first column

  if (gasLevel > gasThreshold) {            // If gas level exceeds threshold (danger)
    lcd.print("DANGER ");                    // Show "DANGER" warning

    // Make buzzer beep intermittently at buzzerInterval timing
    unsigned long currentMillis = millis(); // Get current time in milliseconds
    if (currentMillis - buzzerTimer >= buzzerInterval) {  // Check if interval passed
      buzzerTimer = currentMillis;                          // Reset buzzer timer
      digitalWrite(buzzerPin, !digitalRead(buzzerPin));    // Toggle buzzer state (on/off)
    }
  } else {
    lcd.print("SAFE    ");                 // Show "SAFE" if gas level is normal
    digitalWrite(buzzerPin, LOW);          // Make sure buzzer is off
  }

  // Show if gas level is rising, falling, or stable compared to last reading
  if (gasLevel > previousGasLevel) {
    lcd.print("  RISING");                  // Gas level increasing
  } else if (gasLevel < previousGasLevel) {
  } else {
    lcd.print("  STABLE");                  // Gas level unchanged
  }

  previousGasLevel = gasLevel;               // Save current gas level for next loop comparison
  delay(500);                               // Wait half a second before next reading/update
}