#include <BleGamepad.h>
#include <Adafruit_NeoPixel.h>

BleGamepad bleGamepad("Test Device", "idk", 100);

const int buttonPin1 = 5;
const int buttonPin2 = 6;
const int buttonPin3 = 7;

#define LED_PIN 8
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 500; // 500 ms for blink timing
bool ledOn = false;

void setup() {
  Serial.begin(115200);
  bleGamepad.begin();

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);

  pixels.begin();
  pixels.show(); // Initialize all pixels to off
}

void loop() {
  if (bleGamepad.isConnected()) {
    // Solid green LED when connected
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // Green
    pixels.show();

    // Buttons are active LOW because of INPUT_PULLUP
    bool btn1Pressed = digitalRead(buttonPin1) == LOW;
    bool btn2Pressed = digitalRead(buttonPin2) == LOW;
    bool btn3Pressed = digitalRead(buttonPin3) == LOW;

    // Update button 5
    if (btn1Pressed) {
      bleGamepad.press(5);
    } else {
      bleGamepad.release(5);
    }

    // Update button 6
    if (btn2Pressed) {
      bleGamepad.press(6);
    } else {
      bleGamepad.release(6);
    }

    // Update button 7
    if (btn3Pressed) {
      bleGamepad.press(7);
    } else {
      bleGamepad.release(7);
    }

    bleGamepad.sendReport(); // Send the updated button states

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

  delay(10); // Small debounce delay
}
