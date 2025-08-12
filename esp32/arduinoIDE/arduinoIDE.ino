#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32 Button Box", "YourCompany", 100);

const int buttonPin1 = 12; // GPIO for Button 1
const int buttonPin2 = 13; // GPIO for Button 2

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    // Button pressed when pin goes LOW (pressed)
    if (digitalRead(buttonPin1) == LOW) {
      bleKeyboard.press('a');  // send 'a' key
    } else {
      bleKeyboard.release('a');
    }

    if (digitalRead(buttonPin2) == LOW) {
      bleKeyboard.press('b');  // send 'b' key
    } else {
      bleKeyboard.release('b');
    }
  }
  delay(10);
}
