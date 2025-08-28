// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

#include <Wire.h>                     // For I2C communication
#include <LiquidCrystal_I2C.h>        // For LCD I2C display

// LCD address 0x27, 16 characters, 2 lines
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---- PIN Configuration ----
const int ldrPin = 4;       // LDR sensor digital output (HIGH/LOW)
const int pirPin = 3;       // PIR sensor digital output (motion detection)
const int relayPin = 2;     // Relay control pin
const int buttonPin = 5;    // Button to turn system ON or OFF

// ---- Variables ----
bool motionDetected = false;          // Flag to track if motion is detected
bool pirLastState = LOW;              // Last PIR sensor state
bool systemEnabled = true;            // System starts as ON
bool lastButtonState = HIGH;          // Last state of the button (for debounce)
unsigned long lastButtonPress = 0;    // Timestamp of last button press
const unsigned long debounceDelay = 300; // Debounce delay in milliseconds

unsigned long lastMotionTime = 0;     // Time of last motion detection
unsigned long relayDelay = 15000;     // Light ON duration (15 seconds)
int motionCount = 0;                  // Total number of detected motions

void setup() {
  // Set pin modes
  pinMode(ldrPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Using internal pull-up resistor

  digitalWrite(relayPin, HIGH);     // Relay OFF at start (active LOW)

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Scroll welcome message: "WWW.ROBOZENBD.COM"
  String message = "   WWW.ROBOZENBD.COM   ";
  for (int i = 0; i < message.length() - 15; i++) {
    lcd.setCursor(0, 0);
    lcd.print(message.substring(i, i + 16));
    delay(500);
  }

  lcd.clear();
}

void loop() {
  // ---- Button Toggle Logic ----
  bool currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == LOW && lastButtonState == HIGH && (millis() - lastButtonPress > debounceDelay)) {
    systemEnabled = !systemEnabled;     // Toggle system state
    lastButtonPress = millis();         // Save button press time
    lcd.clear();                        // Clear screen on toggle
  }
  lastButtonState = currentButtonState;

  // ---- System is OFF ----
  if (!systemEnabled) {
    digitalWrite(relayPin, HIGH);   // Make sure relay is OFF
    motionDetected = false;
    pirLastState = LOW;

    lcd.setCursor(0, 0);
    lcd.print("SYSTEM STATS:OFF");
    lcd.setCursor(0, 1);
    lcd.print("PRS BUTTON TO ON");
    delay(500);
    return; // Skip remaining code
  }

  // ---- System is ON ----
  bool isDark = digitalRead(ldrPin) == HIGH;   // Check if it's dark
  bool pirState = digitalRead(pirPin);         // Read PIR sensor

  if (isDark) {
    // --- Motion Detection Logic ---
    if (pirState == HIGH && pirLastState == LOW) {
      lastMotionTime = millis();   // Save time of detection
      motionDetected = true;       // Set motion flag
      motionCount++;               // Increase motion count
    }
    pirLastState = pirState;

    if (motionDetected) {
      unsigned long timeElapsed = millis() - lastMotionTime;

      if (timeElapsed <= relayDelay) {
        digitalWrite(relayPin, LOW); // Turn ON light
        lcd.setCursor(0, 0);
        lcd.print("SYSTEM ON FOR:");
        lcd.print((relayDelay - timeElapsed) / 1000); // Countdown in seconds
        lcd.print("s ");
        lcd.setCursor(0, 1);
        lcd.print("MVNT COUNT: ");
        lcd.print(motionCount);
        lcd.print("     ");
      } else {
        motionDetected = false;        // No recent motion
        digitalWrite(relayPin, HIGH);  // Turn OFF light
        lcd.clear();
      }
    } else {
      // No motion but system is ON and it's dark
      digitalWrite(relayPin, HIGH);    // Keep relay OFF
      lcd.setCursor(0, 0);
      lcd.print("SYSTEM STATS:ON ");
      lcd.setCursor(0, 1);
      lcd.print("MVNT COUNT: ");
      lcd.print(motionCount);
      lcd.print("     ");
      delay(500); // Slow refresh
    }

  } else {
    // It’s bright, system won't respond to motion
    motionDetected = false;
    pirLastState = LOW;
    digitalWrite(relayPin, HIGH);     // Light OFF
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM STATS:OFF");
    lcd.setCursor(0, 1);
    lcd.print("RSN:ENOUGH LIGHT");
    delay(1000);
  }
}