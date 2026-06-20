#pragma once

#include <Arduino.h>

class StepperMotor {
public:
    StepperMotor(int stepPin, int dirPin, int enablePin);

    void begin();

    void enable();
    void disable();

    void moveOpen(int steps);
    void moveClose(int steps);

    void setStepDelayMicros(int delayMicros);
    int getStepDelayMicros() const;

private:
    int _stepPin;
    int _dirPin;
    int _enablePin;
    int _stepDelayMicros;

    void stepMotor(int steps, bool direction);
};