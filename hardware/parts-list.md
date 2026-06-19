# ShadeBot Prototype Parts List

This document lists the parts needed for the first ShadeBot bench prototype.

The purpose of this prototype is to connect an ESP32 microcontroller to a TMC2209 stepper motor driver and control a NEMA 17 stepper motor using serial commands.

## Prototype Goal

The first hardware milestone is:

```text
Serial command → ESP32 GPIO pins → TMC2209 driver → NEMA 17 motor movement
```

The prototype will support these basic commands:

```text
open
close
stop
status
```

At this stage, the motor will sit on the bench. It will not be connected to the real patio-door shade yet.

---

## Core Electronics

| Part | Quantity | Purpose | Notes |
|---|---:|---|---|
| ESP32 development board | 1 | Main microcontroller | Receives commands and sends STEP / DIR signals |
| TMC2209 stepper motor driver | 1 | Drives the stepper motor | Use STEP / DIR mode first; UART can come later |
| NEMA 17 stepper motor | 1 | Prototype motor | 4-wire bipolar motor, approximately 1.5A–1.7A |
| 12V power supply | 1 | Motor power | Use 12V 3A–5A for bench testing |
| USB cable | 1 | ESP32 programming and serial communication | Must be a data cable, not charge-only |
| 100uF or 220uF electrolytic capacitor | 1 | Protects motor power input | Rated at least 25V; place near driver VMOT/GND |
| Breadboard or prototyping board | 1 | Temporary wiring | Screw-terminal breakout is preferred if available |
| Jumper wires | Several | Signal wiring | Male-to-female and male-to-male as needed |

---

## Safety and Control Parts

| Part | Quantity | Purpose | Notes |
|---|---:|---|---|
| Limit switch | 2 | Future open/closed position detection | Not required for first spin test |
| Emergency stop button | 1 | Future safety control | Recommended before attaching to shade |
| Inline fuse holder | 1 | Motor power protection | Optional for bench, recommended for final build |
| Small project box | 1 | Electronics enclosure | For later cleanup |
| Cable glands / strain relief | Several | Wire protection | Useful when moving from bench to mounted prototype |

---

## Mechanical Prototype Parts

| Part | Quantity | Purpose | Notes |
|---|---:|---|---|
| 5mm shaft coupler | 1 | Connects motor shaft to spool/tube | Most NEMA 17 motors use a 5mm shaft |
| Small spool, pulley, or tube | 1 | Simulates the shade roller | Can be 3D printed, wood, PVC, or a small tube |
| Plywood base or mounting plate | 1 | Holds motor during bench test | Keeps the motor from moving on the table |
| NEMA 17 mounting bracket | 1 | Secures the motor | Metal bracket preferred |
| Screws / standoffs | Several | Mounting | Match motor/bracket holes |

---

## Current Parts on Hand

| Part | Status |
|---|---|
| ESP32 development board | Available |
| TMC2209 stepper motor driver | Available |
| NEMA 17 stepper motor | Available |

---

## Required Before Motor Test

Before connecting power to the motor driver, confirm:

```text
[ ] ESP32 firmware uploads successfully
[ ] Serial monitor works at 115200 baud
[ ] open / close / stop / status commands work
[ ] 12V power supply polarity is verified
[ ] ESP32 GND and TMC2209 GND are connected together
[ ] Capacitor is connected across VMOT and GND
[ ] Motor coil pairs are identified
[ ] Motor is not connected or disconnected while driver is powered
```

---

## Notes for Bo

The ESP32 cannot power the stepper motor directly.

The ESP32 only sends small control signals:

```text
STEP
DIR
ENABLE
```

The TMC2209 uses separate motor power to drive the NEMA 17.

This separation is important in embedded systems:

```text
Logic power controls decisions.
Motor power drives physical movement.
```
