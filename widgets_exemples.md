# LCDMenuLib3 Widgets Exemples 128x64

Ce fichier montre des idees de rendu ASCII/Markdown pour les widgets LCDMenuLib3 sur un ecran 128x64.

Hypothese de lecture:

- Ecran: 128 x 64 pixels.
- Police classique: environ 6 x 8 pixels.
- Grille utile: environ 21 colonnes x 8 lignes.
- Les maquettes ci-dessous representent surtout la composition visuelle. Le rendu reel dependra de la police, du driver, du contraste, et de vos marges.

Legende:

- `>` curseur ou ligne active.
- `[x]` choix coche.
- `[ ]` choix non coche.
- `(o)` radio selectionnee.
- `( )` radio non selectionnee.
- `#` progression, barre ou signal fort.
- `.` progression vide, barre faible ou historique.
- `~` activite en cours.
- `!` avertissement.

## Gabarit 128x64

```text
+---------------------+
|012345678901234567890|
|                     |
|                     |
|                     |
|                     |
|                     |
|                     |
|                     |
+---------------------+
```

## Menu Header

```text
+---------------------+
|NETWORK SETUP     W! |
|WiFi credentials     |
|---------------------|
|> SSID               |
|  Password           |
|  Static IP          |
|  Back               |
+---------------------+
```

Usage typique:

```cpp
LCDML3_MenuHeader header;
LCDML3_StatusBar status;

header.begin("NETWORK SETUP", "WiFi credentials", 1);
status.setIcon(LCDML3_ICON_WIFI, true);
status.setIcon(LCDML3_ICON_WARN, true);
```

## Time Editor

```text
+---------------------+
|SET TIME          W  |
|                     |
|      14:32:05       |
|      ^^             |
|                     |
|UP/DN edit  L/R field|
|OK save   BACK cancel|
+---------------------+
```

Usage typique:

```cpp
LCDML3_TimeEditor timeEdit;
timeEdit.begin(14, 32, 5, true);
timeEdit.increment();
timeEdit.nextField();
```

## Timer Editor

```text
+---------------------+
|TIMER                |
|                     |
|      00:15:00       |
|         ^^          |
|                     |
|Step: minutes        |
|OK start             |
+---------------------+
```

Usage typique:

```cpp
LCDML3_TimerEditor timer;
timer.begin(0, 15, 0);
unsigned long seconds = timer.toSeconds();
```

## Date Editor

```text
+---------------------+
|SET DATE             |
|                     |
|      15/05/2026     |
|      ^^             |
|                     |
|Leap years handled   |
|OK save              |
+---------------------+
```

Usage typique:

```cpp
LCDML3_DateEditor dateEdit;
dateEdit.begin(2026, 5, 15);
dateEdit.increment();
```

## Radio List Fenetree

```text
+---------------------+
|MODE                 |
|> ( ) Eco            |
|  (o) Normal         |
|  ( ) Boost          |
|  ( ) Silent         |
|---------------------|
|2/7 selected         |
|OK choose            |
+---------------------+
```

Usage typique:

```cpp
LCDML3_RadioList modes;
modes.begin(7, 4, 1);
modes.down();
modes.selectCursor();
```

## Checklist Fenetree

```text
+---------------------+
|OUTPUTS              |
|> [x] Pump           |
|  [ ] Fan            |
|  [x] Light          |
|  [ ] Valve          |
|---------------------|
|Mask: 0x0005         |
|OK toggle            |
+---------------------+
```

Usage typique:

```cpp
LCDML3_CheckList outputs;
outputs.begin(8, 4, 0x0005);
outputs.toggleCursor();
uint64_t mask = outputs.getMask();
```

## State Button ON/OFF

```text
+---------------------+
|RELAY 1              |
|                     |
|        [ ON ]       |
|                     |
|L/R toggle           |
|OK apply             |
|BACK cancel          |
+---------------------+
```

Usage typique:

```cpp
LCDML3_StateButton relay;
relay.begin(2, LCDML3_STATE_ON);
relay.next();
```

## State Button MANUAL/AUTO

```text
+---------------------+
|CONTROL MODE         |
|                     |
|      [ AUTO ]       |
|                     |
|Manual overrides PID |
|Auto follows program |
|OK apply             |
+---------------------+
```

Usage typique:

```cpp
LCDML3_StateButton mode;
mode.begin(2, 1);
bool automatic = mode.isAuto();
```

## State Button OFF/AUTO/ON

```text
+---------------------+
|PUMP                 |
|                     |
|     OFF AUTO ON     |
|         [AUTO]      |
|                     |
|L/R select state     |
|OK apply             |
+---------------------+
```

Usage typique:

```cpp
LCDML3_StateButton pump;
pump.begin(3, LCDML3_STATE_AUTO);
```

## Numeric Editor

```text
+---------------------+
|BRIGHTNESS        W  |
|                     |
|        075 %        |
|        -----        |
|Min 0  Max 100       |
|Step 5               |
|OK save              |
+---------------------+
```

Usage typique:

```cpp
LCDML3_NumericEditor brightness;
brightness.begin(75, 0, 100, 5, false);
brightness.increment();
```

## Float Editor

```text
+---------------------+
|PID KP               |
|                     |
|        01.250       |
|        ------       |
|Min 0.00 Max 20.00   |
|Step 0.050           |
|OK save              |
+---------------------+
```

Usage typique:

```cpp
LCDML3_FloatEditor kp;
kp.begin(1.250f, 0.0f, 20.0f, 0.050f, 3, false);
```

## IP Address Editor

```text
+---------------------+
|STATIC IP         W  |
|                     |
|   192.168.001.042   |
|       ^^^           |
|                     |
|L/R octet  UP/DN val |
|OK save              |
+---------------------+
```

Usage typique:

```cpp
LCDML3_IPAddressEditor ip;
ip.begin(192, 168, 1, 42);
ip.nextField();
ip.increment();
```

## WiFi Credential Menu

```text
+---------------------+
|WIFI SETUP        W  |
|SSID: Workshop       |
|PASS: ********       |
|---------------------|
|> Scan networks      |
|  Connect            |
|  Static IP          |
|State: idle          |
+---------------------+
```

Usage typique:

```cpp
LCDML3_WiFiMenu wifi;
wifi.begin();
wifi.setCredentials("Workshop", "secret");
wifi.setState(LCDML3_NET_SCAN);
```

## Bluetooth / BLE Menu

```text
+---------------------+
|BLUETOOTH         B  |
|Mode: BLE scan       |
|Device: 03           |
|---------------------|
|> Discover           |
|  Pair               |
|  Disconnect         |
|State: search        |
+---------------------+
```

Usage typique:

```cpp
LCDML3_BluetoothMenu bt;
bt.begin();
bt.setBleMode(true);
bt.setState(LCDML3_BT_BLE_SCAN);
```

## Status Bar Icons

```text
+---------------------+
|TEMP CTRL   W B S !  |
|---------------------|
|> Setpoint  22.5 C   |
|  Mode      AUTO     |
|  Output    ON       |
|  Logs      2 warn   |
|                     |
+---------------------+
```

Usage typique:

```cpp
LCDML3_StatusBar bar;
bar.setIcon(LCDML3_ICON_WIFI, true);
bar.setIcon(LCDML3_ICON_BT, true);
bar.setIcon(LCDML3_ICON_SD, true);
bar.setIcon(LCDML3_ICON_WARN, true);
```

## Theme / Skin Menu

```text
+---------------------+
|THEME                |
|> LCD classic        |
|  OLED mono          |
|  TFT dark           |
|  TFT light          |
|  High contrast      |
|Preview: > [x] (o)   |
|OK apply             |
+---------------------+
```

Usage typique:

```cpp
LCDML3_Theme theme;
LCDML3_applyThemePreset(theme, LCDML3_THEME_TFT_DARK);
```

## Confirm Dialog

```text
+---------------------+
|CONFIRM              |
|                     |
|Erase settings?      |
|                     |
|   [Cancel]   OK     |
|                     |
|L/R choose           |
+---------------------+
```

Usage typique:

```cpp
LCDML3_ConfirmDialog confirm;
confirm.begin(false);
confirm.toggle();
confirm.confirm();
```

## PIN / Password Editor

```text
+---------------------+
|ENTER PIN            |
|                     |
|        **5*         |
|          ^          |
|                     |
|UP/DN digit          |
|OK validate          |
+---------------------+
```

Usage typique:

```cpp
LCDML3_PinEditor pin;
pin.begin(4);
pin.setDigit(2, 5);
bool ok = pin.equals("1254");
```

## Progress Screen

```text
+---------------------+
|OTA UPDATE        W  |
|Downloading          |
|                     |
|[#########.....] 65% |
|                     |
|Do not power off     |
|                     |
+---------------------+
```

Usage typique:

```cpp
LCDML3_ProgressScreen progress;
progress.begin(100);
progress.set(65);
```

## Indeterminate Progress

```text
+---------------------+
|SCANNING I2C         |
|                     |
|        ~ ~ ~        |
|                     |
|Searching devices    |
|Please wait          |
|                     |
+---------------------+
```

Usage typique:

```cpp
LCDML3_ProgressScreen scan;
scan.begin(100, true);
uint8_t frame = scan.frame();
```

## Wizard Flow

```text
+---------------------+
|SETUP WIZARD     2/5 |
|WiFi credentials     |
|---------------------|
|SSID: Workshop       |
|PASS: ********       |
|                     |
|BACK prev   OK next  |
+---------------------+
```

Usage typique:

```cpp
LCDML3_Wizard wizard;
wizard.begin(5);
wizard.goTo(1);
wizard.markComplete(1);
```

## Debug GPIO Menu

```text
+---------------------+
|DEBUG GPIO           |
|Pin: 13              |
|Mode: OUTPUT         |
|Value: HIGH          |
|---------------------|
|> Toggle             |
|  Read pin           |
|Serial: enabled      |
+---------------------+
```

Usage typique:

```cpp
LCDML3_DebugMenu debug;
debug.begin();
debug.setPin(13);
debug.modeOutput();
debug.write(true);
```

## Sparkline Sensor Graph

```text
+---------------------+
|TEMP HISTORY      W  |
|35C              ##  |
|30C        ###  #### |
|25C   ###########    |
|20C ###              |
|15C                  |
|Now: 24.8 C          |
+---------------------+
```

Usage typique:

```cpp
LCDML3_Sparkline graph;
graph.begin(150, 350);
graph.add(248);
uint8_t y = graph.normalized(0, 40);
```

## Log Viewer

```text
+---------------------+
|LOGS filter WARN     |
|! WiFi weak          |
|! Low battery        |
|E Sensor fail        |
|---------------------|
|3 visible / 12 total |
|UP/DN scroll         |
+---------------------+
```

Usage typique:

```cpp
LCDML3_LogViewer logs;
logs.add(LCDML3_LOG_WARN, "WiFi weak");
logs.setFilter(LCDML3_LOG_WARN);
```

## Alarm Scheduler

```text
+---------------------+
|ALARMS               |
|> 07:30  MTWTF  ON   |
|  18:00  MTWTF  OFF  |
|  09:00  SS     ON   |
|---------------------|
|L/R field UP/DN edit |
|OK save              |
+---------------------+
```

Usage typique:

```cpp
LCDML3_AlarmScheduler alarms;
alarms.begin();
alarms.set(0, 7, 30, 0x1F, true);
```

## Unit Selector

```text
+---------------------+
|UNITS                |
|                     |
|Temperature: [ C ]   |
|Pressure:    [bar]   |
|Speed:       [m/s]   |
|                     |
|L/R choose           |
+---------------------+
```

Usage typique:

```cpp
const char *units[] = { "C", "F", "K" };
LCDML3_UnitSelector selector;
selector.begin(units, 3, 0);
```

## OTA Status

```text
+---------------------+
|OTA UPDATE        W  |
|State: flashing      |
|                     |
|[############..] 87% |
|                     |
|Restart when done    |
|                     |
+---------------------+
```

Usage typique:

```cpp
LCDML3_OTAStatus ota;
ota.begin();
ota.setState(LCDML3_OTA_FLASHING);
ota.setProgress(87);
```

## Calibration Wizard

```text
+---------------------+
|CALIBRATION      1/2 |
|Put probe in 0.0 C   |
|Raw: 00123           |
|Ref: 00000           |
|---------------------|
|OK capture           |
|BACK cancel          |
+---------------------+
```

Usage typique:

```cpp
LCDML3_CalibrationWizard cal;
cal.begin(2);
cal.captureRaw(0, 123, 0);
```

## Action Menu

```text
+---------------------+
|ACTIONS              |
|> Relay ON           |
|  Relay OFF          |
|  MQTT publish       |
|  HTTP webhook       |
|---------------------|
|OK trigger           |
|Last: MQTT publish   |
+---------------------+
```

Usage typique:

```cpp
LCDML3_ActionMenu actions;
actions.begin(runAction);
actions.trigger(3);
```

## SD File Menu

```text
+---------------------+
|SD FILES          S  |
|> config.txt         |
|  log001.csv         |
|  log002.csv         |
|  backup.bin         |
|---------------------|
|4/18 visible         |
|OK open              |
+---------------------+
```

Usage typique:

```cpp
LCDML3_SDFileMenu files;
files.begin(4);
files.setItemCount(18);
files.down();
```

## Diagnostic Menu

```text
+---------------------+
|DIAGNOSTICS       W! |
|I2C devices: 03      |
|WiFi found : 07      |
|Heap free  : 42120   |
|Uptime     : 02:14   |
|---------------------|
|OK refresh           |
+---------------------+
```

Usage typique:

```cpp
LCDML3_DiagnosticMenu diag;
diag.begin();
diag.setI2CFound(3);
diag.setWiFiFound(7);
diag.setHeap(42120);
diag.setUptime(millis());
```

## Full Dashboard Example

```text
+---------------------+
|GREENHOUSE     W S ! |
|> Temp set  24.5 C   |
|  Timer     00:15:00 |
|  Pump      AUTO     |
|  WiFi      connected|
|---------------------|
|Graph ###__####_#    |
|OK edit  BACK menu   |
+---------------------+
```

Ce type d'ecran combine:

- `LCDML3_MenuHeader`
- `LCDML3_StatusBar`
- `LCDML3_FloatEditor`
- `LCDML3_TimerEditor`
- `LCDML3_StateButton`
- `LCDML3_WiFiMenu`
- `LCDML3_Sparkline`

## Full Setup Example

```text
+---------------------+
|DEVICE SETUP     4/7 |
|Network              |
|---------------------|
|SSID: Workshop       |
|IP: 192.168.001.042  |
|BT: BLE scan         |
|OK next  BACK prev   |
+---------------------+
```

Ce type d'ecran combine:

- `LCDML3_Wizard`
- `LCDML3_WiFiMenu`
- `LCDML3_IPAddressEditor`
- `LCDML3_BluetoothMenu`
- `LCDML3_ConfirmDialog`
- `LCDML3_SettingsAdapter`
