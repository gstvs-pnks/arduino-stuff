#include <Joystick.h>

// Define pin numbers
const int buttonPins[3] = {2, 3, 4};

// Create Joystick with 3 buttons
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_GAMEPAD,
                   3,    // Number of buttons
                   0,    // No hat switch
                   false, false, false, // No axes
                   false, false, false,
                   false, false,
                   false, false, false);

// Store last state to avoid redundant updates
bool lastButtonState[3] = {false, false, false};

void setup() {
  // Use normal digital input mode
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT);  // NOT INPUT_PULLUP
  }

  // Start the Joystick HID interface
  Joystick.begin();
}

void loop() {
  for (int i = 0; i < 3; i++) {
    // HIGH means pressed
    bool pressed = digitalRead(buttonPins[i]) == HIGH;
    if (pressed != lastButtonState[i]) {
      Joystick.setButton(i, pressed);
      lastButtonState[i] = pressed;
    }
  }
  delay(5); // Small debounce interval
}
