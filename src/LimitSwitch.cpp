#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(int pin)
    : _pin(pin) {
}

void LimitSwitch::begin() {
    pinMode(_pin, INPUT_PULLUP);
}

bool LimitSwitch::isPressed() const {
    // Using INPUT_PULLUP:
    // HIGH = not pressed
    // LOW  = pressed
    return digitalRead(_pin) == LOW;
}

int LimitSwitch::getPin() const {
    return _pin;
}