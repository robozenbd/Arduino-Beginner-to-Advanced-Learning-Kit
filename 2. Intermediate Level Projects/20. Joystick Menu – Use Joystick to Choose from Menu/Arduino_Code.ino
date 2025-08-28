// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

#include <Wire.h>  // Include the Wire library to communicate with I2C devices
#include <LiquidCrystal_I2C.h>  // Include the library for I2C LCD

// Create an LCD object with address 0x27, and screen size 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define joystick pins
const int xPin = A0;  // X-axis of joystick connected to analog pin A0
const int yPin = A1;  // Y-axis of joystick connected to analog pin A1
const int swPin = 2;  // Joystick button (switch) connected to digital pin 2

// Create an array of menu items (you can change these to any options you want)
String menuItems[] = {"Option 1", "Option 2", "Option 3"};
int totalItems = 3;         // Total number of menu items
int currentItem = 0;        // Index of currently selected item (starts at 0)

void setup() {
  pinMode(swPin, INPUT_PULLUP);  // Set the joystick button as input with internal pull-up resistor
  lcd.begin();                   // Initialize the LCD
  lcd.backlight();               // Turn on the LCD backlight
  showMenu();                    // Display the initial menu
}

void loop() {
  int xValue = analogRead(xPin);  // Read X-axis value (not used here)
  int yValue = analogRead(yPin);  // Read Y-axis value (used to scroll menu)

  // If joystick is moved upward (yValue is low), go to previous item
  if (yValue < 300) {
    currentItem--;  // Move up in the menu
    if (currentItem < 0) currentItem = totalItems - 1;  // Wrap to last item if at top
    showMenu();  // Update the LCD with new menu item
    delay(300);  // Delay to avoid multiple fast scrolls
  }

  // If joystick is moved downward (yValue is high), go to next item
  if (yValue > 700) {
    currentItem++;  // Move down in the menu
    if (currentItem >= totalItems) currentItem = 0;  // Wrap to first item if at bottom
    showMenu();  // Update the LCD with new menu item
    delay(300);  // Delay to avoid fast repeated scrolls
  }

  // If joystick button is pressed (active low)
  if (digitalRead(swPin) == LOW) {
    lcd.clear();                    // Clear the screen
    lcd.setCursor(0, 0);            // Move cursor to first row
    lcd.print("Selected:");         // Show "Selected:" text
    lcd.setCursor(0, 1);            // Move cursor to second row
    lcd.print(menuItems[currentItem]);  // Show the selected menu item
    delay(1000);                    // Wait for 1 second
    showMenu();                     // Go back to the main menu
  }
}

// Function to display the current menu item on the LCD
void showMenu() {
  lcd.clear();                        // Clear LCD screen
  lcd.setCursor(0, 0);                // Set cursor to top-left corner
  lcd.print("> " + menuItems[currentItem]);  // Show current item with '>' arrow
  lcd.setCursor(0, 1);                // Move to second line
  lcd.print("  Scroll & Click");      // Instruction for user
}