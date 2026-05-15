#ifndef LCDMenuLib3_widgets_h
#define LCDMenuLib3_widgets_h

#include "Arduino.h"

enum LCDML3_Button3State : uint8_t
{
    LCDML3_STATE_OFF = 0,
    LCDML3_STATE_AUTO = 1,
    LCDML3_STATE_ON = 2
};

enum LCDML3_NetworkMenuState : uint8_t
{
    LCDML3_NET_IDLE = 0,
    LCDML3_NET_SCAN,
    LCDML3_NET_CONNECT,
    LCDML3_NET_CONNECTED,
    LCDML3_NET_DISCONNECT,
    LCDML3_NET_ERROR
};

enum LCDML3_BluetoothMenuState : uint8_t
{
    LCDML3_BT_IDLE = 0,
    LCDML3_BT_DISCOVER,
    LCDML3_BT_SEARCH,
    LCDML3_BT_BLE_SCAN,
    LCDML3_BT_PAIR,
    LCDML3_BT_CONNECTED,
    LCDML3_BT_DISCONNECT
};

enum LCDML3_ConfirmResult : uint8_t
{
    LCDML3_CONFIRM_NONE = 0,
    LCDML3_CONFIRM_CANCEL,
    LCDML3_CONFIRM_OK
};

enum LCDML3_StatusIcon : uint8_t
{
    LCDML3_ICON_WIFI = 0,
    LCDML3_ICON_BT,
    LCDML3_ICON_BLE,
    LCDML3_ICON_SD,
    LCDML3_ICON_LOCK,
    LCDML3_ICON_WARN,
    LCDML3_ICON_BUSY,
    LCDML3_ICON_CUSTOM
};

struct LCDML3_Time
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

struct LCDML3_Timer
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

struct LCDML3_Date
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
};

class LCDML3_TimeEditor
{
    public:
        LCDML3_TimeEditor();
        void begin(uint8_t hour, uint8_t minute, uint8_t second = 0, bool showSeconds = true);
        void nextField(void);
        void previousField(void);
        void increment(void);
        void decrement(void);
        void setValue(uint8_t hour, uint8_t minute, uint8_t second = 0);
        LCDML3_Time getValue(void) const;
        uint8_t getField(void) const;
        void format(char *buffer, size_t size) const;

    private:
        LCDML3_Time value;
        uint8_t field;
        bool secondsVisible;
};

class LCDML3_TimerEditor
{
    public:
        LCDML3_TimerEditor();
        void begin(uint8_t hour, uint8_t minute, uint8_t second = 0);
        void nextField(void);
        void previousField(void);
        void increment(void);
        void decrement(void);
        void setValue(uint8_t hour, uint8_t minute, uint8_t second = 0);
        LCDML3_Timer getValue(void) const;
        unsigned long toSeconds(void) const;
        void fromSeconds(unsigned long seconds);
        uint8_t getField(void) const;
        void format(char *buffer, size_t size) const;

    private:
        LCDML3_Timer value;
        uint8_t field;
};

class LCDML3_DateEditor
{
    public:
        LCDML3_DateEditor();
        void begin(uint16_t year, uint8_t month, uint8_t day);
        void nextField(void);
        void previousField(void);
        void increment(void);
        void decrement(void);
        void setValue(uint16_t year, uint8_t month, uint8_t day);
        LCDML3_Date getValue(void) const;
        uint8_t getField(void) const;
        void format(char *buffer, size_t size) const;
        static bool isLeapYear(uint16_t year);
        static uint8_t daysInMonth(uint16_t year, uint8_t month);

    private:
        void normalize(void);

        LCDML3_Date value;
        uint8_t field;
};

class LCDML3_RadioList
{
    public:
        LCDML3_RadioList();
        void begin(uint8_t itemCount, uint8_t visibleRows, uint8_t selected = 0);
        void up(void);
        void down(void);
        void selectCursor(void);
        void select(uint8_t index);
        uint8_t getCursor(void) const;
        uint8_t getSelected(void) const;
        uint8_t getWindowStart(void) const;
        uint8_t getVisibleRows(void) const;
        bool isVisible(uint8_t index) const;
        bool isSelected(uint8_t index) const;

    private:
        void keepCursorVisible(void);

        uint8_t count;
        uint8_t rows;
        uint8_t cursor;
        uint8_t selectedIndex;
        uint8_t windowStart;
};

class LCDML3_CheckList
{
    public:
        LCDML3_CheckList();
        void begin(uint8_t itemCount, uint8_t visibleRows, uint64_t checkedMask = 0);
        void up(void);
        void down(void);
        void toggleCursor(void);
        void setChecked(uint8_t index, bool checked);
        bool isChecked(uint8_t index) const;
        uint64_t getMask(void) const;
        void setMask(uint64_t mask);
        uint8_t getCursor(void) const;
        uint8_t getWindowStart(void) const;
        uint8_t getVisibleRows(void) const;
        bool isVisible(uint8_t index) const;

    private:
        void keepCursorVisible(void);

        uint8_t count;
        uint8_t rows;
        uint8_t cursor;
        uint8_t windowStart;
        uint64_t mask;
};

class LCDML3_StateButton
{
    public:
        LCDML3_StateButton();
        void begin(uint8_t stateCount, uint8_t initialState = 0);
        void next(void);
        void previous(void);
        void set(uint8_t state);
        uint8_t get(void) const;
        bool isOn(void) const;
        bool isAuto(void) const;
        bool isOff(void) const;
        void label(char *buffer, size_t size) const;

    private:
        uint8_t count;
        uint8_t state;
};

class LCDML3_NumericEditor
{
    public:
        LCDML3_NumericEditor();
        void begin(int32_t value, int32_t minValue, int32_t maxValue, int32_t stepValue = 1, bool wrapEnabled = false);
        void increment(void);
        void decrement(void);
        void setValue(int32_t value);
        void setBounds(int32_t minValue, int32_t maxValue);
        void setStep(int32_t stepValue);
        void setWrap(bool enabled);
        int32_t getValue(void) const;
        int32_t getMin(void) const;
        int32_t getMax(void) const;
        int32_t getStep(void) const;
        void format(char *buffer, size_t size, const char *suffix = NULL) const;

    private:
        void normalize(void);

        int32_t value;
        int32_t minVal;
        int32_t maxVal;
        int32_t step;
        bool wrap;
};

class LCDML3_FloatEditor
{
    public:
        LCDML3_FloatEditor();
        void begin(float value, float minValue, float maxValue, float stepValue = 0.1f, uint8_t precision = 1, bool wrapEnabled = false);
        void increment(void);
        void decrement(void);
        void setValue(float value);
        void setBounds(float minValue, float maxValue);
        void setStep(float stepValue);
        void setPrecision(uint8_t precision);
        void setWrap(bool enabled);
        float getValue(void) const;
        uint8_t getPrecision(void) const;
        void format(char *buffer, size_t size, const char *suffix = NULL) const;

    private:
        void normalize(void);

        float value;
        float minVal;
        float maxVal;
        float step;
        uint8_t precision;
        bool wrap;
};

class LCDML3_IPAddressEditor
{
    public:
        LCDML3_IPAddressEditor();
        void begin(uint8_t a = 192, uint8_t b = 168, uint8_t c = 1, uint8_t d = 1);
        void nextField(void);
        void previousField(void);
        void increment(void);
        void decrement(void);
        void setOctet(uint8_t index, uint8_t value);
        uint8_t getOctet(uint8_t index) const;
        uint8_t getField(void) const;
        void getBytes(uint8_t out[4]) const;
        void format(char *buffer, size_t size) const;

    private:
        uint8_t octets[4];
        uint8_t field;
};

class LCDML3_TextEditor
{
    public:
        LCDML3_TextEditor();
        void begin(char *buffer, uint8_t capacity, const char *alphabet = NULL, bool passwordMode = false);
        void nextChar(void);
        void previousChar(void);
        void nextPosition(void);
        void previousPosition(void);
        void clear(void);
        const char *getText(void) const;
        uint8_t getCursor(void) const;
        bool isPassword(void) const;
        void format(char *out, size_t size) const;

    private:
        int16_t alphabetIndex(char c) const;

        char *text;
        uint8_t cap;
        uint8_t cursor;
        const char *chars;
        bool password;
};

struct LCDML3_WiFiCredentials
{
    char ssid[33];
    char password[65];
};

class LCDML3_WiFiMenu
{
    public:
        LCDML3_WiFiMenu();
        void begin(void);
        void setCredentials(const char *ssid, const char *password);
        LCDML3_WiFiCredentials getCredentials(void) const;
        void setState(LCDML3_NetworkMenuState state);
        LCDML3_NetworkMenuState getState(void) const;
        void setSelectedNetwork(uint8_t index);
        uint8_t getSelectedNetwork(void) const;
        void formatStatus(char *buffer, size_t size) const;

    private:
        LCDML3_WiFiCredentials credentials;
        LCDML3_NetworkMenuState state;
        uint8_t selectedNetwork;
};

class LCDML3_BluetoothMenu
{
    public:
        LCDML3_BluetoothMenu();
        void begin(void);
        void setState(LCDML3_BluetoothMenuState state);
        LCDML3_BluetoothMenuState getState(void) const;
        void nextAction(void);
        void previousAction(void);
        void setSelectedDevice(uint8_t index);
        uint8_t getSelectedDevice(void) const;
        void setBleMode(bool enabled);
        bool isBleMode(void) const;
        void formatStatus(char *buffer, size_t size) const;

    private:
        LCDML3_BluetoothMenuState state;
        uint8_t selectedDevice;
        bool bleMode;
};

class LCDML3_MenuHeader
{
    public:
        LCDML3_MenuHeader();
        void begin(const char *title, const char *subtitle = NULL, uint8_t level = 0);
        void setTitle(const char *title);
        void setSubtitle(const char *subtitle);
        void setLevel(uint8_t level);
        const char *getTitle(void) const;
        const char *getSubtitle(void) const;
        uint8_t getLevel(void) const;
        void format(char *buffer, size_t size) const;

    private:
        const char *title;
        const char *subtitle;
        uint8_t level;
};

class LCDML3_Theme
{
    public:
        LCDML3_Theme();
        void setColors(uint16_t foreground, uint16_t background, uint16_t accent, uint16_t warning);
        void setSymbols(const char *cursor, const char *checked, const char *unchecked, const char *radioOn, const char *radioOff);
        uint16_t fg(void) const;
        uint16_t bg(void) const;
        uint16_t accentColor(void) const;
        uint16_t warningColor(void) const;
        const char *cursorSymbol(void) const;
        const char *checkedSymbol(void) const;
        const char *uncheckedSymbol(void) const;
        const char *radioOnSymbol(void) const;
        const char *radioOffSymbol(void) const;

    private:
        uint16_t colorFg;
        uint16_t colorBg;
        uint16_t colorAccent;
        uint16_t colorWarning;
        const char *symCursor;
        const char *symChecked;
        const char *symUnchecked;
        const char *symRadioOn;
        const char *symRadioOff;
};

class LCDML3_DebugMenu
{
    public:
        LCDML3_DebugMenu();
        void begin(uint8_t pin = 13);
        void setPin(uint8_t pin);
        uint8_t getPin(void) const;
        void modeInput(bool pullup = false);
        void modeOutput(void);
        void write(bool high);
        int readDigital(void) const;
        int readAnalog(void) const;
        void serialWrite(Stream &serial, const char *message);
        void formatPin(char *buffer, size_t size) const;

    private:
        uint8_t pin;
};

class LCDML3_StatusBar
{
    public:
        LCDML3_StatusBar();
        void setIcon(uint8_t icon, bool enabled);
        void toggleIcon(uint8_t icon);
        bool isIconEnabled(uint8_t icon) const;
        uint16_t getMask(void) const;
        void setMask(uint16_t mask);
        void format(char *buffer, size_t size) const;

    private:
        uint16_t mask;
};

class LCDML3_ConfirmDialog
{
    public:
        LCDML3_ConfirmDialog();
        void begin(bool defaultOk = false);
        void toggle(void);
        void chooseOk(void);
        void chooseCancel(void);
        void confirm(void);
        bool isOkSelected(void) const;
        LCDML3_ConfirmResult getResult(void) const;
        bool isDone(void) const;
        void reset(void);
        void format(char *buffer, size_t size, const char *message = NULL) const;

    private:
        bool okSelected;
        LCDML3_ConfirmResult result;
};

class LCDML3_PinEditor
{
    public:
        LCDML3_PinEditor();
        void begin(uint8_t length = 4, char fill = '0');
        void nextField(void);
        void previousField(void);
        void increment(void);
        void decrement(void);
        void setDigit(uint8_t index, uint8_t digit);
        uint8_t getDigit(uint8_t index) const;
        uint8_t getField(void) const;
        uint8_t length(void) const;
        bool equals(const char *pin) const;
        void format(char *buffer, size_t size, bool masked = true) const;

    private:
        char digits[9];
        uint8_t len;
        uint8_t field;
};

class LCDML3_ProgressScreen
{
    public:
        LCDML3_ProgressScreen();
        void begin(uint32_t total = 100, bool indeterminate = false);
        void set(uint32_t value);
        void add(uint32_t delta);
        void setTotal(uint32_t total);
        void setIndeterminate(bool enabled);
        bool isDone(void) const;
        uint8_t percent(void) const;
        uint8_t frame(void);
        void format(char *buffer, size_t size, const char *label = NULL) const;

    private:
        uint32_t value;
        uint32_t total;
        bool indeterminate;
        uint8_t animFrame;
};

class LCDML3_Wizard
{
    public:
        LCDML3_Wizard();
        void begin(uint8_t stepCount);
        void next(void);
        void previous(void);
        void goTo(uint8_t step);
        void markComplete(uint8_t step, bool complete = true);
        bool isComplete(uint8_t step) const;
        bool isLast(void) const;
        uint8_t getStep(void) const;
        uint8_t getStepCount(void) const;
        uint32_t getCompletedMask(void) const;

    private:
        uint8_t step;
        uint8_t count;
        uint32_t completedMask;
};

typedef uint8_t (*LCDML3_SettingsReadFn)(uint16_t address);
typedef void (*LCDML3_SettingsWriteFn)(uint16_t address, uint8_t value);
typedef void (*LCDML3_SettingsCommitFn)(void);

class LCDML3_SettingsAdapter
{
    public:
        LCDML3_SettingsAdapter();
        void begin(LCDML3_SettingsReadFn readFn, LCDML3_SettingsWriteFn writeFn, LCDML3_SettingsCommitFn commitFn = NULL);
        bool available(void) const;
        uint8_t readByte(uint16_t address, uint8_t fallback = 0) const;
        void writeByte(uint16_t address, uint8_t value);
        void readBytes(uint16_t address, uint8_t *buffer, uint16_t length) const;
        void writeBytes(uint16_t address, const uint8_t *buffer, uint16_t length);
        int32_t readInt32(uint16_t address, int32_t fallback = 0) const;
        void writeInt32(uint16_t address, int32_t value);
        float readFloat(uint16_t address, float fallback = 0.0f) const;
        void writeFloat(uint16_t address, float value);
        void commit(void);

    private:
        LCDML3_SettingsReadFn readFn;
        LCDML3_SettingsWriteFn writeFn;
        LCDML3_SettingsCommitFn commitFn;
};

#endif
