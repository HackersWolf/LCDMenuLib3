# LCDMenuLib3

LCDMenuLib3 is a new Arduino menu library based on the MIT-licensed LCDMenuLib2 codebase.
It keeps the familiar LCDML menu macros and examples, while adding helper functions that make projects easier to inspect, control, and debug.

Full API reference: `CODE_REFERENCE_LCDMenuLib3.md`.

## Credits

LCDMenuLib3 is derived from LCDMenuLib2 by Nils Feldkaemper. The original project is available at https://github.com/Jomelo/LCDMenuLib2.

All original LCDMenuLib2 MIT license notices are preserved. LCDMenuLib3 adds new helper APIs, dynamic widgets, examples, and documentation on top of that foundation.

## What is new in LCDMenuLib3

- Version helper: `VERSION_get()`.
- Menu state helpers: `MENU_isAtRoot()`, `MENU_isFunctionActive()`, `MENU_hasChildren()`.
- Menu ID helpers: `MENU_getCurrentElementID()`, `MENU_getDisplayedElementID()`, `MENU_getLastElementID()`.
- Runtime display-row helpers: `MENU_getWindowRows()`, `MENU_setWindowRows(rows)`.
- Button helpers: `BT_press(button)`, `BT_release(button)`, `BT_releaseAll()`, `BT_isPressed(button)`, `BT_anyPressed()`.
- Custom event helpers: `CE_trigger(event)`, `CE_clear(event)`, `CE_clearAll()`, `CE_isTriggered(event)`, `CE_anyTriggered()`, `CE_countTriggered()`.
- Function parameter helpers: `FUNC_getParam()`, `FUNC_getPreviousParam()`.
- Screensaver helpers: `SCREEN_isEnabled()`, `SCREEN_getTimeout()`, `SCREEN_setTimeout(timeoutMs)`.
- Dynamic widget helpers:
  - `LCDML3_TimeEditor` for hour editing, with optional seconds.
  - `LCDML3_TimerEditor` for countdown/timer values up to 99:59:59.
  - `LCDML3_DateEditor` for day/month/year editing with leap-year support.
  - `LCDML3_RadioList` for windowed radio-style lists.
  - `LCDML3_CheckList` for windowed multi-choice checkbox lists, stored as a 64-bit mask.
  - `LCDML3_StateButton` for ON/OFF, MANUAL/AUTO, and OFF/AUTO/ON style buttons.
- Recovered manual LCDML3 DateTime/GFX helpers from the existing Arduino library:
  - `LCDML3::Context` and `LCDML3::RenderConfig`.
  - `LCDML3::handleTime()` / `LCDML3::handleDate()` for button-driven editing.
  - `LCDML3::drawTime()` / `LCDML3::drawDate()` for `Adafruit_GFX`.
  - `LCDML3::handleAndDrawTime()` / `LCDML3::handleAndDrawDate()` for one-call edit-and-render flows.
  - `LCDML3::formatHHMM()`, `formatDateDDMMYY()`, `formatDateDDMMYYYY()`, `daysInMonth()`, and `clampDate()`.
- Advanced widgets:
  - `LCDML3_NumericEditor` for integer values with min, max, step, and optional wrap.
  - `LCDML3_FloatEditor` for calibration, PID, and decimal setpoints.
  - `LCDML3_IPAddressEditor` and `LCDML3_WiFiMenu` for ESP32/ESP8266 network setup.
  - `LCDML3_BluetoothMenu` for discover, search, BLE scan, pair, connect, and disconnect flows.
  - `LCDML3_MenuHeader`, `LCDML3_Theme`, and `LCDML3_StatusBar` for headers, skins, and WiFi/BT/status icons.
  - `LCDML3_DebugMenu` for GPIO read/write and serial debug helpers.
  - `LCDML3_ConfirmDialog`, `LCDML3_PinEditor`, `LCDML3_ProgressScreen`, and `LCDML3_Wizard`.
  - `LCDML3_SettingsAdapter` for EEPROM, ESP32 Preferences, SD, or any storage using read/write callbacks.
- System and utility widgets:
  - `LCDML3_RotaryEncoderHelper` for encoder acceleration.
  - `LCDML3_TouchMenu` for touchscreen hitboxes.
  - `LCDML3_Sparkline` for compact sensor graphs.
  - `LCDML3_LogViewer` for filtered INFO/WARN/ERROR logs.
  - `LCDML3_AlarmScheduler` for daily/weekly scheduled actions.
  - `LCDML3_UnitSelector` for metric/imperial or custom units.
  - `LCDML3_OTAStatus` for update state/progress.
  - `LCDML3_CalibrationWizard` for two-point sensor calibration.
  - `LCDML3_ActionMenu` for GPIO, MQTT, HTTP, serial, or user actions.
  - `LCDML3_SDFileMenu` for file-list navigation.
  - `LCDML3_DiagnosticMenu` for I2C/WiFi/heap/uptime summaries.

## Dynamic Widget Example

Open `examples/LCDML3_010_dynamic_widgets` in the Arduino IDE.
It demonstrates these controls in the Serial Monitor:

- `u` / `d`: increment/decrement fields and move list cursors.
- `l` / `r`: previous/next field or state.
- `e`: select the current radio entry and toggle the current checkbox.
- `q`: show help.

## Recovered DateTime/GFX Helpers

These functions come from the manually patched LCDML3 version already present in your Arduino libraries folder.
They require `Adafruit_GFX`.

```cpp
#include <LCDMenuLib3.h>

static LCDML3::Context ctx;

LCDML3::RenderConfig cfg;
cfg.x = 0;
cfg.y = 16;
cfg.w = 128;
cfg.h = 8;
cfg.labelAlign = LCDML3::ALIGN_LEFT;
cfg.valueAlign = LCDML3::ALIGN_RIGHT;

LCDML3::handleAndDrawTime(display, ctx, LCDML, line, cfg, "LIGHT ON", hourValue, minuteValue);
```

## Proposed Next Widgets

- Rotary encoder acceleration helper.
- Touchscreen hitbox/menu adapter for XPT2046 or capacitive touch controllers.
- Graph/sparkline widget for sensor history.
- Log viewer with scrolling and severity filter.
- Alarm/scheduler editor for daily or weekly actions.
- Unit selector for metric/imperial and localized date/time formats.
- OTA update progress/status screen for ESP32/ESP8266.
- Sensor calibration wizard with save/restore defaults.
- Macro/action menu for binding menu entries to GPIO, HTTP, MQTT, or serial commands.
- Theme presets for character LCD, OLED monochrome, TFT dark, TFT light, and high contrast.

## Compatibility

Existing LCDMenuLib2 sketches can usually be migrated by replacing:

```cpp
#include <LCDMenuLib2.h>
LCDMenuLib2 LCDML(...);
```

with:

```cpp
#include <LCDMenuLib3.h>
LCDMenuLib3 LCDML(...);
```

The classic macros such as `LCDML_add`, `LCDML_setup`, `BT_enter`, `BT_up`, `CE_set`, and `CE_reset` are still available.

## Install

Copy the `LCDMenuLib3` folder into your Arduino libraries folder, for example:

```powershell
Copy-Item -Recurse "C:\path\to\LCDMenuLib3" "$env:USERPROFILE\Documents\Arduino\libraries\LCDMenuLib3"
```

Restart the Arduino IDE after copying the library.

## Compile Example

With Arduino CLI:

```powershell
arduino-cli compile --fqbn arduino:avr:uno --libraries "C:\path\to" "C:\path\to\LCDMenuLib3\examples\00_beginners\LCDML_000_serialMonitor"
```

## License

LCDMenuLib3 keeps the MIT license from LCDMenuLib2. See `LICENSE`.
