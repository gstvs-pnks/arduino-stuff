#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <I2C_LCD.h>

// Pin where the DS18B20 is connected
#define ONE_WIRE_BUS 2

// Setup a oneWire instance
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature
DallasTemperature sensors(&oneWire);

// LCD setup 
I2C_LCD lcd(0x27);


void setup() {
  Serial.begin(9600);
  sensors.begin(); // Start up the library

  Wire.begin(6, 7);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TempSense v1.1");
}

void loop() {
  sensors.requestTemperatures(); // Send command to get temperatures
  float tempC1 = sensors.getTempCByIndex(0); // Get temp in °C for first sensor
  float tempC2 = sensors.getTempCByIndex(1);
  //Serial.print("Temperature: ");
  //Serial.print(tempC);
  //Serial.println(" °C");
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp.1 : ");
  lcd.print(tempC1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Temp.2 : ");
  lcd.print(tempC2);
  lcd.print(" C");


  delay(1000);
}
