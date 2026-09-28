#include <LiquidCrystal.h>

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Sensor pins
const int ldrPin = A0;
const int tempPin = A1;

// LED pins
const int tempLED = 12;
const int lightLED = 13;

void setup() {
  pinMode(tempLED, OUTPUT);
  pinMode(lightLED, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("SMART ROOM");
  lcd.setCursor(0, 1);
  lcd.print("MONITORING");
  delay(2000);

  lcd.clear();
}

void loop() {

  // -------- Temperature Sensor --------
  int tempValue = analogRead(tempPin);

  float voltage = tempValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;

  // -------- LDR --------
  int lightValue = analogRead(ldrPin);

  // -------- LCD Display --------
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(lightValue);
  lcd.print("    ");

  // -------- Temperature Alert --------
  if (temperatureC > 30) {
    digitalWrite(tempLED, HIGH);
  } else {
    digitalWrite(tempLED, LOW);
  }

  // -------- Light Alert --------
  if (lightValue < 500) {
    digitalWrite(lightLED, HIGH);
  } else {
    digitalWrite(lightLED, LOW);
  }

  // -------- Serial Monitor --------
  Serial.print("Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.print(" C | Light: ");
  Serial.println(lightValue);

  delay(500);
}