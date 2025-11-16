#include "Button.h"

Button::Button(int pin, unsigned long debounceTime, bool activeState)
    : _pin(pin),
      _currentState(false),
      _lastState(false),
      _pressedEvent(false),
      _releasedEvent(false),
      _lastDebounceTime(0),
      _debounceDelay(debounceTime),
      _activeState(activeState),
      _onPress(nullptr),
      _onRelease(nullptr)
{
    pinMode(_pin, INPUT_PULLUP);
}

void Button::setPullup(bool enable)
{
    pinMode(_pin, enable ? INPUT_PULLUP : INPUT);
}

void Button::setActiveState(bool activeState)
{
    _activeState = activeState;
}

void Button::update() {
    bool reading = digitalRead(_pin) == _activeState;  // Use _activeState
    unsigned long currentTime = millis();

    // Debounce logic
    if (reading != _lastState) {
        _lastDebounceTime = currentTime;
    }

    if ((currentTime - _lastDebounceTime) > _debounceDelay) {
        if (reading != _currentState) {
            _currentState = reading;

            if (_currentState) {
                _pressedEvent = true;
                // invoke press callback if set
                if (_onPress) _onPress();
            } else {
                _releasedEvent = true;
                // invoke release callback if set
                if (_onRelease) _onRelease();
            }
        }
    }

    _lastState = reading;
}

bool Button::isPressed() const {
    return _currentState;
}

bool Button::wasPressed() {
    if (_pressedEvent) {
        _pressedEvent = false;
        return true;
    }
    return false;
}

bool Button::wasReleased() {
    if (_releasedEvent) {
        _releasedEvent = false;
        return true;
    }
    return false;
}

// callback setters
void Button::setPressCallback(void (*cb)()) {
    _onPress = cb;
}

void Button::setReleaseCallback(void (*cb)()) {
    _onRelease = cb;
}

void Button::clearPressCallback() {
    _onPress = nullptr;
}

void Button::clearReleaseCallback() {
    _onRelease = nullptr;
}
