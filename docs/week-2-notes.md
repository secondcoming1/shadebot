# Week 2 Notes

## What We Built

- Connected ESP32 to TMC2209 stepper motor driver
- Connected NEMA 17 stepper motor
- Added 12V motor power through barrel jack adapter
- Added 220uF capacitor across VM/GND
- Verified motor coil pairs:
  - Red + Blue
  - Green + Black
- Uploaded motor test firmware
- Controlled motor from Serial Monitor
- Refactored motor control logic into a reusable `StepperMotor` C++ class

## Commands Tested

- `status`
- `enable`
- `open`
- `close`
- `stop`
- `speedslow`
- `speednormal`
- `help`

## Hardware Wiring

- ESP32 `3V3` → TMC2209 `VDD`
- ESP32 `GND` → TMC2209 `GND`
- ESP32 `D26` → TMC2209 `STP`
- ESP32 `D27` → TMC2209 `DIR`
- ESP32 `D25` → TMC2209 `EN`
- 12V positive → TMC2209 `VM`
- 12V negative → TMC2209 `GND`
- Capacitor positive → `VM`
- Capacitor negative / stripe → `GND`
- Motor red/blue → `A1/A2`
- Motor green/black → `B1/B2`

## Issue Encountered

The motor initially did not move because the power strip supplying the 12V adapter was bad.

## Lesson Learned

In embedded systems, not every failure is software. Always verify:

- Power source
- Ground
- Wiring
- Driver enable
- Motor coil pairs
- Firmware pin assignments

## Result

The motor successfully moved using serial commands from the ESP32.

The code was then refactored so that:

- `main.cpp` handles serial commands
- `StepperMotor.h` defines the motor-control interface
- `StepperMotor.cpp` handles the low-level STEP / DIR / ENABLE control

## Next Goals

- Mount the NEMA 17 motor securely
- Add limit switches
- Add emergency stop behavior
- Create a shade state machine
- Test with a spool or small shade prototype