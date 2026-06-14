#include <Arduino.h>

String commandBuffer = "";

void handleCommand(String command) {
    command.trim();

    Serial.print("Received command: ");
    Serial.println(command);

    if (command == "open") {
        Serial.println("Opening shade...");
    }
    else if (command == "close") {
        Serial.println("Closing shade...");
    }
    else if (command == "stop") {
        Serial.println("Stopping shade...");
    }
    else if (command == "status") {
        Serial.println("ShadeBot status: IDLE");
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

    Serial.println();
    Serial.println("ShadeBot command interface ready.");
    Serial.println("Type one of these commands and press Enter:");
    Serial.println("open");
    Serial.println("close");
    Serial.println("stop");
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