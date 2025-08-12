#include <BleGamepad.h>
#include <Adafruit_NeoPixel.h>

BleGamepad bleGamepad("Test Device", "idk", 100);

#define LED_PIN 8
#define NUMPIXELS 1
#define AXIS_PIN 3  // Analog input pin for joystick axis

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 500; // 500 ms for blink timing
bool ledOn = false;

void setup() {
  Serial.begin(115200);
  bleGamepad.begin();

  pixels.begin();
  pixels.show(); // Initialize all pixels to off
}

void loop() {

  //Serial.println(analogRead(AXIS_PIN));

  if (bleGamepad.isConnected()) {
    // Solid green LED when connected
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // Green
    pixels.show();

    // Read analog axis value (0–4095 for ESP32 ADC)
    int rawValue = analogRead(AXIS_PIN);
    // Map to joystick range (-32767 to 32767)
    int16_t mappedValue = map(rawValue, 0, 4095, -32767, 32767);

    // Send axis value as X-axis (or Y if you prefer)
    bleGamepad.setX(mappedValue);
    bleGamepad.sendReport();

  } else {
    // Blink red LED at 1 Hz when not connected
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledOn = !ledOn;

      if (ledOn) {
        pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Red ON
      } else {
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));   // LED OFF
      }
      pixels.show();
    }

    Serial.println("Waiting for BLE connection...");
  }

  delay(10);
}
