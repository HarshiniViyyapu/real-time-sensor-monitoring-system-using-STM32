
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensorPin = PA0;
const int ledPin = PA5;
const int buzzerPin = PA4;
const int threshold = 300;

void setup() {
  Serial.begin(115200);

  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Sensor Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  lcd.setCursor(0, 0);
  lcd.print("Sensor: ");
  lcd.print(sensorValue);
  lcd.print("    ");

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue >= threshold) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("ALARM: HIGH     ");
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: NORMAL  ");
  }

  delay(300);
}
