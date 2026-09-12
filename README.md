# ESP32 Dual-OLED Chess Clock

[Insert link to GIF or photo here]

A standalone digital chess clock built using an ESP32, two OLED displays, and arcade microswitches to manage exact match timing.

## Features & Game Logic
* **Independent Displays:** Uses the U8g2 SW I2C implementation to run two 0.96" OLEDs that share the same default hardware address.
* **Turn Management:** Pressing the active player's button pauses their timer and instantly starts the opponent's timer.
* **Time Control:** Standard base time countdown.
* **Timeout Condition:** If a timer reaches zero, the display flags "Out of Time". This results in a loss on time, subject to standard chess rules regarding insufficient material.
* **Internal Pull-ups:** Uses the ESP32's internal pull-up resistors (`INPUT_PULLUP`) for the arcade buttons, removing the need for external resistors.

## Hardware & Engineering
* 1x ESP32 Development Board
* 2x SSD1306 0.96" I2C OLED Displays
* 2x Arcade Buttons with Microswitches
* Female-to-Female Jumper Wires
* Custom 3D Printed Enclosure

**Hardware Fix:** Encountered unreliable physical pin contact on the lower ESP32 header. Solved the intermittent signal issue by bypassing loose contact points using female-to-female jumper wire connections, ensuring stable operation during fast physical button presses.

## Wiring Configuration

| Component | ESP32 Pin | Note |
| :--- | :--- | :--- |
| Screen 1 | SDA = 21, SCL = 22 | Powered via 3.3V / GND |
| Screen 2 | SDA = 32, SCL = 33 | Powered via 3.3V / GND |
| Button 1 | Pin 14 | Connect NO to Pin 14, COM to GND |
| Button 2 | Pin 27 | Connect NO to Pin 27, COM to GND |

## Build Instructions
1. Clone this repository.
2. Open the project folder in Visual Studio Code with the **PlatformIO** extension installed.
3. The OLED displays require the `U8g2` library.
4. Connect the ESP32 via USB-C.
5. Click the **Upload** button (the right-pointing arrow `→`) on the bottom PlatformIO status bar to compile and flash the board.
6. Press either arcade button to start the timers.
