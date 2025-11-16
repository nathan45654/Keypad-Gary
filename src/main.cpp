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
#include "Adafruit_TinyUSB.h"
#include "Keypad.h"
#include "Button.h"
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 1
#define PIXELS_PIN 8
Adafruit_NeoPixel pixels(NUMPIXELS, PIXELS_PIN);

Button buttons[] = {
    Button(5, 10, HIGH),
    Button(6, 10, HIGH),
    Button(7, 10, LOW),
    Button(9, 10, HIGH)
};
Keypad keypad;

// 
bool buttonActiveState = true;

void flashPixelColor(uint8_t r, uint8_t g, uint8_t b);


// the setup function runs once when you press reset or power the board
void setup() {

    keypad.begin();
    pixels.begin();
    pixels.clear();
    pixels.setBrightness(50);
    pixels.show();

    // led pin
    #ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    #endif

    // Set up pin as input
    // pinMode(5, buttonActiveState ? INPUT_PULLDOWN : INPUT_PULLUP);
    buttons[0].setPressCallback([]() {
        flashPixelColor(0, 150, 150);  // green flash
        keypad.write_with_modifier(HID_MODIFIER_CONTROL_LEFT, HID_KEY_Z);
    });
    buttons[0].setPullup(false);
    buttons[1].setPressCallback([]() {
        flashPixelColor(150, 0, 0);  // green flash
        keypad.write(HID_KEY_BACKSPACE);
    });
    buttons[1].setPullup(false);
    buttons[2].setPressCallback([]() {
        flashPixelColor(0, 150, 0);  // green flash
        keypad.write(HID_KEY_M);
        delay(5);
        keypad.write(HID_KEY_SPACE);
    });
    buttons[3].setPressCallback([]() {
        flashPixelColor(150, 150, 0);  // green flash
        keypad.write(HID_KEY_C);
        delay(5);
        keypad.write(HID_KEY_O);
        delay(5);
        keypad.write(HID_KEY_SPACE);
    });
    buttons[3].setPullup(false);
    
}

void loop() {

    for (uint8_t i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++) {
        buttons[i].update();
    }


    // if (digitalRead(5) == 0){ flashPixelColor(50, 0, 0); }
    // // if (button7.isPressed()){ flashPixelColor(0, 50, 0); }
    // else { flashPixelColor(50, 0, 0); }


}

void myPressHandler() {
    // e.g. set neopixel or call keypad.write(HID_KEY_Z);
}

void myReleaseHandler() {
    // e.g. clear neopixel
}

void flashPixelColor(uint8_t r, uint8_t g, uint8_t b)
{
    pixels.setPixelColor(0, r, g, b);
    pixels.show();
    delay(10);
    pixels.clear();
    pixels.show();
}