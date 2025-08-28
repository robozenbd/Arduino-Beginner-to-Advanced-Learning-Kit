#include <Keypad.h>                // Library for handling 4x4 keypad
#include <LiquidCrystal_I2C.h>     // Library for using I2C LCD display
#include <Servo.h>                 // Library for controlling servo motors

// Initialize LCD with I2C address 0x27 and 16x2 characters
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define keypad rows and columns (4x4 keypad)
const byte ROWS = 4;
const byte COLS = 4;

// Keypad character layout (same as physical keys)
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad row pins to Arduino pins
byte rowPins[ROWS] = {9, 8, 7, 6};  // R1-R4 connected to digital pins

// Connect keypad column pins to Arduino pins
byte colPins[COLS] = {5, 4, 3, 2};  // C1-C4 connected to digital pins

// Create a keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Set the correct password
String password = "1234";

// Variable to store user input
String input = "";

// Counter to track wrong attempts
int attempts = 0;

// Pin setup for components
const int greenLED = 11;   // Green LED for access granted
const int redLED = 12;     // Red LED for wrong password
const int buzzer = 13;     // Buzzer to alert wrong password

Servo gateServo;           // Servo motor object for gate

void setup() {
  lcd.init();             // Start LCD
  lcd.backlight();         // Turn on LCD backlight

  pinMode(greenLED, OUTPUT); // Set green LED as output
  pinMode(redLED, OUTPUT);   // Set red LED as output
  pinMode(buzzer, OUTPUT);   // Set buzzer as output

  gateServo.attach(10);     // Connect servo signal pin to pin 10
  gateServo.write(0);       // Start with gate closed

  scrollMessage("www.robozenbd.com");  // Show scrolling text
  lcd.clear();             // Clear LCD after scroll
  lcd.setCursor(0, 0);     // Set cursor to top line
  lcd.print("Enter Password:"); // Prompt user
}

void loop() {
  char key = keypad.getKey();   // Read key pressed

  if (key) { // If a key is pressed
    if (key == '#') {       // '#' is used to submit password
      checkPassword();      // Call function to check password
    } else if (key == 'C') { // '' clears input
      input = "";            // Clear input
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Password:");
    } else {
      if (input.length() < 16) { // Limit input to 16 characters
        input += key;            // Add key to input string
        lcd.setCursor(0, 1);     // Show input on second line
        lcd.print(input);
      }
    }
  }
}

void checkPassword() {
  if (input == password) {      // If password is correct
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted"); // Show success message
    digitalWrite(greenLED, HIGH); // Turn on green LED
    gateServo.write(90);          // Open the gate (rotate servo)

    delay(5000);                  // Keep gate open for 5 seconds

    gateServo.write(0);           // Close the gate
    digitalWrite(greenLED, LOW);  // Turn off green LED

    // Reset LCD and input
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    input = "";
    attempts = 0;                 // Reset attempt counter

  } else { // If password is incorrect
    attempts++;                   // Increase attempt count
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Incorrect!");
    digitalWrite(redLED, HIGH);   // Turn on red LED
    tone(buzzer, 1000, 500);      // Buzz for 0.5 sec
    delay(1000);                  // Wait 1 second
    digitalWrite(redLED, LOW);    // Turn off red LED

    lcd.setCursor(0, 1);
    lcd.print("Try Again");
    delay(1000);                  // Display message briefly

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    input = "";                   // Clear wrong input

    // If 3 wrong attempts, lock system briefly
    if (attempts >= 3) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access Denied!");
      digitalWrite(redLED, HIGH); // Red LED on
      tone(buzzer, 1500);         // Continuous buzzer
      delay(5000);                // Lockout time
      noTone(buzzer);             // Stop buzzer
      digitalWrite(redLED, LOW);  // Red LED off

      attempts = 0;               // Reset attempts
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Password:");
    }
  }
}

// Function to scroll a message on LCD
void scrollMessage(String msg) {
  msg = "                " + msg + "                "; // Add blank padding
  for (int i = 0; i < msg.length() - 15; i++) {
    lcd.clear();                  // Clear LCD
    lcd.setCursor(0, 0);          // Set to first row
    lcd.print(msg.substring(i, i + 16)); // Print 16-character window
    delay(250);                   // Delay between shifts
  }
}