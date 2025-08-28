#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; // R1, R2, R3, R4
byte colPins[COLS] = {6, 7, 8, 9}; // C1, C2, C3, C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);

String password = "1234";
String input = "";

int buzzer = 10; // Buzzer pin

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Enter Password:");
  pinMode(buzzer, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '#') {
      if (input == password) {
        lcd.clear();
        lcd.print("Access Granted");
        digitalWrite(buzzer, HIGH); // Buzzer ON
        delay(3000);                // 3 seconds
        digitalWrite(buzzer, LOW);  // Buzzer OFF
        lcd.clear();                // Clear LCD
        lcd.print("Enter Password:");
        input = ""; // Reset input
      } else {
        lcd.clear();
        lcd.print("Wrong Password");
        delay(2000);
        lcd.clear();
        lcd.print("Enter Password:");
        input = ""; // Reset input
      }
    }
    else if (key == 'C') {
      input = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else if (key >= '0' && key <= '9') {
      if (input.length() < 4) {
        input += key;
        lcd.setCursor(input.length() - 1, 1);
        lcd.print("*");
      }
    }
  }
}
