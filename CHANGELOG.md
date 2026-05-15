# Changelog

All notable LCDMenuLib3 changes are documented here.

## 3.0.0 - 2026-05-15

### Added

- LCDMenuLib3 library identity derived from LCDMenuLib2, with renamed source files, headers, examples, metadata, and keywords.
- Helper methods for menu state, current/displayed menu IDs, display row count, button state, custom events, function parameters, screensaver settings, and library version.
- Dynamic time editor with optional seconds.
- Dynamic timer editor with conversion to/from seconds.
- Date editor with leap-year handling and day/month normalization.
- Windowed radio list helper.
- Windowed multi-choice checklist helper using a 64-bit mask.
- State button helper for ON/OFF, MANUAL/AUTO, and OFF/AUTO/ON style controls.
- Numeric editor with min/max/step/wrap support for temperature, speed, PWM, brightness, volume, and setpoints.
- Float editor with configurable precision for calibration values, decimal setpoints, and PID tuning.
- Text editor for SSID, password, labels, and compact text input.
- IP address editor for four-octet network setup.
- WiFi credential and connection state menu helper for ESP8266/ESP32 projects.
- Bluetooth/BLE menu helper for discover, search, scan, pair, connect, and disconnect flows.
- Menu header helper for title, subtitle, and nesting level display.
- Theme helper with colors, symbols, and preset skins.
- Status bar helper with WiFi, Bluetooth, BLE, SD, lock, warning, busy, and custom icon flags.
- Debug menu helper for GPIO read/write state and serial debug text.
- Confirm dialog with `Cancel` / `OK` result handling.
- PIN/password editor with masked formatting and comparison helper.
- Progress screen helper for determinate and indeterminate long operations.
- Wizard flow helper for multi-step setup menus.
- Persistent settings adapter with byte, int32, float, block read/write, and commit callbacks for EEPROM, ESP32 Preferences, SD, FRAM, or custom storage.
- Rotary encoder helper with acceleration.
- Touch menu hitbox mapper.
- Sparkline history helper for compact sensor graphs.
- Log viewer with INFO/WARN/ERROR filtering.
- Alarm scheduler with day masks.
- Unit selector for metric/imperial or custom units.
- OTA status helper for check, download, flash, done, and error states.
- Calibration wizard for raw/reference point capture and corrected output.
- Action menu callback dispatcher for GPIO, MQTT, HTTP, serial, or user-defined commands.
- SD file menu state helper for windowed file lists.
- Diagnostic menu formatter for I2C count, WiFi count, heap, and uptime.
- Recovered `LCDML3::` DateTime/Adafruit_GFX helpers from the existing local LCDML3 work, including edit handlers, draw helpers, combined handle-and-draw functions, formatting helpers, and date normalization helpers.

### Examples

- Added `LCDML3_000_serial_helpers`.
- Added `LCDML3_010_dynamic_widgets`.
- Added `LCDML3_020_advanced_widgets`.
- Added `LCDML3_030_serial_all_widgets`.
- Added `LCDML3_031_lcd_20x4_widgets`.
- Added `LCDML3_032_gfx_oled_widgets`.
- Added `LCDML3_033_esp_network_widgets`.
- Added `LCDML3_034_diagnostic_storage_widgets`.

### Documentation

- Added detailed `CODE_REFERENCE_LCDMenuLib3.md` with original LCDMenuLib style usage plus LCDMenuLib3 helper APIs and widget examples.
- Added `widgets_exemples.md` with ASCII/Markdown 128x64 screen mockups for widget presentation and layout planning.
- Reworked `README.md` as a public feature presentation.
- Added this changelog for feature history.
- Preserved credit to Nils Feldkaemper and the original LCDMenuLib2 project.

### Verification

- Compiled the included examples for `arduino:avr:uno` with `arduino-cli`.
- Kept ESP-specific WiFi/Bluetooth/OTA usage behind sketch-level integration so the core widgets remain portable on AVR boards.
