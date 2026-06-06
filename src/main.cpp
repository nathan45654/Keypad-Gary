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

// Pin definitions for F13-F24 macro keys
#define F13_PIN 10
#define F14_PIN 11
#define F15_PIN 12
#define F16_PIN 13
#define F17_PIN 14
#define F18_PIN 15
#define F19_PIN 16
#define F20_PIN 17
#define F21_PIN 18
#define F22_PIN 19
#define F23_PIN 20
#define F24_PIN 21

Button buttons[] = {
    Button(5, 10, HIGH),
    Button(6, 10, HIGH),
    Button(7, 10, LOW),
    Button(9, 10, HIGH),
    Button(F13_PIN, 10, LOW),   // F13 - pin to ground, so activeState = LOW
    Button(F14_PIN, 10, LOW),   // F14
    Button(F15_PIN, 10, LOW),   // F15
    Button(F16_PIN, 10, LOW),   // F16
    Button(F17_PIN, 10, LOW),   // F17
    Button(F18_PIN, 10, LOW),   // F18
    Button(F19_PIN, 10, LOW),   // F19
    Button(F20_PIN, 10, LOW),   // F20
    Button(F21_PIN, 10, LOW),   // F21
    Button(F22_PIN, 10, LOW),   // F22
    Button(F23_PIN, 10, LOW),   // F23
    Button(F24_PIN, 10, LOW)    // F24
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
    
    // F13-F24 macro key callbacks with unique colors
    buttons[4].setPressCallback([]() {
        flashPixelColor(255, 0, 0);    // Red - F13
        keypad.write(HID_KEY_F13);
    });
    
    buttons[5].setPressCallback([]() {
        flashPixelColor(255, 165, 0);  // Orange - F14
        keypad.write(HID_KEY_F14);
    });
    
    buttons[6].setPressCallback([]() {
        flashPixelColor(255, 255, 0);  // Yellow - F15
        keypad.write(HID_KEY_F15);
    });
    
    buttons[7].setPressCallback([]() {
        flashPixelColor(0, 255, 0);    // Green - F16
        keypad.write(HID_KEY_F16);
    });
    
    buttons[8].setPressCallback([]() {
        flashPixelColor(0, 255, 255);  // Cyan - F17
        keypad.write(HID_KEY_F17);
    });
    
    buttons[9].setPressCallback([]() {
        flashPixelColor(0, 0, 255);    // Blue - F18
        keypad.write(HID_KEY_F18);
    });
    
    buttons[10].setPressCallback([]() {
        flashPixelColor(255, 0, 255);  // Purple - F19
        keypad.write(HID_KEY_F19);
    });
    
    buttons[11].setPressCallback([]() {
        flashPixelColor(255, 192, 203); // Pink - F20
        keypad.write(HID_KEY_F20);
    });
    
    buttons[12].setPressCallback([]() {
        flashPixelColor(255, 255, 255); // White - F21
        keypad.write(HID_KEY_F21);
    });
    
    buttons[13].setPressCallback([]() {
        flashPixelColor(50, 205, 50);  // Lime - F22
        keypad.write(HID_KEY_F22);
    });
    
    buttons[14].setPressCallback([]() {
        flashPixelColor(75, 0, 130);   // Indigo - F23
        keypad.write(HID_KEY_F23);
    });
    
    buttons[15].setPressCallback([]() {
        flashPixelColor(255, 0, 128);  // Magenta - F24
        keypad.write(HID_KEY_F24);
    });
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
