// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Initialize LCD with I2C address 0x27, 16 columns and 2 rows

const int gasSensorPin = A0;         // Analog pin A0 connected to gas sensor output
const float thresholdVoltage = 1.0;  // Voltage level to consider gas detected

float displayedVoltage = 0.0;        // Variable to store the value shown on LCD

void setup() {
    lcd.init();         // Initialize the LCD
    lcd.backlight();    // Turn on the LCD backlight
    Serial.begin(9600); // Start serial communication at 9600 baud rate for debugging
}

void loop() {
    int gasValue = analogRead(gasSensorPin);              // Read analog value from gas sensor (0-1023)
    float voltage = gasValue * (5.0 / 1023.0);            // Convert sensor value to voltage (0-5V)

if (voltage > thresholdVoltage) {
    // If gas level is above threshold, update displayedVoltage instantly
    displayedVoltage = voltage;
} else {
    // If gas level is below threshold, slowly decrease displayedVoltage by 0.1 volts per second
    displayedVoltage -= 0.1 * 0.5;   // Decrease by 0.05 every 500ms (delay time)
    
    if (displayedVoltage < 0) {
      displayedVoltage = 0;          // Make sure voltage doesn't go below 0
    }
}

  // Show the gas level on the LCD
    lcd.clear();                      // Clear previous display
    lcd.setCursor(0, 0);             // Set cursor to first row, first column
    lcd.print("Gas Level:");         
    lcd.setCursor(0, 1);             // Set cursor to second row, first column
    lcd.print(displayedVoltage, 2);  // Print voltage with 2 decimal places
    lcd.print(" V");

  // Print gas voltage to Serial Monitor for debugging
    Serial.print("Gas sensor voltage: ");
    Serial.println(displayedVoltage, 2);

  delay(500);  // Wait for 500 milliseconds before reading again
}