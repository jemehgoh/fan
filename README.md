# fan

A program for a fan with multiple speed settings using a STM32F303RE.

## Overview

The fan built in this project has four separate speed modes, namely:

* Zero speed (fan is stopped)
* Half speed
* Full speed
* Variable speed

These modes can be switched to by the user through a set of buttons, with each button corresponding to a mode stated above.

In addition, in variable speed mode, the speed of the fan can be varied by the user using a potentiometer.

## Hardware and firmware

### Fan speed controls

The buttons used for switching between modes are active-high buttons with 10 kilo-ohm pull-down resistors. These buttons are connected to pins PC1-PC4 on the Nucleo board.

Each of the pins PC1-PC4 is then connected to an interrupt line, which is asserted when the corresponding button is pressed.








