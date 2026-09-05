# ESP32 Dual-OLED Chess Clock ♟️🕒

![Demo GIF Placeholder](link-to-your-gif-here.gif) *(Tip: Replace this line with a link to a short GIF of the clock working!)*

A dual-screen, competitive chess clock built from scratch using an ESP32, two OLED displays, and arcade microswitches. Designed to bypass hardware I2C limitations by implementing Software I2C to drive multiple identical displays simultaneously without addressing conflicts.

## Features
- **Dual Independent Displays**: Uses the U8g2 SW I2C implementation to run two `0.96"` OLEDs that share the same default hardware address.
- **Dramatic Sub-Minute UI**: Timers automatically switch from `MM:SS` to `SS.d` (tenths of a second) when a player drops under 1 minute for high-pressure endgames.
- **Active Turn Indicators**: Dynamically displays whose turn it is.
- **Internal Hardware Pull-ups**: Uses the ESP32's internal pull-up resistors (`INPUT_PULLUP`) for clean, responsive arcade button presses without needing external resistors.

## Hardware Required
- 1x ESP32 Development Board
- 2x SSD1306 0.96" I2C OLED Displays (or SH1106 1.3")
- 2x Arcade Buttons with Microswitches
- Female-to-Female Jumper Wires
- *(Optional: 3D Printed Enclosure - CAD files coming soon!)*

## Wiring & Pinout
| Component | ESP32 Pin | Note |
| :--- | :--- | :--- |
| **Screen 1 (Player 1)** | `SDA = 21`, `SCL = 22` | Powered via 3.3V / GND |
| **Screen 2 (Player 2)** | `SDA = 32`, `SCL = 33` | Powered via 3.3V / GND |
| **Button 1 (Player 1)** | `Pin 14` | Connect `NO` to Pin 14, `COM` to GND |
| **Button 2 (Player 2)** | `Pin 27` | Connect `NO` to Pin 27, `COM` to GND |

## Software & Libraries
This project is built using [PlatformIO](https://platformio.org/).
- **Framework:** Arduino
- **Libraries:** [`olikraus/U8g2`](https://github.com/olikraus/u8g2) (For driving the OLED displays)

## How to Build & Flash
1. Clone this repository.
2. Open the project folder in VS Code with the PlatformIO extension installed.
3. Build the project and upload it to your ESP32.
4. Press either arcade button to start the timers!

