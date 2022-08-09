#include <LiquidCrystal.h>
#include "DHT.h"

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int transistor = 10;
const int photoresistor = A0;

void setup(void) {
  pinMode(transistor, OUTPUT);
  pinMode(photoresistor, INPUT);
  dht.begin();
  lcd.begin(16, 2);
}

void loop() {
  //check ambient light, toggle transistor
  if (analogRead(photoresistor) < 100) {
    digitalWrite(transistor, LOW);
  } else {
    digitalWrite(transistor, HIGH);
  }

  //get sensor readings
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    return;
  }

  //display to lcd
  lcd.setCursor(0, 0);
  lcd.print("T ");
  lcd.print(t);
  lcd.print("C/ ");
  lcd.print(f);
  lcd.print("F");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");

  delay(2000);
}
