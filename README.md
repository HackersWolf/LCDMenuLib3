<div align="center">

# LCDMenuLib3

### Modern Arduino Menu Framework for LCD, OLED, TFT & Serial Interfaces

> Extended and modernized version of LCDMenuLib2 for Arduino, ESP8266 and ESP32 projects.

<br>

![Arduino](https://img.shields.io/badge/Arduino-Compatible-00979D?style=flat-square&logo=arduino)
![ESP32](https://img.shields.io/badge/ESP32-Supported-E7352C?style=flat-square&logo=espressif)
![ESP8266](https://img.shields.io/badge/ESP8266-Supported-808080?style=flat-square&logo=esphome)
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)
![Status](https://img.shields.io/badge/Status-WIP-orange?style=flat-square)

</div>

---

LCDMenuLib3 is an Arduino menu library for building clear, structured menus on character LCDs, OLED displays, TFT screens, and Serial Monitor based interfaces.

It keeps the familiar LCDMenuLib2 menu tree, callback, and navigation model, then adds ready-to-use editors, dialogs, setup flows, status helpers, diagnostics, and persistence helpers for modern Arduino, ESP8266, and ESP32 projects.

# Features

### Menu System

- Hierarchical menus
- Dynamic & static entries
- Callback-driven architecture
- Windowed lists
- Lightweight embedded design

### Widgets

- Numeric & float editors
- Time & date setup
- Timer editors
- Radio lists
- Multi-choice checklists
- ON/OFF & AUTO/MANUAL controls
- Progress bars
- Confirmation dialogs
- PIN/password entry

### Connectivity

- WiFi setup screens
- IP address editors
- Bluetooth/BLE helpers
- OTA status pages
- ESP32 Preferences support

### Diagnostics

- GPIO monitor
- I2C scanner
- WiFi scanner
- Heap & uptime monitor
- Log viewer
- Sparkline graphs

### Persistence

- EEPROM
- ESP32 Preferences
- SD card
- Custom storage callbacks

# Supported Hardware

### Boards

- Arduino Uno / Nano / Mega
- ESP8266
- ESP32

### Displays

- 16x2 / 20x4 LCD
- GLCD 32x64/64x64/128x64...
- I2C LCD backpacks
- OLED displays
- TFT displays
- Serial Monitor interfaces

# Supported Libraries

- `LiquidCrystal`
- `LiquidCrystal_I2C`
- `Adafruit_GFX`

# Included Examples

Open the examples from the Arduino IDE or compile them with `arduino-cli`.

Some examples are not complete/functioning yet — I’m still working on them 🙂

- `LCDML3_000_serial_helpers`: core LCDMenuLib3 helper methods.
- `LCDML3_010_dynamic_widgets`: time, timer, date, radio list, checklist, and state buttons.
- `LCDML3_020_advanced_widgets`: numeric/float editors, IP, WiFi, Bluetooth, headers, themes, status bar, dialogs, PIN, progress, wizard, and settings.
- `LCDML3_030_serial_all_widgets`: all widgets together in a Serial Monitor dashboard.
- `LCDML3_031_lcd_20x4_widgets`: character LCD oriented widget display.
- `LCDML3_032_gfx_oled_widgets`: Adafruit_GFX/OLED style rendering.
- `LCDML3_033_esp_network_widgets`: ESP network/Bluetooth/OTA oriented menu state.
- `LCDML3_034_diagnostic_storage_widgets`: diagnostics, logs, storage, SD file menu, actions, and calibration helpers.

# Documentation

- `CODE_REFERENCE.md`: detailed API reference with practical examples.
- `widgets_exemples.md`: ASCII/Markdown 128x64 screen mockups for the widget layouts.
- `CHANGELOG.md`: release notes and feature additions.

# What You Can Build

- Hierarchical menus with static or dynamic entries.
- Time, timer, and date setup screens.
- Windowed radio lists and multi-choice checklists.
- ON/OFF, MANUAL/AUTO, and OFF/AUTO/ON controls.
- Numeric and float editors for temperature, PWM, speed, brightness, volume, PID values, calibration factors, and setpoints.
- IP address and WiFi credential setup screens for connected projects.
- Bluetooth and BLE flow menus for discover, search, pair, connect, and disconnect operations.
- Headers, status bars, WiFi/Bluetooth/SD/lock/warning icons, and theme presets.
- Confirmation dialogs, PIN/password entry, progress screens, and multi-step setup wizards.
- Debug and diagnostic pages for GPIO, serial messages, I2C scans, WiFi scans, heap, and uptime.
- Sparkline graphs, log viewers, alarm schedules, unit selectors, OTA status pages, SD file browser state, and action menus.
- Persistent settings through EEPROM, ESP32 Preferences, SD card, or custom storage callbacks.

# Installation

- Download the library `LCDMenuLib3-main.zip` from the GitHub repository.
- Open the Arduino IDE.
- Go to Sketch > Include Library > Add .ZIP Library.
- Select the downloaded `LCDMenuLib3-main.zip` file and click Open.

OR

- Download the library `LCDMenuLib3-main.zip` from the GitHub repository and unzip.
- Copy the `LCDMenuLib3` folder into your Arduino libraries directory:

```text
Documents/Arduino/libraries/LCDMenuLib3
```

Then restart the Arduino IDE and include the library:

```cpp
#include <LCDMenuLib3.h>
```

For dynamic widgets:

```cpp
#include <LCDMenuLib3_widgets.h>
```

For the recovered Adafruit_GFX date/time helpers:

```cpp
#include <LCDMenuLib3_DateTime.h>
```

# Credits

LCDMenuLib3 is derived from LCDMenuLib2 by Nils Feldkaemper.

Original project: https://github.com/Jomelo/LCDMenuLib2

All original LCDMenuLib2 MIT license notices are preserved. LCDMenuLib3 builds on that foundation with additional widgets, helpers, examples, and documentation.

# License

MIT license, following the original LCDMenuLib2 licensing model.

---

<div align="center">

### LCDMenuLib3 — Modern Embedded UI Framework

Built for Arduino, ESP8266 & ESP32.

</div>
