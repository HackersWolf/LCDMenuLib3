# LCDMenuLib3 Code Reference

Reference for LCDMenuLib3 v3.0.0.

LCDMenuLib3 is based on the LCDMenuLib2 API and keeps the classic LCDML menu tree, callback, button, event, display, timer, jump, and screensaver functions. LCDMenuLib3 adds helper functions and widget classes for dynamic menus, date/time editing, numeric values, WiFi/Bluetooth flows, headers, themes, debug tools, status icons, dialogs, PIN/password entry, progress screens, setup wizards, and persistent settings.

## Contents

- Quick start
- Configuration defines
- Menu creation macros
- Main class constructor and lifecycle
- Menu navigation API
- Button and custom event API
- Display API
- Menu function API
- Timer API
- Other jump/search API
- Screensaver API
- LCDMenuLib3 helper API
- DateTime/GFX helpers
- Dynamic widgets
- Persistence helpers
- Full examples

## Quick Start

```cpp
#include <LCDMenuLib3.h>

#define _LCDML_DISP_cols 20
#define _LCDML_DISP_rows 4

LCDMenuLib3_menu LCDML_0(255, 0, 0, NULL, NULL);

void lcdml_display();
void lcdml_clear();
void lcdml_control();
void mFunc_info(uint8_t param);

LCDMenuLib3 LCDML(
  LCDML_0,
  _LCDML_DISP_rows,
  _LCDML_DISP_cols,
  lcdml_display,
  lcdml_clear,
  lcdml_control
);

LCDML_add(0, LCDML_0, 1, "Info", mFunc_info);
LCDML_createMenu(0);

void setup() {
  Serial.begin(115200);
  LCDML_setup(0);
}

void loop() {
  LCDML.loop();
}
```

## Configuration Defines

These are configured before or inside `LCDMenuLib3.h`.

```cpp
//#define _LCDML_cfg_use_ram
//#define _LCDML_plattform_io_support
//#define _LCDML_cfg_use_32bit_cpu
#define _LCDML_CE_cb_function_cnt 4
//#define LCDML_DBG 1
```

### `_LCDML_cfg_use_ram`

Stores menu text in RAM instead of PROGMEM. This is automatically enabled on ESP8266 and ESP32.

Use it when:

- dynamic text tables are easier than flash strings
- the board has enough RAM
- PROGMEM handling creates platform issues

### `_LCDML_plattform_io_support`

Adds compatibility declarations for PlatformIO projects.

### `_LCDML_cfg_use_32bit_cpu`

Uses 32-bit compatible PROGMEM pointer reads. Useful for Arduino UNO R4 and some non-AVR boards.

### `_LCDML_CE_cb_function_cnt`

Number of custom event callback slots. Default is `4`.

### Debug Defines

```cpp
#define LCDML_DBG 1
#define LCDML_DBG_function_name_LOOP 1
#define LCDML_DBG_function_name_MENU 1
#define LCDML_DBG_function_name_FUNC 1
#define LCDML_DBG_function_name_BT 1
#define LCDML_DBG_function_name_CE 1
#define LCDML_DBG_function_name_OTHER 1
#define LCDML_DBG_function_name_DISP 1
#define LCDML_DBG_function_name_TIMER 1
#define LCDML_DBG_function_name_SCREEN 1
```

Enable only the groups you need. Debug output uses `Serial.print()`.

## Core Constants

```cpp
#define _LCDML_VERSION "LCDML3 v3.0.0"
#define _LCDML_CE_events_cnt 64
#define _LCDML_NO_FUNC 255
#define _LCDML_FIRST_ELEMENT_ID 255
```

Button bit constants:

```cpp
_LCDML_REG_button_enter
_LCDML_REG_button_up
_LCDML_REG_button_down
_LCDML_REG_button_left
_LCDML_REG_button_right
_LCDML_REG_button_quit
_LCDML_REG_button_custom_1
_LCDML_REG_button_custom_2
```

Use these with LCDMenuLib3 helper methods:

```cpp
LCDML.BT_press(_LCDML_REG_button_enter);
LCDML.BT_release(_LCDML_REG_button_enter);
```

## Callback Types

```cpp
typedef void (*LCDML_FuncPtr)();
typedef void (*LCDML_FuncPtr_pu8)(uint8_t);
typedef bool (*LCDML_FuncPtr_rb)();
```

- `LCDML_FuncPtr`: no-argument callback, used for display/control/clear.
- `LCDML_FuncPtr_pu8`: menu function with a `uint8_t` parameter.
- `LCDML_FuncPtr_rb`: condition callback returning `true` or `false`.

## Menu Creation Macros

### `LCDML_add(id, parent, child, content, callback)`

Creates a normal menu entry.

```cpp
void mFunc_settings(uint8_t param);

LCDML_add(0, LCDML_0, 1, "Settings", mFunc_settings);
```

Parameters:

- `id`: numeric menu ID, from `0` to the last menu ID
- `parent`: parent menu object
- `child`: object suffix used internally
- `content`: display label
- `callback`: function called when activated

### `LCDML_addAdvanced(id, parent, child, condition, content, callback, param, settings)`

Creates a menu entry with condition, parameter, and type flags.

```cpp
bool showAdvanced() {
  return true;
}

void mFunc_advanced(uint8_t param) {
  Serial.println(param);
}

LCDML_addAdvanced(
  1,
  LCDML_0,
  2,
  showAdvanced,
  "Advanced",
  mFunc_advanced,
  42,
  _LCDML_TYPE_default
);
```

Menu item types:

```cpp
_LCDML_TYPE_default
_LCDML_TYPE_dynParam
_LCDML_TYPE_dynParam_enableSubMenus
_LCDML_TYPE_dynParam_enableCustomRefresh
```

### `LCDML_createMenu(lastId)`

Creates the language table for menu labels. `lastId` must match the last menu ID.

```cpp
LCDML_add(0, LCDML_0, 1, "Info", mFunc_info);
LCDML_add(1, LCDML_0, 2, "Settings", mFunc_settings);
LCDML_createMenu(1);
```

### `LCDML_setup(lastId)`

Initializes menu objects and calls `LCDML.init(lastId)`.

```cpp
void setup() {
  LCDML_setup(1);
}
```

### `LCDML_getContent(buffer, id)`

Copies the menu label for `id` into `buffer`.

```cpp
char text[20];
LCDML_getContent(text, 0);
Serial.println(text);
```

### `LCDML_getElementName(buffer, element_id)`

Alias for the default language table.

```cpp
char text[20];
LCDML_getElementName(text, LCDML.MENU_getElementIDFromCursorPos());
```

### Custom Language Macros

```cpp
LCDML_langDef(id, lang, content)
LCDML_createCustomLang(N, lang)
LCDML_getCustomContent(lang, buffer, id)
LCDML_getCustomElementName(lang, buffer, element_id)
```

Use these to build multiple label tables.

## Main Class

### Constructor

```cpp
LCDMenuLib3(
  LCDMenuLib3_menu &root,
  const uint8_t rows,
  const uint8_t cols,
  LCDML_FuncPtr contentUpdate,
  LCDML_FuncPtr contentClear,
  LCDML_FuncPtr menuControl
);
```

Example:

```cpp
LCDMenuLib3 LCDML(
  LCDML_0,
  4,
  20,
  lcdml_display,
  lcdml_clear,
  lcdml_control
);
```

Callbacks:

- `contentUpdate`: redraw menu/function display
- `contentClear`: clear the display
- `menuControl`: read buttons/encoder/touch/serial and set button bits

## Lifecycle

### `init(uint8_t lastElementId)`

Initializes or resets the menu engine.

```cpp
LCDML.init(5);
```

Usually called by:

```cpp
LCDML_setup(5);
```

### `loop()`

Runs control and menu logic.

```cpp
void loop() {
  LCDML.loop();
}
```

### `loop_control()`

Runs only the control callback and internal control handling.

```cpp
LCDML.loop_control();
```

### `loop_menu()`

Runs only menu update/function logic.

```cpp
LCDML.loop_menu();
```

## Menu Navigation API

### `MENU_display(uint8_t update = 0)`

Requests a display/menu update.

```cpp
LCDML.MENU_display();
```

### `MENU_goRoot()`

Returns to the root menu.

```cpp
LCDML.MENU_goRoot();
```

### `MENU_enRollover()` / `MENU_disRollover()`

Controls whether scrolling past the last item wraps to the first item.

```cpp
LCDML.MENU_enRollover();
LCDML.MENU_disRollover();
```

### `MENU_enScroll()` / `MENU_disScroll()`

Enables or disables automatic menu scrolling.

Useful when editing a field inside one menu line.

```cpp
LCDML.MENU_disScroll();
// edit value
LCDML.MENU_enScroll();
```

### `MENU_getScrollDisableStatus()`

Returns true if scrolling is disabled.

```cpp
if (LCDML.MENU_getScrollDisableStatus()) {
  Serial.println(F("Scroll locked"));
}
```

### `MENU_getLayer()`

Current menu depth.

```cpp
Serial.println(LCDML.MENU_getLayer());
```

### `MENU_getCursorPos()`

Visible row cursor position.

```cpp
if (row == LCDML.MENU_getCursorPos()) {
  Serial.print(F("> "));
}
```

### `MENU_getCursorPosAbs()`

Absolute cursor position in current layer.

### `MENU_getCursorObjPos()`

Object position of the cursor inside current menu children.

### `MENU_getChilds()`

Number of visible child entries in current layer.

```cpp
uint8_t count = LCDML.MENU_getChilds();
```

### `MENU_getParentID(uint8_t layer = 0)`

Returns parent menu ID.

```cpp
char title[20];
LCDML_getContent(title, LCDML.MENU_getParentID());
```

### `MENU_getScroll()`

Current window scroll start.

```cpp
uint8_t first = LCDML.MENU_getScroll();
```

### `MENU_getLastActiveFunctionID()`

ID of the previous active function.

### `MENU_getLastCursorPositionID()`

ID of the item where the cursor was before a function opened.

### `MENU_getElementIDFromCursorPos()`

ID of the currently selected menu element.

```cpp
uint8_t id = LCDML.MENU_getElementIDFromCursorPos();
```

## LCDMenuLib3 Menu Additions

### `MENU_getCurrentElementID()`

Returns the current menu object ID.

```cpp
uint8_t current = LCDML.MENU_getCurrentElementID();
```

### `MENU_getDisplayedElementID()`

Returns the first displayed object ID in the current window.

```cpp
uint8_t firstVisible = LCDML.MENU_getDisplayedElementID();
```

### `MENU_getLastElementID()`

Returns the last menu ID passed to `LCDML_setup()` / `init()`.

### `MENU_getWindowRows()`

Returns configured display row count.

### `MENU_setWindowRows(uint8_t rows)`

Changes display row count at runtime.

```cpp
LCDML.MENU_setWindowRows(3);
```

### `MENU_isAtRoot()`

Returns true when layer is root.

### `MENU_hasChildren()`

Returns true if the current object has children.

### `MENU_isFunctionActive()`

Returns true if a menu function is currently active.

## Dynamic Content / Condition API

### `MENU_updateAllCondetions()`

Refreshes all condition callbacks.

### `MENU_allCondetionRefresh()`

Refreshes all menu conditions.

### `MENU_setDynFunctionContentUpdate()`

Requests dynamic function content update.

### `MENU_clearDynFunctionContentUpdate()`

Clears dynamic function update request.

### `MENU_enUseDynElementsWithSubElements()` / `MENU_disUseDynElementsWithSubElements()`

Allows dynamic menu elements to behave as parent entries.

### `MENU_enRefreshAllOnButtonAction()` / `MENU_disRefreshAllOnButtonAction()`

Controls full menu refresh on button action.

### `MENU_setDynRContent()` / `MENU_clearDynRContent()` / `MENU_checkDynRContent()`

Marks and checks dynamic refreshed content state.

## Menu Object API

### `MENU_getDisplayedObj()`

Returns pointer to first displayed menu object.

```cpp
LCDMenuLib3_menu *item = LCDML.MENU_getDisplayedObj();
```

### `MENU_getCurrentObj()`

Returns pointer to current menu object.

### `MENU_getRootObj()`

Returns pointer to root menu object.

### `LCDMenuLib3_menu`

Important methods:

```cpp
LCDML_FuncPtr_pu8 getCbFunction();
void addChild(LCDMenuLib3_menu &child);
LCDMenuLib3_menu *getChild(uint8_t which);
LCDMenuLib3_menu *getSibling(uint8_t howfar);
LCDMenuLib3_menu *getParent();
uint8_t getID();
bool checkCondition();
void updateCondetion();
uint8_t getParam();
bool checkType_menu();
bool checkType_dynParam();
bool checkType_dynParam_enabledSubMenu();
bool checkType_dynParam_enabledCustomRefresh();
void callback(uint8_t param);
```

Example display loop:

```cpp
void lcdml_display() {
  if (LCDML.DISP_checkMenuUpdate() || LCDML.DISP_checkMenuCursorUpdate()) {
    char text[21];
    LCDMenuLib3_menu *tmp = LCDML.MENU_getDisplayedObj();
    uint8_t row = 0;

    while (tmp != NULL && row < LCDML.MENU_getWindowRows()) {
      if (tmp->checkCondition()) {
        Serial.print(row == LCDML.MENU_getCursorPos() ? F("> ") : F("  "));
        LCDML_getContent(text, tmp->getID());
        Serial.println(text);
        row++;
      }
      tmp = tmp->getSibling(1);
    }
  }
}
```

## Button API

Classic macros:

```cpp
BT_enter()
BT_up()
BT_down()
BT_left()
BT_right()
BT_quit()

BT_resetEnter()
BT_resetUp()
BT_resetDown()
BT_resetLeft()
BT_resetRight()
BT_resetQuit()
BT_resetAll()

BT_checkEnter()
BT_checkUp()
BT_checkDown()
BT_checkLeft()
BT_checkRight()
BT_checkQuit()
BT_checkAny()
```

Example serial control:

```cpp
void lcdml_control() {
  if (!Serial.available()) return;
  char c = Serial.read();
  if (c == 'e') LCDML.BT_enter();
  if (c == 'u') LCDML.BT_up();
  if (c == 'd') LCDML.BT_down();
  if (c == 'q') LCDML.BT_quit();
}
```

LCDMenuLib3 method helpers:

```cpp
bool BT_setup();
void BT_press(uint8_t button);
void BT_release(uint8_t button);
void BT_releaseAll();
bool BT_isPressed(uint8_t button);
bool BT_anyPressed();
```

Example:

```cpp
if (digitalRead(2) == LOW) {
  LCDML.BT_press(_LCDML_REG_button_enter);
}

if (LCDML.BT_anyPressed()) {
  Serial.println(F("Button pending"));
}
```

## Custom Event API

Classic macros:

```cpp
CE_set(event)
CE_reset(event)
CE_resetAll()
CE_check(event)
CE_checkAny()
```

Methods:

```cpp
bool CE_setup();
void CE_trigger(uint8_t event);
void CE_clear(uint8_t event);
void CE_clearAll();
bool CE_isTriggered(uint8_t event);
bool CE_anyTriggered();
uint8_t CE_countTriggered();
void CE_setOnChangeCbFunction(uint8_t event, LCDML_FuncPtr_pu8 function);
void CE_clearOnChangeCbFunction(uint8_t event);
```

Example:

```cpp
void mFunc_alarm(uint8_t param) {
  if (LCDML.FUNC_setup()) Serial.println(F("Alarm event"));
  if (LCDML.FUNC_close()) Serial.println(F("Leave alarm"));
}

void setup() {
  LCDML_setup(2);
  LCDML.CE_setOnChangeCbFunction(0, mFunc_alarm);
}

void loop() {
  if (sensorAlarm()) {
    LCDML.CE_trigger(0);
  }
  LCDML.loop();
}
```

## Register API

```cpp
void REG_set(uint8_t reg, uint8_t val);
void REG_reset(uint8_t reg, uint8_t val);
void REG_resetAll(uint8_t reg);
bool REG_check(uint8_t reg, uint8_t val);
bool REG_checkAny(uint8_t reg);
```

Registers:

```cpp
_LCDML_REG_CTRL__button
_LCDML_REG_CTRL__events
```

Prefer `BT_*` and `CE_*` helpers unless you need low-level access.

## Display API

```cpp
void DISP_update();
void DISP_menuUpdate();
void DISP_clear();
bool DISP_checkMenuUpdate();
bool DISP_checkMenuCursorUpdate();
uint8_t DISP_getMenuContentId(uint8_t n);
```

### `DISP_checkMenuUpdate()`

Use inside display callback to know when full menu content should redraw.

### `DISP_checkMenuCursorUpdate()`

Use inside display callback to redraw only cursor if supported.

### `DISP_getMenuContentId(uint8_t n)`

LCDMenuLib3 helper that returns menu ID for visible line `n`.

```cpp
for (uint8_t row = 0; row < LCDML.MENU_getWindowRows(); row++) {
  uint8_t id = LCDML.DISP_getMenuContentId(row);
  if (id < _LCDML_NO_FUNC) {
    char text[21];
    LCDML_getContent(text, id);
    Serial.println(text);
  }
}
```

## Menu Function API

```cpp
bool FUNC_setup();
bool FUNC_loop();
bool FUNC_close();
void FUNC_goBackToMenu(uint8_t goBackCnt = 0);
uint8_t FUNC_getID();
uint8_t FUNC_getParam();
uint8_t FUNC_getPreviousParam();
void FUNC_setLoopInterval(unsigned long ms);
void FUNC_disableScreensaver();
void FUNC_setGBAToLastCursorPos();
void FUNC_setGBAToLastFunc();
void FUNC_setGBA();
void FUNC_setCEMask(unsigned long mask);
```

Typical menu function:

```cpp
void mFunc_counter(uint8_t param) {
  static uint16_t count;

  if (LCDML.FUNC_setup()) {
    count = 0;
    LCDML.FUNC_setLoopInterval(500);
  }

  if (LCDML.FUNC_loop()) {
    Serial.print(F("Count: "));
    Serial.println(count++);
  }

  if (LCDML.FUNC_close()) {
    Serial.println(F("Counter closed"));
  }
}
```

### `FUNC_getParam()`

Returns active menu entry parameter.

```cpp
void mFunc_param(uint8_t param) {
  if (LCDML.FUNC_setup()) {
    Serial.println(LCDML.FUNC_getParam());
  }
}
```

### `FUNC_setLoopInterval(ms)`

Controls how often `FUNC_loop()` becomes true.

### `FUNC_goBackToMenu()`

Closes current function and returns to menu.

```cpp
if (done) {
  LCDML.FUNC_goBackToMenu();
}
```

## Timer API

```cpp
bool TIMER_ms(unsigned long &timer, unsigned long interval);
void TIMER_msReset(unsigned long &timer);
bool TIMER_us(unsigned long &timer, unsigned long interval);
void TIMER_usReset(unsigned long &timer);
```

Example:

```cpp
unsigned long blinkTimer;

void loop() {
  if (LCDML.TIMER_ms(blinkTimer, 1000)) {
    Serial.println(F("tick"));
  }
}
```

## Other / Jump API

```cpp
void OTHER_jumpToFunc(LCDML_FuncPtr_pu8 function, uint8_t param = 0);
void OTHER_jumpToID(uint8_t id, uint8_t param = 0);
void OTHER_setCursorToID(uint8_t id);
void OTHER_setCursorToFunc(LCDML_FuncPtr_pu8 function);
uint8_t OTHER_getIDFromFunction(LCDML_FuncPtr_pu8 function);
void OTHER_updateFunc();
```

Examples:

```cpp
LCDML.OTHER_jumpToID(3);
LCDML.OTHER_jumpToFunc(mFunc_settings, 7);
LCDML.OTHER_setCursorToID(1);
uint8_t id = LCDML.OTHER_getIDFromFunction(mFunc_settings);
```

## Screensaver API

```cpp
void SCREEN_enable(LCDML_FuncPtr_pu8 function, unsigned long timeoutMs);
void SCREEN_disable();
void SCREEN_resetTimer();
void SCREEN_start();
bool SCREEN_isEnabled();
unsigned long SCREEN_getTimeout();
void SCREEN_setTimeout(unsigned long timeoutMs);
```

Example:

```cpp
void mFunc_screen(uint8_t param) {
  if (LCDML.FUNC_setup()) {
    Serial.println(F("Screensaver"));
    LCDML.FUNC_setLoopInterval(1000);
  }
  if (LCDML.FUNC_loop()) {
    Serial.println(F("sleep frame"));
  }
}

void setup() {
  LCDML_setup(2);
  LCDML.SCREEN_enable(mFunc_screen, 30000);
}
```

## Version Helper

```cpp
const char *VERSION_get();
```

Example:

```cpp
Serial.println(LCDML.VERSION_get());
```

## DateTime/GFX Helpers

Namespace: `LCDML3`.

Requires:

```cpp
#include <Adafruit_GFX.h>
#include <LCDMenuLib3.h>
```

### `LCDML3::Context`

Holds edit state, cursor symbol, blink timing, key repeat timing, wrap mode, and animation frame.

```cpp
static LCDML3::Context ctx;
ctx.wrap = true;
ctx.blinkPeriod = 420;
ctx.repeatDelayMs = 380;
```

### `LCDML3::RenderConfig`

Controls drawing area and alignment for Adafruit_GFX.

```cpp
LCDML3::RenderConfig cfg;
cfg.x = 0;
cfg.y = 16;
cfg.w = 128;
cfg.h = 8;
cfg.charW = 6;
cfg.fontH = 8;
cfg.labelAlign = LCDML3::ALIGN_LEFT;
cfg.valueAlign = LCDML3::ALIGN_RIGHT;
```

### DateTime Functions

```cpp
void reset(Context& ctx, LCDMenuLib3& lcdml);
void tick(Context& ctx);
const char* cursor(const Context& ctx);

void formatHHMM(char* out, size_t outSize, uint8_t hh, uint8_t mm, bool blinkHours = false, bool blinkMinutes = false);
void formatDateDDMMYY(char* out, size_t outSize, uint8_t dd, uint8_t mm, uint16_t yy, bool blinkDay = false, bool blinkMonth = false, bool blinkYear = false);
void formatDateDDMMYYYY(char* out, size_t outSize, uint8_t dd, uint8_t mm, uint16_t yy, bool blinkDay = false, bool blinkMonth = false, bool blinkYear = false);

uint8_t daysInMonth(uint8_t month, uint16_t year);
void clampDate(uint8_t& dd, uint8_t& mm, uint16_t& yy, uint16_t minYear = 2000, uint16_t maxYear = 2099);

bool handleTime(Context& ctx, LCDMenuLib3& lcdml, uint8_t line, uint8_t& hh, uint8_t& mm);
bool handleDate(Context& ctx, LCDMenuLib3& lcdml, uint8_t line, uint8_t& dd, uint8_t& mm, uint16_t& yy, uint16_t minYear = 2000, uint16_t maxYear = 2099);

void drawAligned(Adafruit_GFX& gfx, const char* txt, int16_t x, int16_t y, int16_t w, Align align, uint8_t charW = 6);
void drawTime(Adafruit_GFX& gfx, Context& ctx, const RenderConfig& cfg, const char* label, uint8_t hh, uint8_t mm);
void drawDate(Adafruit_GFX& gfx, Context& ctx, const RenderConfig& cfg, const char* label, uint8_t dd, uint8_t mm, uint16_t yy, bool useShortYear = true);
void handleAndDrawTime(Adafruit_GFX& gfx, Context& ctx, LCDMenuLib3& lcdml, uint8_t line, const RenderConfig& cfg, const char* label, uint8_t& hh, uint8_t& mm);
void handleAndDrawDate(Adafruit_GFX& gfx, Context& ctx, LCDMenuLib3& lcdml, uint8_t line, const RenderConfig& cfg, const char* label, uint8_t& dd, uint8_t& mm, uint16_t& yy, uint16_t minYear = 2000, uint16_t maxYear = 2099, bool useShortYear = true);
```

### Time Editor With Adafruit_GFX

```cpp
static LCDML3::Context timeCtx;
uint8_t onHour = 18;
uint8_t onMinute = 30;

void drawLineTime(Adafruit_GFX &display, uint8_t line) {
  LCDML3::RenderConfig cfg;
  cfg.x = 0;
  cfg.y = 8 * (line + 1);
  cfg.w = 128;
  cfg.h = 8;
  LCDML3::handleAndDrawTime(display, timeCtx, LCDML, line, cfg, "LIGHT ON", onHour, onMinute);
}
```

### Date Editor With Adafruit_GFX

```cpp
static LCDML3::Context dateCtx;
uint8_t day = 15;
uint8_t month = 5;
uint16_t year = 2026;

void drawLineDate(Adafruit_GFX &display, uint8_t line) {
  LCDML3::RenderConfig cfg;
  cfg.x = 0;
  cfg.y = 8 * (line + 1);
  cfg.w = 128;
  LCDML3::handleAndDrawDate(display, dateCtx, LCDML, line, cfg, "DATE", day, month, year, 2020, 2099, false);
}
```

## Dynamic Widgets

These classes do not draw by themselves. They manage state and formatting. You can render them on Serial, LCD, OLED, TFT, or any display callback.

## `LCDML3_TimeEditor`

Edits a time value.

```cpp
LCDML3_TimeEditor editor;

editor.begin(12, 30, 0, true);
editor.increment();
editor.nextField();

char text[12];
editor.format(text, sizeof(text)); // "13:30:00"
```

API:

```cpp
void begin(uint8_t hour, uint8_t minute, uint8_t second = 0, bool showSeconds = true);
void nextField();
void previousField();
void increment();
void decrement();
void setValue(uint8_t hour, uint8_t minute, uint8_t second = 0);
LCDML3_Time getValue() const;
uint8_t getField() const;
void format(char *buffer, size_t size) const;
```

Fields:

- `0`: hour
- `1`: minute
- `2`: second, when seconds are enabled

## `LCDML3_TimerEditor`

Edits a duration up to 99:59:59.

```cpp
LCDML3_TimerEditor timer;
timer.begin(1, 15, 0);
timer.fromSeconds(5400);

Serial.println(timer.toSeconds());
```

## `LCDML3_DateEditor`

Edits date with month length and leap-year handling.

```cpp
LCDML3_DateEditor date;
date.begin(2026, 5, 15);
date.nextField();
date.increment();

char text[12];
date.format(text, sizeof(text)); // "15/06/2026"
```

## `LCDML3_RadioList`

Windowed single-choice list.

```cpp
const char *items[] = {"Eco", "Comfort", "Boost", "Night"};
LCDML3_RadioList radio;

radio.begin(4, 2, 0);
radio.down();
radio.selectCursor();

for (uint8_t i = radio.getWindowStart(); i < radio.getWindowStart() + radio.getVisibleRows(); i++) {
  Serial.print(radio.isSelected(i) ? F("(o) ") : F("( ) "));
  Serial.println(items[i]);
}
```

## `LCDML3_CheckList`

Windowed multi-choice list. Stores selected values in a 64-bit mask.

```cpp
LCDML3_CheckList checks;
checks.begin(6, 3, 0b000101);
checks.down();
checks.toggleCursor();

if (checks.isChecked(1)) {
  Serial.println(F("Option 1 checked"));
}
```

## `LCDML3_StateButton`

Two-state or three-state button.

```cpp
LCDML3_StateButton power;
power.begin(2, 0); // OFF/ON
power.next();

LCDML3_StateButton mode;
mode.begin(3, LCDML3_STATE_AUTO); // OFF/AUTO/ON

char label[8];
mode.label(label, sizeof(label));
```

## `LCDML3_NumericEditor`

Integer editor with min/max/step/wrap.

Good for:

- temperature
- speed
- PWM
- brightness
- volume
- setpoints

```cpp
LCDML3_NumericEditor temp;
temp.begin(21, -20, 80, 1);

if (LCDML.BT_checkUp()) {
  temp.increment();
  LCDML.BT_resetUp();
}

char text[12];
temp.format(text, sizeof(text), " C");
```

API:

```cpp
void begin(int32_t value, int32_t minValue, int32_t maxValue, int32_t stepValue = 1, bool wrapEnabled = false);
void increment();
void decrement();
void setValue(int32_t value);
void setBounds(int32_t minValue, int32_t maxValue);
void setStep(int32_t stepValue);
void setWrap(bool enabled);
int32_t getValue() const;
int32_t getMin() const;
int32_t getMax() const;
int32_t getStep() const;
void format(char *buffer, size_t size, const char *suffix = NULL) const;
```

## `LCDML3_FloatEditor`

Float editor with precision. Good for calibration and PID.

```cpp
LCDML3_FloatEditor kp;
kp.begin(1.25f, 0.0f, 10.0f, 0.05f, 2);
kp.increment();

char text[16];
kp.format(text, sizeof(text)); // "1.30"
```

## `LCDML3_IPAddressEditor`

IP editor with four fields.

```cpp
LCDML3_IPAddressEditor ip;
ip.begin(192, 168, 1, 50);
ip.nextField();
ip.increment();

uint8_t bytes[4];
ip.getBytes(bytes);
```

## `LCDML3_TextEditor`

Generic text/password editor.

```cpp
char ssid[33] = "MyWiFi";
LCDML3_TextEditor ssidEditor;
ssidEditor.begin(ssid, sizeof(ssid));
ssidEditor.nextChar();
ssidEditor.nextPosition();
```

Password mode:

```cpp
char password[65] = "";
LCDML3_TextEditor passEditor;
passEditor.begin(password, sizeof(password), NULL, true);

char masked[65];
passEditor.format(masked, sizeof(masked));
```

## `LCDML3_WiFiMenu`

State holder for WiFi setup flows. It is platform-neutral and can be connected to ESP32/ESP8266 WiFi calls from your sketch.

```cpp
LCDML3_WiFiMenu wifi;
wifi.setCredentials("router", "password");
wifi.setState(LCDML3_NET_SCAN);
wifi.setSelectedNetwork(0);

char status[24];
wifi.formatStatus(status, sizeof(status)); // "WiFi Scan #0"
```

ESP32 sketch integration:

```cpp
#if defined(ESP32) || defined(ESP8266)
#include <WiFi.h>

void startWifi(LCDML3_WiFiMenu &menu) {
  LCDML3_WiFiCredentials c = menu.getCredentials();
  menu.setState(LCDML3_NET_CONNECT);
  WiFi.begin(c.ssid, c.password);
}
#endif
```

## `LCDML3_BluetoothMenu`

State holder for Bluetooth discovery/search/BLE/pair/disconnect flows.

```cpp
LCDML3_BluetoothMenu bt;
bt.setBleMode(true);
bt.setState(LCDML3_BT_BLE_SCAN);
bt.setSelectedDevice(2);

char status[32];
bt.formatStatus(status, sizeof(status)); // "BLE BLE scan #2"
```

States:

```cpp
LCDML3_BT_IDLE
LCDML3_BT_DISCOVER
LCDML3_BT_SEARCH
LCDML3_BT_BLE_SCAN
LCDML3_BT_PAIR
LCDML3_BT_CONNECTED
LCDML3_BT_DISCONNECT
```

## `LCDML3_MenuHeader`

Stores formatted menu title/subtitle/level.

```cpp
LCDML3_MenuHeader header;
header.begin("Settings", "Network", 2);

char line[32];
header.format(line, sizeof(line));
```

## `LCDML3_Theme`

Stores colors and UI symbols.

```cpp
LCDML3_Theme theme;
theme.setColors(0xFFFF, 0x0000, 0x07E0, 0xF800);
theme.setSymbols(">", "[x]", "[ ]", "(o)", "( )");

Serial.print(theme.cursorSymbol());
```

## `LCDML3_DebugMenu`

GPIO and Serial debug helper.

```cpp
LCDML3_DebugMenu dbg;
dbg.begin(13);
dbg.modeOutput();
dbg.write(true);

char line[32];
dbg.formatPin(line, sizeof(line));
Serial.println(line);
```

Note: `readAnalog()` only makes sense on analog-capable pins.

## `LCDML3_StatusBar`

Bitmask status icon manager.

```cpp
LCDML3_StatusBar bar;
bar.setIcon(LCDML3_ICON_WIFI, true);
bar.setIcon(LCDML3_ICON_BT, true);

char text[32];
bar.format(text, sizeof(text)); // "WiFi BT"
```

Icons:

```cpp
LCDML3_ICON_WIFI
LCDML3_ICON_BT
LCDML3_ICON_BLE
LCDML3_ICON_SD
LCDML3_ICON_LOCK
LCDML3_ICON_WARN
LCDML3_ICON_BUSY
LCDML3_ICON_CUSTOM
```

## `LCDML3_ConfirmDialog`

Cancel/OK dialog state.

```cpp
LCDML3_ConfirmDialog confirm;
confirm.begin(false);
confirm.toggle();
confirm.confirm();

if (confirm.getResult() == LCDML3_CONFIRM_OK) {
  Serial.println(F("OK"));
}
```

## `LCDML3_PinEditor`

PIN/password digit editor.

```cpp
LCDML3_PinEditor pin;
pin.begin(4);
pin.increment();
pin.nextField();

char masked[8];
pin.format(masked, sizeof(masked), true);

if (pin.equals("1234")) {
  Serial.println(F("Unlocked"));
}
```

## `LCDML3_ProgressScreen`

Determinate or indeterminate progress display helper.

```cpp
LCDML3_ProgressScreen progress;
progress.begin(100);
progress.add(10);

char text[20];
progress.format(text, sizeof(text), "OTA");
```

Indeterminate:

```cpp
progress.begin(100, true);
uint8_t frame = progress.frame();
```

## `LCDML3_Wizard`

Multi-step flow helper.

```cpp
LCDML3_Wizard wizard;
wizard.begin(4);

wizard.markComplete(wizard.getStep(), true);
wizard.next();

if (wizard.isLast()) {
  Serial.println(F("Last step"));
}
```

## Persistent Settings Adapter

`LCDML3_SettingsAdapter` wraps storage with callbacks. This makes the same menu code work with EEPROM, ESP32 Preferences, SD files, FRAM, or custom storage.

```cpp
typedef uint8_t (*LCDML3_SettingsReadFn)(uint16_t address);
typedef void (*LCDML3_SettingsWriteFn)(uint16_t address, uint8_t value);
typedef void (*LCDML3_SettingsCommitFn)(void);
```

API:

```cpp
void begin(LCDML3_SettingsReadFn readFn, LCDML3_SettingsWriteFn writeFn, LCDML3_SettingsCommitFn commitFn = NULL);
bool available() const;
uint8_t readByte(uint16_t address, uint8_t fallback = 0) const;
void writeByte(uint16_t address, uint8_t value);
void readBytes(uint16_t address, uint8_t *buffer, uint16_t length) const;
void writeBytes(uint16_t address, const uint8_t *buffer, uint16_t length);
int32_t readInt32(uint16_t address, int32_t fallback = 0) const;
void writeInt32(uint16_t address, int32_t value);
float readFloat(uint16_t address, float fallback = 0.0f) const;
void writeFloat(uint16_t address, float value);
void commit();
```

### EEPROM Example

```cpp
#include <EEPROM.h>
#include <LCDMenuLib3.h>

uint8_t settingsRead(uint16_t address) {
  return EEPROM.read(address);
}

void settingsWrite(uint16_t address, uint8_t value) {
  EEPROM.write(address, value);
}

void settingsCommit() {
#if defined(ESP8266) || defined(ESP32)
  EEPROM.commit();
#endif
}

LCDML3_SettingsAdapter settings;

void setup() {
  EEPROM.begin(64);
  settings.begin(settingsRead, settingsWrite, settingsCommit);

  int32_t brightness = settings.readInt32(0, 50);
  settings.writeInt32(0, brightness + 1);
  settings.commit();
}
```

## Full Example: Serial Menu With Numeric Editor

```cpp
#include <LCDMenuLib3.h>

#define _LCDML_DISP_cols 20
#define _LCDML_DISP_rows 4

LCDMenuLib3_menu LCDML_0(255, 0, 0, NULL, NULL);
LCDML3_NumericEditor brightness;

void lcdml_display();
void lcdml_clear();
void lcdml_control();
void mFunc_brightness(uint8_t param);

LCDMenuLib3 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_display, lcdml_clear, lcdml_control);

LCDML_add(0, LCDML_0, 1, "Brightness", mFunc_brightness);
LCDML_createMenu(0);

void setup() {
  Serial.begin(115200);
  brightness.begin(50, 0, 255, 5);
  LCDML_setup(0);
}

void loop() {
  LCDML.loop();
}

void lcdml_clear() {
  Serial.println();
}

void lcdml_display() {
  if (LCDML.DISP_checkMenuUpdate()) {
    char text[21];
    uint8_t id = LCDML.DISP_getMenuContentId(0);
    LCDML_getContent(text, id);
    Serial.print(F("> "));
    Serial.println(text);
  }
}

void lcdml_control() {
  if (!Serial.available()) return;
  char c = Serial.read();
  if (c == 'e') LCDML.BT_enter();
  if (c == 'u') LCDML.BT_up();
  if (c == 'd') LCDML.BT_down();
  if (c == 'q') LCDML.BT_quit();
}

void mFunc_brightness(uint8_t param) {
  LCDML_UNUSED(param);

  if (LCDML.FUNC_setup()) {
    LCDML.MENU_disScroll();
    LCDML.FUNC_setLoopInterval(100);
    Serial.println(F("Use u/d to edit, q to quit"));
  }

  if (LCDML.FUNC_loop()) {
    if (LCDML.BT_checkUp()) {
      brightness.increment();
      LCDML.BT_resetUp();
    }
    if (LCDML.BT_checkDown()) {
      brightness.decrement();
      LCDML.BT_resetDown();
    }

    char text[16];
    brightness.format(text, sizeof(text));
    Serial.print(F("Brightness="));
    Serial.println(text);
  }

  if (LCDML.FUNC_close()) {
    LCDML.MENU_enScroll();
  }
}
```

## Full Example: WiFi Credentials State Menu

```cpp
#include <LCDMenuLib3.h>

LCDML3_WiFiMenu wifi;
LCDML3_IPAddressEditor ip;
char ssid[33] = "router";
char pass[65] = "password";
LCDML3_TextEditor ssidEditor;
LCDML3_TextEditor passEditor;

void setup() {
  Serial.begin(115200);
  wifi.setCredentials(ssid, pass);
  wifi.setState(LCDML3_NET_IDLE);
  ip.begin(192, 168, 1, 10);
  ssidEditor.begin(ssid, sizeof(ssid));
  passEditor.begin(pass, sizeof(pass), NULL, true);
}

void loop() {
  char text[40];

  wifi.formatStatus(text, sizeof(text));
  Serial.println(text);

  ip.format(text, sizeof(text));
  Serial.print(F("IP: "));
  Serial.println(text);

  passEditor.format(text, sizeof(text));
  Serial.print(F("Password: "));
  Serial.println(text);

  delay(1000);
}
```

## Full Example: Confirm Dialog and Progress

```cpp
#include <LCDMenuLib3.h>

LCDML3_ConfirmDialog confirm;
LCDML3_ProgressScreen progress;

void setup() {
  Serial.begin(115200);
  confirm.begin(false);
  progress.begin(100);
}

void loop() {
  char line[24];

  confirm.toggle();
  confirm.format(line, sizeof(line), "Start OTA?");
  Serial.println(line);

  confirm.confirm();
  if (confirm.getResult() == LCDML3_CONFIRM_OK) {
    while (!progress.isDone()) {
      progress.add(10);
      progress.format(line, sizeof(line), "OTA");
      Serial.println(line);
      delay(200);
    }
  }
}
```

## Notes For ESP32/ESP8266

LCDMenuLib3 widget classes are platform-neutral. They store menu state and format text. Your sketch performs the actual WiFi, Bluetooth, BLE, Preferences, SD, or OTA operations.

This keeps LCDMenuLib3 compilable on AVR boards while still supporting ESP projects.

For ESP32 Preferences, connect `LCDML3_SettingsAdapter` to wrapper callbacks. For WiFi and Bluetooth, use `LCDML3_WiFiMenu` and `LCDML3_BluetoothMenu` to track menu state while your sketch calls `WiFi.scanNetworks()`, `WiFi.begin()`, BLE scan APIs, or Bluetooth pairing APIs.

