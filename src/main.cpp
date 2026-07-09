#include <Arduino.h>
#include "StepperMotor.h"
#include "LimitSwitch.h"

// ESP32 to TMC2209 wiring:
// ESP32 D26 -> TMC2209 STP
// ESP32 D27 -> TMC2209 DIR
// ESP32 D25 -> TMC2209 EN

const int STEP_PIN = 26;
const int DIR_PIN = 27;
const int ENABLE_PIN = 25;

// Limit switch wiring:
// Switch terminal 1 / COM -> ESP32 GND
// Switch terminal 3 / NO  -> ESP32 GPIO pin
//
// Uses INPUT_PULLUP:
// HIGH = not pressed
// LOW  = pressed

const int OPEN_LIMIT_PIN = 32;
const int CLOSED_LIMIT_PIN = 33;

const int DEFAULT_MOVE_STEPS = 800;
const int LIMIT_TEST_MAX_STEPS = 4000;

StepperMotor shadeMotor(STEP_PIN, DIR_PIN, ENABLE_PIN);
LimitSwitch openLimit(OPEN_LIMIT_PIN);
LimitSwitch closedLimit(CLOSED_LIMIT_PIN);

String commandBuffer = "";

bool isOpenLimitReached() {
    return openLimit.isPressed();
}

bool isClosedLimitReached() {
    return closedLimit.isPressed();
}

void printLimitStatus() {
    Serial.print("Open limit: ");
    Serial.println(openLimit.isPressed() ? "PRESSED" : "not pressed");

    Serial.print("Closed limit: ");
    Serial.println(closedLimit.isPressed() ? "PRESSED" : "not pressed");
}

void printHelp() {
    Serial.println("ShadeBot limit switch test ready.");
    Serial.println("Type one of these commands and press Enter:");
    Serial.println("open");
    Serial.println("close");
    Serial.println("openlimit");
    Serial.println("closelimit");
    Serial.println("stop");
    Serial.println("enable");
    Serial.println("status");
    Serial.println("testlimits");
    Serial.println("speedslow");
    Serial.println("speednormal");
    Serial.println("help");
    Serial.println();
}

void handleCommand(String command) {
    command.trim();

    if (command.length() == 0) {
        return;
    }

    Serial.print("Received command: ");
    Serial.println(command);

    if (command == "open") {
        Serial.println("Moving motor OPEN direction for fixed step test...");
        shadeMotor.moveOpen(DEFAULT_MOVE_STEPS);
        shadeMotor.disable();
        Serial.println("Done.");
    }
    else if (command == "close") {
        Serial.println("Moving motor CLOSE direction for fixed step test...");
        shadeMotor.moveClose(DEFAULT_MOVE_STEPS);
        shadeMotor.disable();
        Serial.println("Done.");
    }
    else if (command == "openlimit") {
        if (openLimit.isPressed()) {
            Serial.println("Open limit already pressed. Not moving.");
            return;
        }

        Serial.println("Moving OPEN until open limit is pressed...");
        bool hitLimit = shadeMotor.moveOpenUntilLimit(
            LIMIT_TEST_MAX_STEPS,
            isOpenLimitReached
        );

        if (hitLimit) {
            Serial.println("Stopped: open limit reached.");
        } else {
            Serial.println("Stopped: max steps reached before open limit.");
        }
    }
    else if (command == "closelimit") {
        if (closedLimit.isPressed()) {
            Serial.println("Closed limit already pressed. Not moving.");
            return;
        }

        Serial.println("Moving CLOSE until closed limit is pressed...");
        bool hitLimit = shadeMotor.moveCloseUntilLimit(
            LIMIT_TEST_MAX_STEPS,
            isClosedLimitReached
        );

        if (hitLimit) {
            Serial.println("Stopped: closed limit reached.");
        } else {
            Serial.println("Stopped: max steps reached before closed limit.");
        }
    }
    else if (command == "stop") {
        Serial.println("Disabling motor driver.");
        shadeMotor.disable();
    }
    else if (command == "enable") {
        Serial.println("Enabling motor driver.");
        shadeMotor.enable();
    }
    else if (command == "status") {
        Serial.println("ShadeBot status: LIMIT SWITCH TEST READY");

        Serial.print("Step delay micros: ");
        Serial.println(shadeMotor.getStepDelayMicros());

        printLimitStatus();
    }
    else if (command == "testlimits") {
        printLimitStatus();
    }
    else if (command == "speedslow") {
        shadeMotor.setStepDelayMicros(2000);
        Serial.println("Motor speed set to slow.");
    }
    else if (command == "speednormal") {
        shadeMotor.setStepDelayMicros(800);
        Serial.println("Motor speed set to normal.");
    }
    else if (command == "help") {
        printHelp();
    }
    else {
        Serial.println("Unknown command.");
        Serial.println("Type help for available commands.");
    }
}

void setup() {
    delay(2000);

    Serial.begin(115200);
    delay(1000);

    shadeMotor.begin();
    openLimit.begin();
    closedLimit.begin();

    Serial.println();
    printHelp();
}

void loop() {
    while (Serial.available() > 0) {
        char incomingChar = Serial.read();

        if (incomingChar == '\n' || incomingChar == '\r') {
            if (commandBuffer.length() > 0) {
                handleCommand(commandBuffer);
                commandBuffer = "";
            }
        }
        else {
            commandBuffer += incomingChar;
        }
    }
}