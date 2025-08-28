// 🔐 Smart Door Lock System
// Components: Arduino UNO, Servo, 4x4 Keypad, 16x2 I2C LCD, Buzzer, Green + Red LED
// Author: Robozen BD (Beginner-Friendly Code)

// লাইব্রেরি ইনক্লুড
#include <Servo.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD সেটআপ (I2C 16x2 LCD – সাধারণত 0x27 address হয়)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo সেটআপ
Servo myServo;
int servoPin = 10;   // Servo signal pin

// LED + Buzzer পিন
int greenLED = 12;
int redLED   = 13;
int buzzer   = 11;

// Keypad সেটআপ
const byte ROWS = 4; // 4 rows
const byte COLS = 4; // 4 columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};   // Keypad row pins
byte colPins[COLS] = {5, 4, 3, 2};   // Keypad col pins
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password সেটআপ
String password = "1234";  // Default password
String inputPassword = "";

int wrongCount = 0;        // Wrong password counter
bool systemLocked = false; // Lock status

void setup() {
  // Servo attach
  myServo.attach(servoPin);
  myServo.write(0); // Initial position → locked

  // LED এবং Buzzer pinMode
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(redLED, HIGH);   // Start → Locked mode
  digitalWrite(greenLED, LOW);

  // LCD শুরু
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Smart Door Lock ");
  lcd.setCursor(0, 1);
  lcd.print(" Enter Password ");
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey(); // কীপ্যাড থেকে কী পড়া

  if (systemLocked) {
    lcd.setCursor(0, 0);
    lcd.print(" System Locked! ");
    lcd.setCursor(0, 1);
    lcd.print(" Try Reset (*)  ");
    
    // Hidden Reset Mode → * চাপলে reset হবে
    if (key == '*') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Enter Old Pass ");
      String resetPass = getPasswordInput();
      if (resetPass == password) {
        wrongCount = 0;
        systemLocked = false;
        lcd.clear();
        lcd.print(" Reset Success! ");
        digitalWrite(buzzer, LOW);
        delay(2000);
        lcd.clear();
      } else {
        lcd.clear();
        lcd.print(" Reset Failed! ");
        delay(2000);
        lcd.clear();
      }
    }
    return;
  }

  if (key) { // যদি কোনো key চাপা হয়
    if (key == '#') { 
      // Password এন্ট্রি শেষ (# দিয়ে)
      if (inputPassword == password) {
        accessGranted();
      } else {
        wrongCount++;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Wrong Password ");
        lcd.setCursor(0, 1);
        lcd.print(" Wrong: ");
        lcd.print(wrongCount);
        
        if (wrongCount >= 3) {
          systemLocked = true;
          digitalWrite(buzzer, HIGH);
        }
        delay(2000);
        lcd.clear();
      }
      inputPassword = ""; // Reset input
    } 
    else if (key == '*') {
      // Hidden reset shortcut
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" Enter Old Pass ");
      String resetPass = getPasswordInput();
      if (resetPass == password) {
        wrongCount = 0;
        lcd.clear();
        lcd.print(" Reset Success ");
        delay(2000);
        lcd.clear();
      } else {
        lcd.clear();
        lcd.print(" Reset Failed! ");
        delay(2000);
        lcd.clear();
      }
    } 
    else {
      // Password build করা
      inputPassword += key;
      lcd.setCursor(0, 0);
      lcd.print(" Entering...    ");
      lcd.setCursor(0, 1);
      lcd.print("Length: ");
      lcd.print(inputPassword.length());
    }
  }
}

// ✅ Access Granted Function
void accessGranted() {
  lcd.clear();
  lcd.print(" Access Granted ");
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  myServo.write(90); // Door unlock
  delay(5000);       // 5 sec open
  myServo.write(0);  // Door lock again
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  lcd.clear();
  lcd.print(" Door Locked ");
  delay(2000);
  lcd.clear();
}

// 🔑 Helper function → password entry নেয়া
String getPasswordInput() {
  String tempPass = "";
  while (true) {
    char k = keypad.getKey();
    if (k) {
      if (k == '#') break; // End password input
      tempPass += k;
    }
  }
  return tempPass;
}
