# lab_supply

## Overview

Arduino code to control the display of measured and setpoint current and voltage to an LCD as part of my bench power supply

- 4 analog input chanels are used to monitor the 4 signals (measured and setpoint current and voltage)
- The values are output to a 20x4 charcter LCD display
- There is a separate calibrate mode which displays the raw measured voltages at each pin
- The actual voltage and current must be measured on a multimeter and divided by the display values to get the calibration factors.
