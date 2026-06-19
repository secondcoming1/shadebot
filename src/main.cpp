#include <Arduino.h>

const int STEP_PIN = 26;    // ESP32 D26 -> TMC2209 STP
const int DIR_PIN = 27;     // ESP32 D27 -> TMC2209 DIR
const int ENABLE_PIN = 25;  // ESP32 D25 -> TMC2209 EN

String commandBuffer = "";

void stepMotor(int steps, bool direction) {
    digitalWrite(DIR_PIN, direction ? HIGH : LOW);

    for (int i = 0; i < steps; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(800);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(800);
    }
}

void handleCommand(String command) {
    command.trim();

    Serial.print("Received command: ");
    Serial.println(command);

    if (command == "open") {
        Serial.println("Moving motor OPEN direction...");
        digitalWrite(ENABLE_PIN, LOW);   // LOW usually enables TMC2209
        stepMotor(800, true);
        Serial.println("Done.");
    }
    else if (command == "close") {
        Serial.println("Moving motor CLOSE direction...");
        digitalWrite(ENABLE_PIN, LOW);   // LOW usually enables TMC2209
        stepMotor(800, false);
        Serial.println("Done.");
    }
    else if (command == "stop") {
        Serial.println("Disabling motor driver.");
        digitalWrite(ENABLE_PIN, HIGH);  // HIGH usually disables TMC2209
    }
    else if (command == "enable") {
        Serial.println("Enabling motor driver.");
        digitalWrite(ENABLE_PIN, LOW);
    }
    else if (command == "status") {
        Serial.println("ShadeBot status: MOTOR TEST READY");
    }
    else if (command.length() == 0) {
        // Ignore blank lines
    }
    else {
        Serial.println("Unknown command.");
    }
}

void setup() {
    delay(2000);
    Serial.begin(115200);
    delay(1000);

    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);

    digitalWrite(STEP_PIN, LOW);
    digitalWrite(DIR_PIN, LOW);
    digitalWrite(ENABLE_PIN, HIGH); // Start disabled for safety

    Serial.println();
    Serial.println("ShadeBot motor test ready.");
    Serial.println("Type one of these commands and press Enter:");
    Serial.println("open");
    Serial.println("close");
    Serial.println("stop");
    Serial.println("enable");
    Serial.println("status");
    Serial.println();
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