#pragma once

#include <Arduino.h>

class LimitSwitch {
public:
    LimitSwitch(int pin);

    void begin();
    bool isPressed() const;
    int getPin() const;

private:
    int _pin;
};