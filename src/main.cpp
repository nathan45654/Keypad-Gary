/*********************************************************************
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 Copyright (c) 2019 Ha Thach for Adafruit Industries
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <Arduino.h>
// #include "Adafruit_TinyUSB.h"
#include "Keypad.h"
#include "Button.h"
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 1
#define PIXELS_PIN 8
#define FLASH_TIME 100
Adafruit_NeoPixel pixels(NUMPIXELS, PIXELS_PIN);

// Pin definitions for F13-F24 macro keys
enum keypadState {
    ONE,
    TWO,
    THREE
};

keypadState keypad_state{ONE};

#define STATE_1_PIN 10
#define F13_PIN 9
#define F14_PIN 5
#define F15_PIN 23

#define STATE_2_PIN 13
#define F16_PIN 12
#define F17_PIN 19
#define F18_PIN 18

#define STATE_3_PIN 14
#define F19_PIN 16
#define F20_PIN 2
#define F21_PIN 22

#define DEBOUNCE_TIME 10

Button buttons[] = {
    Button(STATE_1_PIN, DEBOUNCE_TIME, LOW),   
    Button(F13_PIN, DEBOUNCE_TIME, LOW),   // F13 - pin to ground, so activeState = LOW
    Button(F14_PIN, DEBOUNCE_TIME, LOW),   // F14
    Button(F15_PIN, DEBOUNCE_TIME, LOW),   // F15

    Button(STATE_2_PIN, DEBOUNCE_TIME, LOW),   
    Button(F16_PIN, DEBOUNCE_TIME, LOW),   // F16
    Button(F17_PIN, DEBOUNCE_TIME, LOW),   // F17
    Button(F18_PIN, DEBOUNCE_TIME, LOW),   // F18

    Button(STATE_3_PIN, DEBOUNCE_TIME, LOW),   
    Button(F19_PIN, DEBOUNCE_TIME, LOW),   // F19
    Button(F20_PIN, DEBOUNCE_TIME, LOW),   // F20
    Button(F21_PIN, DEBOUNCE_TIME, LOW)   // F21
    };
Keypad keypad;

// 
bool buttonActiveState = true;

void flashPixelColor(uint8_t r, uint8_t g, uint8_t b);
void setupButtonCallbacks();

// the setup function runs once when you press reset or power the board
void setup() {

    Serial.begin(115200);
    Serial.write("checking pins... ");
    keypad.begin();
    pixels.begin();
    pixels.clear();
    pixels.setBrightness(50);
    pixels.show();

    setupButtonCallbacks();
    
}

void loop() {

    for (uint8_t i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++) {
        buttons[i].update();
    }

}

void flashPixelColor(uint8_t r, uint8_t g, uint8_t b)
{
    pixels.setPixelColor(0, r, g, b);
    pixels.show();
    delay(FLASH_TIME);
    pixels.clear();
    pixels.show();
}

void setupButtonCallbacks() {

    buttons[0].setPressCallback([]() {
        flashPixelColor(255, 0, 0);    // Red - F13
        keypad_state = ONE;
        Serial.println("state one active");
    });
    
    buttons[1].setPressCallback([]() {
        flashPixelColor(255, 165, 0);  // Orange - F13
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F13);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F13);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F13);
        }
        Serial.println("State " + String(keypad_state) + ": F13 pressed on pin " + String(buttons[1].Pin()));
    });
    
    buttons[2].setPressCallback([]() {
        flashPixelColor(255, 255, 0);  // Yellow - F14
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F14);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F14);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F14);
        }
        Serial.println("State " + String(keypad_state) + ": F14 pressed on pin " + String(buttons[2].Pin()));
    });
    
    buttons[3].setPressCallback([]() {
        flashPixelColor(0, 255, 0);    // Green - F15
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F15);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F15);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F15);
        }
        Serial.println("State " + String(keypad_state) + ": F15 pressed on pin " + String(buttons[3].Pin()));
    });
    
    buttons[4].setPressCallback([]() {
        flashPixelColor(0, 255, 255);  // Cyan - F16
        keypad_state = TWO;
        Serial.println("state two active");
    });
    
    buttons[5].setPressCallback([]() {
        flashPixelColor(0, 0, 255);    // Blue - F17
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F16);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F16);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F16);
        }
        Serial.println("State " + String(keypad_state) + ": F16 pressed on pin " + String(buttons[5].Pin()));
    });
    
    buttons[6].setPressCallback([]() {
        flashPixelColor(255, 0, 255);  // Purple - F18
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F17);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F17);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F17);
        }
        Serial.println("State " + String(keypad_state) + ": F17 pressed on pin " + String(buttons[6].Pin()));
    });
    
    buttons[7].setPressCallback([]() {
        flashPixelColor(255, 192, 203); // Pink - F19
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F18);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F18);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F18);
        }
        Serial.println("State " + String(keypad_state) + ": F18 pressed on pin " + String(buttons[7].Pin()));
    });
    
    buttons[8].setPressCallback([]() {
        flashPixelColor(255, 255, 255); // White - F20
        keypad_state = THREE;
        Serial.println("state three active");
    });
    
    buttons[9].setPressCallback([]() {
        flashPixelColor(50, 205, 50);  // Lime - F21
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F19);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F19);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F19);
        }
        Serial.println("State " + String(keypad_state) + ": F19 pressed on pin " + String(buttons[9].Pin()));
    });
    
    buttons[10].setPressCallback([]() {
        flashPixelColor(75, 0, 130);   // Indigo - F22
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F20);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F20);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F20);
        }
        Serial.println("State " + String(keypad_state) + ": F20 pressed on pin " + String(buttons[10].Pin()));
    });
    
    buttons[11].setPressCallback([]() {
        flashPixelColor(255, 0, 128);  // Magenta - F23
        if (keypad_state == ONE) {
            keypad.write(HID_KEY_F21);
        } else if (keypad_state == TWO) {
            keypad.write_with_modifier(HID_MODIFIER_SHIFT_LEFT, HID_KEY_F21);
        } else if (keypad_state == THREE) {
            keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_F21);
        }
        Serial.println("State " + String(keypad_state) + ": F21 pressed on pin " + String(buttons[11].Pin()));
    });
}