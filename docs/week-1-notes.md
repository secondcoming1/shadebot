# Week 1 Notes

## What We Built

- Set up VS Code and PlatformIO
- Created an ESP32 firmware project
- Uploaded firmware to the ESP32
- Opened the serial monitor
- Built a serial command interface
- Tested open, close, stop, and status commands

## Commands Tested

open
close
stop
status

## What We Learned

- How the Mac communicates with ESP32 over USB serial
- How to upload firmware
- How to use Serial.begin()
- How to read serial input
- How to process command strings
- Why baud rate matters
- Why bootloader garbage can appear in the serial monitor
- Why keyboard echo may need to be enabled

## Problems Encountered

- Serial monitor initially showed garbage because baud rate did not match
- Keyboard input was not echoed in the terminal
- readStringUntil() processed partial commands when typing slowly
- Fixed command handling by reading characters one at a time

## Next Goal

Connect the TMC2209 stepper driver and NEMA 17 motor, then map serial commands to motor movement.