# ShadeBot Prototype Wiring Diagram

This document describes the first bench wiring plan for connecting the ESP32, TMC2209 stepper driver, and NEMA 17 stepper motor.

The goal is to safely test motor movement before connecting anything to the real patio-door shade.

---

## System Overview

```text
Mac / VS Code
     |
     | USB
     v
ESP32
     |
     | STEP / DIR / ENABLE
     v
TMC2209 Stepper Driver
     |
     | Motor coil outputs
     v
NEMA 17 Stepper Motor
```

Motor power is separate:

```text
12V Power Supply → TMC2209 → NEMA 17 Motor
```

The ESP32 is powered by USB during development.

---

## Important Safety Rule

Do not power the motor from the ESP32.

The ESP32 controls the driver. The 12V power supply powers the motor.

Also:

```text
Never plug or unplug the motor while the TMC2209 is powered.
```

Turn off 12V power first.

---

## ESP32 to TMC2209 Signal Wiring

Suggested first-test pin assignment:

| ESP32 Pin | TMC2209 Pin | Purpose |
|---|---|---|
| 3V3 | VIO / VCC_IO | Logic voltage for driver |
| GND | GND | Common ground |
| GPIO 26 | STEP / STP | Step pulse signal |
| GPIO 27 | DIR | Motor direction signal |
| GPIO 25 | EN / ENABLE | Driver enable signal |

Notes:

```text
STEP may be labeled STP.
ENABLE may be labeled EN.
VIO may be labeled VCC_IO, 3.3V, or logic VCC.
```

Use the labels printed on the actual TMC2209 board.

---

## Motor Power Wiring

| 12V Power Supply | TMC2209 Pin | Purpose |
|---|---|---|
| 12V positive | VM / VMOT | Motor supply voltage |
| 12V negative | GND | Motor power ground |

The ESP32 and TMC2209 must share ground:

```text
ESP32 GND → TMC2209 GND → 12V power supply negative
```

---

## Capacitor Placement

Place a capacitor across the motor power input near the TMC2209:

| Capacitor Lead | Connects To |
|---|---|
| Positive lead | VM / VMOT / 12V positive |
| Negative lead | GND / 12V negative |

Recommended capacitor:

```text
100uF or 220uF electrolytic capacitor
25V rating or higher
```

Observe polarity. Electrolytic capacitors are polarized.

---

## Motor Coil Wiring

The NEMA 17 motor has four wires. These are two separate coils.

The TMC2209 motor outputs are usually labeled:

```text
A1
A2
B1
B2
```

or:

```text
1A
1B
2A
2B
```

One coil connects to the A pair. The other coil connects to the B pair.

Example:

| Motor Coil | TMC2209 Output |
|---|---|
| Coil 1 wire 1 | A1 |
| Coil 1 wire 2 | A2 |
| Coil 2 wire 1 | B1 |
| Coil 2 wire 2 | B2 |

Do not guess the coil pairs. Identify them first.

---

## How to Identify Motor Coil Pairs

Use a multimeter in resistance mode.

A pair of wires that shows low resistance belongs to the same coil.

Example:

```text
Red + Blue = Coil 1
Green + Black = Coil 2
```

Then wire:

```text
Red   → A1
Blue  → A2
Green → B1
Black → B2
```

Actual colors may vary by motor.

If the motor only vibrates or buzzes, the coil pairs may be wired incorrectly.

---

## Full Bench Wiring Diagram

```text
ESP32                         TMC2209                         NEMA 17
-----                         -------                         -------
3V3      ------------------>  VIO / VCC_IO

GND      ------------------>  GND  <----------------------  12V -

GPIO 26 ------------------>   STEP / STP

GPIO 27 ------------------>   DIR

GPIO 25 ------------------>   EN / ENABLE

12V +   ------------------>   VM / VMOT

A1      ----------------------------------------------->  Coil 1 wire 1
A2      ----------------------------------------------->  Coil 1 wire 2

B1      ----------------------------------------------->  Coil 2 wire 1
B2      ----------------------------------------------->  Coil 2 wire 2
```

Capacitor:

```text
Capacitor positive → VM / VMOT
Capacitor negative → GND
```

---

## Power-Up Sequence

Use this sequence for the first test:

```text
1. Keep 12V motor power disconnected.
2. Connect ESP32 to Mac by USB.
3. Upload the firmware.
4. Open Serial Monitor.
5. Confirm serial commands work.
6. Double-check all TMC2209 wiring.
7. Connect 12V power to the TMC2209.
8. Send the status command.
9. Send the open command.
10. Confirm the motor turns.
11. Send the close command.
12. Confirm the motor turns the opposite direction.
13. Send stop.
```

---

## First Test Expectations

The first motor test should only prove that:

```text
[ ] Motor rotates forward
[ ] Motor rotates backward
[ ] Motor stops between commands
[ ] ESP32 does not reset
[ ] TMC2209 does not overheat
[ ] Motor does not overheat
```

The motor should not yet be connected to the shade.

---

## Troubleshooting

### Motor does not move

Check:

```text
[ ] 12V power is connected to VMOT and GND
[ ] ESP32 GND and TMC2209 GND are connected
[ ] ENABLE pin is in the correct state
[ ] STEP and DIR pins match the firmware
[ ] Motor coil pairs are correct
```

### Motor buzzes but does not rotate

Likely causes:

```text
[ ] Coil wires are mixed up
[ ] Current limit is too low
[ ] Step pulse timing is too fast
```

### Driver gets hot

Likely causes:

```text
[ ] Current limit is too high
[ ] Heat sink is not installed
[ ] Motor is holding position too long
```

### ESP32 resets when motor starts

Likely causes:

```text
[ ] Motor power noise
[ ] Missing capacitor
[ ] Weak power supply
[ ] Poor grounding
```

---

## Notes for Bo

The wiring demonstrates a key embedded systems pattern:

```text
Microcontroller → Driver → Actuator
```

The ESP32 does not drive the motor directly. It makes decisions and sends control signals.

The driver handles the electrical load.

The motor converts electrical energy into physical motion.


## First Motor Test Result

The NEMA 17 motor successfully moved using serial commands from the ESP32.

### Working Commands

- `enable`
- `open`
- `close`
- `stop`
- `status`

### Issue Encountered

The motor initially did not move because the power strip supplying the 12V adapter was bad. After changing the power source, the motor worked.

### Lesson Learned

When debugging embedded hardware, verify the power path before assuming the problem is in the firmware or wiring.