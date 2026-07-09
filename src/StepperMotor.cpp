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

bool StepperMotor::moveOpenUntilLimit(int maxSteps, bool (*limitReached)()) {
    enable();
    return stepMotorUntilLimit(maxSteps, true, limitReached);
}

bool StepperMotor::moveCloseUntilLimit(int maxSteps, bool (*limitReached)()) {
    enable();
    return stepMotorUntilLimit(maxSteps, false, limitReached);
}

void StepperMotor::setStepDelayMicros(int delayMicros) {
    if (delayMicros < 200) {
        _stepDelayMicros = 200;
    } else {
        _stepDelayMicros = delayMicros;
    }
}

int StepperMotor::getStepDelayMicros() const {
    return _stepDelayMicros;
}

void StepperMotor::setDirection(bool direction) {
    digitalWrite(_dirPin, direction ? HIGH : LOW);
    delay(10);
}

void StepperMotor::stepOnce() {
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(_stepDelayMicros);

    digitalWrite(_stepPin, LOW);
    delayMicroseconds(_stepDelayMicros);
}

void StepperMotor::stepMotor(int steps, bool direction) {
    setDirection(direction);

    for (int i = 0; i < steps; i++) {
        stepOnce();
    }
}

bool StepperMotor::stepMotorUntilLimit(int maxSteps, bool direction, bool (*limitReached)()) {
    setDirection(direction);

    for (int i = 0; i < maxSteps; i++) {
        if (limitReached != nullptr && limitReached()) {
            disable();
            return true;
        }

        stepOnce();
    }

    disable();
    return false;
}