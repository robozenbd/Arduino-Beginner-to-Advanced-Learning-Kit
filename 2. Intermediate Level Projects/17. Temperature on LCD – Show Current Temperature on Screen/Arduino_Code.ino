// This project is a part of Robozen BD Arduino Beginner to Advanced Learning Kit.
// You can buy this kit or any other components from Robozen BD.

#include <Wire.h>                  // Include library for I2C communication
#include <LiquidCrystal_I2C.h>    // Include library to control I2C LCD
#include <DHT.h>                  // Include library to control DHT sensor

#define DHTPIN 2                  // Define Arduino pin 2 for DHT11 data signal
#define DHTTYPE DHT11             // Define the sensor type as DHT11

LiquidCrystal_I2C lcd(0x27,16,2); // Create LCD object with address 0x27 and size 16x2
DHT dht(DHTPIN, DHTTYPE);          // Create DHT sensor object with specified pin and type

void setup() {
  lcd.init();            // Initialize the LCD
  lcd.backlight();       // Turn on the LCD backlight so we can see the text
  dht.begin();           // Start communication with the DHT11 sensor
  Serial.begin(9600);    // Start serial communication for debugging at 9600 baud rate
}

void loop() {
  float temperature = dht.readTemperature();  // Read temperature value from sensor in Celsius

  if (isnan(temperature)) {                    // Check if reading failed (NaN means Not a Number)
    lcd.clear();                              // Clear LCD screen
    lcd.print("Sensor Error");                // Show error message on LCD
    return;                                   // Stop rest of loop and try again next time
}

  lcd.clear();                                // Clear LCD before showing new data
  lcd.setCursor(0,0);                         // Set cursor to first row, first column
  lcd.print("Temp: ");                        // Print label "Temp: " on LCD
  lcd.print(temperature);                     // Print the temperature value
  lcd.print(" C");                            // Print degree Celsius symbol

  Serial.print("Temperature: ");              // Print label on serial monitor
  Serial.print(temperature);                   // Print temperature value on serial monitor
  Serial.println(" C");                        // Print degree Celsius and move to new line

  delay(2000);                                // Wait 2 seconds before reading sensor again
}