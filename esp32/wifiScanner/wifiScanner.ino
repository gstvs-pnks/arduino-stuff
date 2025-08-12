#include <WiFi.h>
#include <Wire.h>
#include <I2C_LCD.h>

// LCD setup (change address if needed)
I2C_LCD lcd(0x27);

void setup() {
  Serial.begin(115200);

  // Init I2C with SDA=6, SCL=7
  Wire.begin(6, 7);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Scanner");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(1500);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning...");
  delay(1000);

  int n = WiFi.scanNetworks();
  if (n == 0) {
    lcd.clear();
    lcd.print("No networks");
    delay(2000);
  } else {
    for (int i = 0; i < n; i++) {
      lcd.clear();

      // First line: index and signal strength
      lcd.setCursor(0, 0);
      lcd.print(i + 1);
      lcd.print("/");
      lcd.print(n);
      lcd.print(" ");
      lcd.print(WiFi.RSSI(i));
      lcd.print("dB");

      // Second line: SSID with scrolling if needed
      String ssid = WiFi.SSID(i);
      if (ssid.length() <= 16) {
        lcd.setCursor(0, 1);
        lcd.print(ssid);
        delay(2000); // Wait before showing next network
      } else {
        // Scroll the long SSID
        for (int pos = 0; pos <= ssid.length() - 16; pos++) {
          lcd.setCursor(0, 1);
          lcd.print(ssid.substring(pos, pos + 16));
          delay(300); // Adjust scrolling speed
        }
        delay(1000); // Pause after scrolling
      }
    }
  }
  delay(3000); // Pause before rescanning
}
