# Limit Switch Safety Test

## Goal

Add physical endpoint detection so the motor stops when the open or closed limit switch is pressed.

## Hardware

- ESP32 DevKit
- TMC2209 stepper motor driver
- NEMA 17 stepper motor
- Two KW12-3 roller lever micro limit switches
- 12V motor power supply

## Limit Switch Wiring

The KW12-3 switches use:

- Terminal 1 = COM
- Terminal 3 = NO
- Terminal 2 = NC, unused for this test

Open limit switch:

- Terminal 1 / COM → ESP32 GND
- Terminal 3 / NO → ESP32 GPIO 32

Closed limit switch:

- Terminal 1 / COM → ESP32 GND
- Terminal 3 / NO → ESP32 GPIO 33

The code uses `INPUT_PULLUP`, so:

- Not pressed = HIGH
- Pressed = LOW

## Commands Tested

- `testlimits`
- `speedslow`
- `openlimit`
- `closelimit`
- `stop`

## Test Results

Open limit test:

```text
Received command: openlimit
Moving OPEN until open limit is pressed...
Stopped: open limit reached.