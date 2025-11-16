#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
    Button(int pin, unsigned long debounceTime = 50, bool activeState = LOW);
    void setPullup(bool enable);
    void setActiveState(bool activeState);

    void update();             // call this every loop() cycle
    bool isPressed() const;    // current state
    bool wasPressed();         // true once when pressed down
    bool wasReleased();        // true once when released

    // Callback setters
    void setPressCallback(void (*cb)());
    void setReleaseCallback(void (*cb)());
    void clearPressCallback();
    void clearReleaseCallback();

private:
    int _pin;
    bool _currentState;
    bool _lastState;
    bool _pressedEvent;
    bool _releasedEvent;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
    bool _activeState;

    // callbacks
    void (*_onPress)();
    void (*_onRelease)();

};

#endif
