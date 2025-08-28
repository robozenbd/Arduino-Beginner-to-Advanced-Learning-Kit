#include <Wire.h>  // Include the library to communicate with I2C devices
#include <LiquidCrystal_I2C.h>  // Include the LCD I2C library

// Initialize LCD with I2C address 0x27 and 16 columns x 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the pin numbers connected to different sensors and components
int flameSensor = 5;       // Digital pin for flame sensor (LOW = fire detected)
int gasSensor = A1;        // Analog pin for gas sensor (higher value = more gas)
int pirSensor = 2;         // Digital pin for PIR motion sensor (HIGH = motion detected)

int buzzer = 3;            // Digital pin connected to buzzer
int redLED = 13;         // Used for Fire alert signal
int yellowLED = 6;         // Used as Gas alert signal

void setup() {
  // Set pin modes for inputs and outputs
  pinMode(flameSensor, INPUT);     // Set flame sensor as input
  pinMode(gasSensor, INPUT);       // Set gas sensor as input
  pinMode(pirSensor, INPUT);       // Set motion sensor as input
  pinMode(buzzer, OUTPUT);         // Set buzzer as output
  pinMode(redLED, OUTPUT);       // Set LED as output
  pinMode(yellowLED, OUTPUT);      //Set LED as output

  Serial.begin(9600);              // Start serial communication for debugging

  lcd.init();                     // Initialize the LCD screen
  lcd.backlight();                 // Turn on the LCD backlight
  lcd.setCursor(0, 0);             // Set cursor to first line, first column
  lcd.print("Smart Alert Ready");  // Print startup message
  delay(2000);                     // Wait 2 seconds
  lcd.clear();                     // Clear the screen
}

void loop() {
  // Read sensor values
  int flameDetected = digitalRead(flameSensor);   // Read flame sensor (LOW = fire)
  int gasValue = analogRead(gasSensor);           // Read gas sensor (analog value)
  int motionDetected = digitalRead(pirSensor);    // Read PIR sensor (HIGH = motion)

  lcd.clear();                    // Clear LCD before updating new info
  lcd.setCursor(0, 0);            // Set cursor to first line
  lcd.print("Gas:");              // Show gas label
  lcd.print(gasValue);            // Show gas value
  lcd.setCursor(0, 1);            // Move to second line of LCD

  // 🔴 Condition 1: Fire + Gas + Human
  if (flameDetected == LOW && gasValue > 300 && motionDetected == HIGH) {
    lcd.print("MOTION+FIRE+GAS");  // Display alert message
    tone(buzzer, 1000);            // Turn on buzzer with 1000Hz tone
    digitalWrite(redLED, HIGH);  // Turn on Fire LED
    digitalWrite(yellowLED, HIGH);  // Turn on Gas LED
  }

  // 🔴 Condition 2: Fire + Gas (but no human detected)
  else if (flameDetected == LOW && gasValue > 300) {
    lcd.print("GAS + FIRE");       // Display alert
    tone(buzzer, 1000);            // Turn on buzzer
    digitalWrite(redLED, HIGH);  // Turn on LED
    digitalWrite(yellowLED, HIGH);  // Turn on LED
  }

  // ⚠ Condition 3: Gas + Human
  else if (gasValue > 300 && motionDetected == HIGH) {
    lcd.print("GAS + MOTION");     // Tell human to leave room
    noTone(buzzer);                // Turn off buzzer
    digitalWrite(redLED, LOW);   // LED stays off
        // Blink LED as a warning for 10 seconds
    for (int i = 0; i < 20; i++) {     // Repeat 20 times (250ms on/off = 10s)
      digitalWrite(yellowLED, HIGH);    // LED ON
      delay(250);                      // Wait 250ms
      digitalWrite(yellowLED, LOW);     // LED OFF
      delay(250);                      // Wait 250ms
    }
  }

  // 🔥 Condition 4: Fire + Human
  else if (flameDetected == LOW && motionDetected == HIGH) {
    lcd.print("FIRE + MOTION");    // Display fire warning
    noTone(buzzer);                // Turn off buzzer

    // Blink LED as a warning for 10 seconds
    for (int i = 0; i < 20; i++) {     // Repeat 20 times (250ms on/off = 10s)
      digitalWrite(redLED, HIGH);    // LED ON
      delay(250);                      // Wait 250ms
      digitalWrite(redLED, LOW);     // LED OFF
      delay(250);                      // Wait 250ms
    }
  }

  // 🔥 Condition 5: Only Fire (no human, no gas)
  else if (flameDetected == LOW) {
    lcd.print("FIRE DETECTED");   // Show fire alert
    noTone(buzzer);                   // Buzzer stays off in this case
    digitalWrite(redLED, HIGH);     // Turn on LED
  }

  // 🟡 Condition 6: High gas level but no human present
  else if (gasValue > 300 && motionDetected == LOW) {
    lcd.print("-HIGH GAS LEVEL-");    // Show gas warning
    noTone(buzzer);                   // No buzzer sound
    digitalWrite(yellowLED, HIGH);     // Turn on LED
  }

  // ✅ All safe: No fire, no gas, no human
  else {
    lcd.print("------SAFE------");    // System is in safe condition
    noTone(buzzer);                   // Buzzer off
    digitalWrite(redLED, LOW);      // LED off
    digitalWrite(yellowLED, LOW);      // LED off
  }

  delay(1000);  // Wait 1 second before next reading
}