# LCDMenuLib3

LCDMenuLib3 is an Arduino menu library for building clear, structured menus on character LCDs, OLED displays, TFT screens, and Serial Monitor based interfaces.

It keeps the familiar LCDMenuLib2 menu tree, callback, and navigation model, then adds ready-to-use editors, dialogs, setup flows, status helpers, diagnostics, and persistence helpers for modern Arduino, ESP8266, and ESP32 projects.

## What You Can Build

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

## Display And Board Support

LCDMenuLib3 is designed to stay portable. The widget classes store state, validate values, and format text; your sketch decides how to draw the result on the selected display.

Typical targets include:

- Arduino Uno/Nano/Mega with 16x2 or 20x4 LCD displays.
- I2C LCD backpacks using `LiquidCrystal_I2C`.
- OLED and TFT displays using `Adafruit_GFX`.
- ESP8266 and ESP32 projects with WiFi, Bluetooth, BLE, Preferences, OTA, and SD card features.
- Serial Monitor demos for quick testing without extra hardware.

## Included Examples

Open the examples from the Arduino IDE or compile them with `arduino-cli`.

- `LCDML3_000_serial_helpers`: core LCDMenuLib3 helper methods.
- `LCDML3_010_dynamic_widgets`: time, timer, date, radio list, checklist, and state buttons.
- `LCDML3_020_advanced_widgets`: numeric/float editors, IP, WiFi, Bluetooth, headers, themes, status bar, dialogs, PIN, progress, wizard, and settings.
- `LCDML3_030_serial_all_widgets`: all widgets together in a Serial Monitor dashboard.
- `LCDML3_031_lcd_20x4_widgets`: character LCD oriented widget display.
- `LCDML3_032_gfx_oled_widgets`: Adafruit_GFX/OLED style rendering.
- `LCDML3_033_esp_network_widgets`: ESP network/Bluetooth/OTA oriented menu state.
- `LCDML3_034_diagnostic_storage_widgets`: diagnostics, logs, storage, SD file menu, actions, and calibration helpers.

## Documentation

- `CODE_REFERENCE.md`: detailed API reference with practical examples.
- `widgets_exemples.md`: ASCII/Markdown 128x64 screen mockups for the widget layouts.
- `CHANGELOG.md`: release notes and feature additions.

## Installation

Copy the `LCDMenuLib3` folder into your Arduino libraries directory:

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

## Credits

LCDMenuLib3 is derived from LCDMenuLib2 by Nils Feldkaemper.

Original project: https://github.com/Jomelo/LCDMenuLib2

All original LCDMenuLib2 MIT license notices are preserved. LCDMenuLib3 builds on that foundation with additional widgets, helpers, examples, and documentation.

## License

MIT license, following the original LCDMenuLib2 licensing model.
