#include "StepperMotor.h"

StepperMotor::StepperMotor(int stepPin, int dirPin, int enablePin)
    : _stepPin(stepPin),
      _dirPin(dirPin),
      _enablePin(enablePin),
      _stepDelayMicros(800) {
}

void StepperMotor::begin() {
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);

    digitalWrite(_stepPin, LOW);
    digitalWrite(_dirPin, LOW);

    // TMC2209 EN is usually active LOW.
    // HIGH disables the driver.
    disable();
}

void StepperMotor::enable() {
    digitalWrite(_enablePin, LOW);
}

void StepperMotor::disable() {
    digitalWrite(_enablePin, HIGH);
}

void StepperMotor::moveOpen(int steps) {
    enable();
    stepMotor(steps, true);
}

void StepperMotor::moveClose(int steps) {
    enable();
    stepMotor(steps, false);
}

void StepperMotor::setStepDelayMicros(int delayMicros) {
    if (delayMicros < 200) {
        // Avoid going too fast for the first prototype.
        _stepDelayMicros = 200;
    } else {
        _stepDelayMicros = delayMicros;
    }
}

int StepperMotor::getStepDelayMicros() const {
    return _stepDelayMicros;
}

void StepperMotor::stepMotor(int steps, bool direction) {
    digitalWrite(_dirPin, direction ? HIGH : LOW);
    delay(10);

    for (int i = 0; i < steps; i++) {
        digitalWrite(_stepPin, HIGH);
        delayMicroseconds(_stepDelayMicros);

        digitalWrite(_stepPin, LOW);
        delayMicroseconds(_stepDelayMicros);
    }
}