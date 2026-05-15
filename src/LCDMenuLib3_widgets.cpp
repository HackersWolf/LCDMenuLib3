#include "LCDMenuLib3_widgets.h"
#include <string.h>

static uint8_t lcdml3_wrapIncrement(uint8_t value, uint8_t maxValue)
{
    return value >= maxValue ? 0 : value + 1;
}

static uint8_t lcdml3_wrapDecrement(uint8_t value, uint8_t maxValue)
{
    return value == 0 ? maxValue : value - 1;
}

static uint8_t lcdml3_clampRows(uint8_t rows)
{
    return rows == 0 ? 1 : rows;
}

LCDML3_TimeEditor::LCDML3_TimeEditor()
{
    begin(0, 0, 0);
}

void LCDML3_TimeEditor::begin(uint8_t hour, uint8_t minute, uint8_t second, bool showSeconds)
{
    secondsVisible = showSeconds;
    field = 0;
    setValue(hour, minute, second);
}

void LCDML3_TimeEditor::nextField(void)
{
    uint8_t maxField = secondsVisible ? 2 : 1;
    field = lcdml3_wrapIncrement(field, maxField);
}

void LCDML3_TimeEditor::previousField(void)
{
    uint8_t maxField = secondsVisible ? 2 : 1;
    field = lcdml3_wrapDecrement(field, maxField);
}

void LCDML3_TimeEditor::increment(void)
{
    if(field == 0) value.hour = lcdml3_wrapIncrement(value.hour, 23);
    if(field == 1) value.minute = lcdml3_wrapIncrement(value.minute, 59);
    if(field == 2) value.second = lcdml3_wrapIncrement(value.second, 59);
}

void LCDML3_TimeEditor::decrement(void)
{
    if(field == 0) value.hour = lcdml3_wrapDecrement(value.hour, 23);
    if(field == 1) value.minute = lcdml3_wrapDecrement(value.minute, 59);
    if(field == 2) value.second = lcdml3_wrapDecrement(value.second, 59);
}

void LCDML3_TimeEditor::setValue(uint8_t hour, uint8_t minute, uint8_t second)
{
    value.hour = hour > 23 ? 23 : hour;
    value.minute = minute > 59 ? 59 : minute;
    value.second = second > 59 ? 59 : second;
}

LCDML3_Time LCDML3_TimeEditor::getValue(void) const
{
    return value;
}

uint8_t LCDML3_TimeEditor::getField(void) const
{
    return field;
}

void LCDML3_TimeEditor::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;

    if(secondsVisible)
    {
        snprintf(buffer, size, "%02u:%02u:%02u", value.hour, value.minute, value.second);
    }
    else
    {
        snprintf(buffer, size, "%02u:%02u", value.hour, value.minute);
    }
}

static void lcdml3_copyText(char *dest, size_t size, const char *src)
{
    if(dest == NULL || size == 0) return;
    if(src == NULL) src = "";
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}

static int32_t lcdml3_abs32(int32_t value)
{
    return value < 0 ? -value : value;
}

static float lcdml3_absFloat(float value)
{
    return value < 0.0f ? -value : value;
}

LCDML3_TimerEditor::LCDML3_TimerEditor()
{
    begin(0, 0, 0);
}

void LCDML3_TimerEditor::begin(uint8_t hour, uint8_t minute, uint8_t second)
{
    field = 0;
    setValue(hour, minute, second);
}

void LCDML3_TimerEditor::nextField(void)
{
    field = lcdml3_wrapIncrement(field, 2);
}

void LCDML3_TimerEditor::previousField(void)
{
    field = lcdml3_wrapDecrement(field, 2);
}

void LCDML3_TimerEditor::increment(void)
{
    if(field == 0) value.hour = lcdml3_wrapIncrement(value.hour, 99);
    if(field == 1) value.minute = lcdml3_wrapIncrement(value.minute, 59);
    if(field == 2) value.second = lcdml3_wrapIncrement(value.second, 59);
}

void LCDML3_TimerEditor::decrement(void)
{
    if(field == 0) value.hour = lcdml3_wrapDecrement(value.hour, 99);
    if(field == 1) value.minute = lcdml3_wrapDecrement(value.minute, 59);
    if(field == 2) value.second = lcdml3_wrapDecrement(value.second, 59);
}

void LCDML3_TimerEditor::setValue(uint8_t hour, uint8_t minute, uint8_t second)
{
    value.hour = hour > 99 ? 99 : hour;
    value.minute = minute > 59 ? 59 : minute;
    value.second = second > 59 ? 59 : second;
}

LCDML3_Timer LCDML3_TimerEditor::getValue(void) const
{
    return value;
}

unsigned long LCDML3_TimerEditor::toSeconds(void) const
{
    return ((unsigned long)value.hour * 3600UL) + ((unsigned long)value.minute * 60UL) + value.second;
}

void LCDML3_TimerEditor::fromSeconds(unsigned long seconds)
{
    value.hour = (seconds / 3600UL) > 99 ? 99 : (uint8_t)(seconds / 3600UL);
    seconds %= 3600UL;
    value.minute = (uint8_t)(seconds / 60UL);
    value.second = (uint8_t)(seconds % 60UL);
}

uint8_t LCDML3_TimerEditor::getField(void) const
{
    return field;
}

void LCDML3_TimerEditor::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "%02u:%02u:%02u", value.hour, value.minute, value.second);
}

LCDML3_DateEditor::LCDML3_DateEditor()
{
    begin(2026, 1, 1);
}

void LCDML3_DateEditor::begin(uint16_t year, uint8_t month, uint8_t day)
{
    field = 0;
    setValue(year, month, day);
}

void LCDML3_DateEditor::nextField(void)
{
    field = lcdml3_wrapIncrement(field, 2);
}

void LCDML3_DateEditor::previousField(void)
{
    field = lcdml3_wrapDecrement(field, 2);
}

void LCDML3_DateEditor::increment(void)
{
    if(field == 0) value.day++;
    if(field == 1) value.month++;
    if(field == 2) value.year++;
    normalize();
}

void LCDML3_DateEditor::decrement(void)
{
    if(field == 0)
    {
        value.day = value.day == 1 ? daysInMonth(value.year, value.month) : value.day - 1;
    }
    if(field == 1)
    {
        value.month = value.month == 1 ? 12 : value.month - 1;
    }
    if(field == 2)
    {
        value.year = value.year <= 1970 ? 2099 : value.year - 1;
    }
    normalize();
}

void LCDML3_DateEditor::setValue(uint16_t year, uint8_t month, uint8_t day)
{
    value.year = year;
    value.month = month;
    value.day = day;
    normalize();
}

LCDML3_Date LCDML3_DateEditor::getValue(void) const
{
    return value;
}

uint8_t LCDML3_DateEditor::getField(void) const
{
    return field;
}

void LCDML3_DateEditor::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "%02u/%02u/%04u", value.day, value.month, value.year);
}

bool LCDML3_DateEditor::isLeapYear(uint16_t year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

uint8_t LCDML3_DateEditor::daysInMonth(uint16_t year, uint8_t month)
{
    static const uint8_t days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if(month < 1 || month > 12) return 31;
    if(month == 2 && isLeapYear(year)) return 29;

    return days[month - 1];
}

void LCDML3_DateEditor::normalize(void)
{
    if(value.year < 1970) value.year = 1970;
    if(value.year > 2099) value.year = 2099;
    if(value.month < 1) value.month = 1;
    if(value.month > 12) value.month = 1;

    uint8_t maxDay = daysInMonth(value.year, value.month);
    if(value.day < 1) value.day = 1;
    if(value.day > maxDay) value.day = 1;
}

LCDML3_RadioList::LCDML3_RadioList()
{
    begin(0, 1, 0);
}

void LCDML3_RadioList::begin(uint8_t itemCount, uint8_t visibleRows, uint8_t selected)
{
    count = itemCount;
    rows = lcdml3_clampRows(visibleRows);
    selectedIndex = (count == 0 || selected >= count) ? 0 : selected;
    cursor = selectedIndex;
    windowStart = 0;
    keepCursorVisible();
}

void LCDML3_RadioList::up(void)
{
    if(count == 0) return;
    cursor = cursor == 0 ? count - 1 : cursor - 1;
    keepCursorVisible();
}

void LCDML3_RadioList::down(void)
{
    if(count == 0) return;
    cursor = cursor + 1 >= count ? 0 : cursor + 1;
    keepCursorVisible();
}

void LCDML3_RadioList::selectCursor(void)
{
    selectedIndex = cursor;
}

void LCDML3_RadioList::select(uint8_t index)
{
    if(index >= count) return;
    selectedIndex = index;
    cursor = index;
    keepCursorVisible();
}

uint8_t LCDML3_RadioList::getCursor(void) const
{
    return cursor;
}

uint8_t LCDML3_RadioList::getSelected(void) const
{
    return selectedIndex;
}

uint8_t LCDML3_RadioList::getWindowStart(void) const
{
    return windowStart;
}

uint8_t LCDML3_RadioList::getVisibleRows(void) const
{
    return rows;
}

bool LCDML3_RadioList::isVisible(uint8_t index) const
{
    return index >= windowStart && index < (uint8_t)(windowStart + rows);
}

bool LCDML3_RadioList::isSelected(uint8_t index) const
{
    return index == selectedIndex;
}

void LCDML3_RadioList::keepCursorVisible(void)
{
    if(cursor < windowStart) windowStart = cursor;
    if(cursor >= (uint8_t)(windowStart + rows)) windowStart = cursor - rows + 1;
}

LCDML3_CheckList::LCDML3_CheckList()
{
    begin(0, 1, 0);
}

void LCDML3_CheckList::begin(uint8_t itemCount, uint8_t visibleRows, uint64_t checkedMask)
{
    count = itemCount > 64 ? 64 : itemCount;
    rows = lcdml3_clampRows(visibleRows);
    cursor = 0;
    windowStart = 0;
    mask = checkedMask;
}

void LCDML3_CheckList::up(void)
{
    if(count == 0) return;
    cursor = cursor == 0 ? count - 1 : cursor - 1;
    keepCursorVisible();
}

void LCDML3_CheckList::down(void)
{
    if(count == 0) return;
    cursor = cursor + 1 >= count ? 0 : cursor + 1;
    keepCursorVisible();
}

void LCDML3_CheckList::toggleCursor(void)
{
    setChecked(cursor, !isChecked(cursor));
}

void LCDML3_CheckList::setChecked(uint8_t index, bool checked)
{
    if(index >= count) return;

    if(checked)
    {
        mask |= (1ULL << index);
    }
    else
    {
        mask &= ~(1ULL << index);
    }
}

bool LCDML3_CheckList::isChecked(uint8_t index) const
{
    if(index >= count) return false;
    return (mask & (1ULL << index)) != 0;
}

uint64_t LCDML3_CheckList::getMask(void) const
{
    return mask;
}

void LCDML3_CheckList::setMask(uint64_t checkedMask)
{
    mask = checkedMask;
}

uint8_t LCDML3_CheckList::getCursor(void) const
{
    return cursor;
}

uint8_t LCDML3_CheckList::getWindowStart(void) const
{
    return windowStart;
}

uint8_t LCDML3_CheckList::getVisibleRows(void) const
{
    return rows;
}

bool LCDML3_CheckList::isVisible(uint8_t index) const
{
    return index >= windowStart && index < (uint8_t)(windowStart + rows);
}

void LCDML3_CheckList::keepCursorVisible(void)
{
    if(cursor < windowStart) windowStart = cursor;
    if(cursor >= (uint8_t)(windowStart + rows)) windowStart = cursor - rows + 1;
}

LCDML3_StateButton::LCDML3_StateButton()
{
    begin(2, 0);
}

void LCDML3_StateButton::begin(uint8_t stateCount, uint8_t initialState)
{
    count = stateCount < 2 ? 2 : stateCount;
    if(count > 3) count = 3;
    state = initialState >= count ? 0 : initialState;
}

void LCDML3_StateButton::next(void)
{
    state = state + 1 >= count ? 0 : state + 1;
}

void LCDML3_StateButton::previous(void)
{
    state = state == 0 ? count - 1 : state - 1;
}

void LCDML3_StateButton::set(uint8_t newState)
{
    if(newState < count) state = newState;
}

uint8_t LCDML3_StateButton::get(void) const
{
    return state;
}

bool LCDML3_StateButton::isOn(void) const
{
    return state == LCDML3_STATE_ON || (count == 2 && state == 1);
}

bool LCDML3_StateButton::isAuto(void) const
{
    return count == 3 && state == LCDML3_STATE_AUTO;
}

bool LCDML3_StateButton::isOff(void) const
{
    return state == LCDML3_STATE_OFF;
}

void LCDML3_StateButton::label(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;

    if(count == 2)
    {
        snprintf(buffer, size, "%s", state == 0 ? "OFF" : "ON");
    }
    else
    {
        const char *labels[] = {"OFF", "AUTO", "ON"};
        snprintf(buffer, size, "%s", labels[state]);
    }
}

LCDML3_NumericEditor::LCDML3_NumericEditor()
{
    begin(0, 0, 100, 1, false);
}

void LCDML3_NumericEditor::begin(int32_t initialValue, int32_t minValue, int32_t maxValue, int32_t stepValue, bool wrapEnabled)
{
    minVal = minValue;
    maxVal = maxValue;
    step = stepValue == 0 ? 1 : lcdml3_abs32(stepValue);
    wrap = wrapEnabled;
    value = initialValue;
    normalize();
}

void LCDML3_NumericEditor::increment(void)
{
    value += step;
    if(value > maxVal) value = wrap ? minVal : maxVal;
}

void LCDML3_NumericEditor::decrement(void)
{
    value -= step;
    if(value < minVal) value = wrap ? maxVal : minVal;
}

void LCDML3_NumericEditor::setValue(int32_t newValue)
{
    value = newValue;
    normalize();
}

void LCDML3_NumericEditor::setBounds(int32_t minValue, int32_t maxValue)
{
    minVal = minValue;
    maxVal = maxValue;
    normalize();
}

void LCDML3_NumericEditor::setStep(int32_t stepValue)
{
    step = stepValue == 0 ? 1 : lcdml3_abs32(stepValue);
}

void LCDML3_NumericEditor::setWrap(bool enabled)
{
    wrap = enabled;
}

int32_t LCDML3_NumericEditor::getValue(void) const { return value; }
int32_t LCDML3_NumericEditor::getMin(void) const { return minVal; }
int32_t LCDML3_NumericEditor::getMax(void) const { return maxVal; }
int32_t LCDML3_NumericEditor::getStep(void) const { return step; }

void LCDML3_NumericEditor::format(char *buffer, size_t size, const char *suffix) const
{
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "%ld%s", (long)value, suffix == NULL ? "" : suffix);
}

void LCDML3_NumericEditor::normalize(void)
{
    if(minVal > maxVal)
    {
        int32_t tmp = minVal;
        minVal = maxVal;
        maxVal = tmp;
    }
    if(value < minVal) value = minVal;
    if(value > maxVal) value = maxVal;
}

LCDML3_FloatEditor::LCDML3_FloatEditor()
{
    begin(0.0f, 0.0f, 100.0f, 0.1f, 1, false);
}

void LCDML3_FloatEditor::begin(float initialValue, float minValue, float maxValue, float stepValue, uint8_t decimalPrecision, bool wrapEnabled)
{
    minVal = minValue;
    maxVal = maxValue;
    step = stepValue == 0.0f ? 0.1f : lcdml3_absFloat(stepValue);
    precision = decimalPrecision > 6 ? 6 : decimalPrecision;
    wrap = wrapEnabled;
    value = initialValue;
    normalize();
}

void LCDML3_FloatEditor::increment(void)
{
    value += step;
    if(value > maxVal) value = wrap ? minVal : maxVal;
}

void LCDML3_FloatEditor::decrement(void)
{
    value -= step;
    if(value < minVal) value = wrap ? maxVal : minVal;
}

void LCDML3_FloatEditor::setValue(float newValue)
{
    value = newValue;
    normalize();
}

void LCDML3_FloatEditor::setBounds(float minValue, float maxValue)
{
    minVal = minValue;
    maxVal = maxValue;
    normalize();
}

void LCDML3_FloatEditor::setStep(float stepValue)
{
    step = stepValue == 0.0f ? 0.1f : lcdml3_absFloat(stepValue);
}

void LCDML3_FloatEditor::setPrecision(uint8_t decimalPrecision)
{
    precision = decimalPrecision > 6 ? 6 : decimalPrecision;
}

void LCDML3_FloatEditor::setWrap(bool enabled)
{
    wrap = enabled;
}

float LCDML3_FloatEditor::getValue(void) const { return value; }
uint8_t LCDML3_FloatEditor::getPrecision(void) const { return precision; }

void LCDML3_FloatEditor::format(char *buffer, size_t size, const char *suffix) const
{
    if(buffer == NULL || size == 0) return;
    char valueText[18];
    dtostrf(value, 0, precision, valueText);
    snprintf(buffer, size, "%s%s", valueText, suffix == NULL ? "" : suffix);
}

void LCDML3_FloatEditor::normalize(void)
{
    if(minVal > maxVal)
    {
        float tmp = minVal;
        minVal = maxVal;
        maxVal = tmp;
    }
    if(value < minVal) value = minVal;
    if(value > maxVal) value = maxVal;
}

LCDML3_IPAddressEditor::LCDML3_IPAddressEditor()
{
    begin();
}

void LCDML3_IPAddressEditor::begin(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    octets[0] = a;
    octets[1] = b;
    octets[2] = c;
    octets[3] = d;
    field = 0;
}

void LCDML3_IPAddressEditor::nextField(void) { field = lcdml3_wrapIncrement(field, 3); }
void LCDML3_IPAddressEditor::previousField(void) { field = lcdml3_wrapDecrement(field, 3); }
void LCDML3_IPAddressEditor::increment(void) { octets[field] = lcdml3_wrapIncrement(octets[field], 255); }
void LCDML3_IPAddressEditor::decrement(void) { octets[field] = lcdml3_wrapDecrement(octets[field], 255); }
void LCDML3_IPAddressEditor::setOctet(uint8_t index, uint8_t octetValue) { if(index < 4) octets[index] = octetValue; }
uint8_t LCDML3_IPAddressEditor::getOctet(uint8_t index) const { return index < 4 ? octets[index] : 0; }
uint8_t LCDML3_IPAddressEditor::getField(void) const { return field; }

void LCDML3_IPAddressEditor::getBytes(uint8_t out[4]) const
{
    if(out == NULL) return;
    for(uint8_t i = 0; i < 4; i++) out[i] = octets[i];
}

void LCDML3_IPAddressEditor::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "%u.%u.%u.%u", octets[0], octets[1], octets[2], octets[3]);
}

LCDML3_TextEditor::LCDML3_TextEditor()
{
    text = NULL;
    cap = 0;
    cursor = 0;
    chars = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-";
    password = false;
}

void LCDML3_TextEditor::begin(char *buffer, uint8_t capacity, const char *alphabet, bool passwordMode)
{
    text = buffer;
    cap = capacity;
    cursor = 0;
    chars = alphabet == NULL ? " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-" : alphabet;
    password = passwordMode;
    if(text != NULL && cap > 0) text[cap - 1] = '\0';
}

void LCDML3_TextEditor::nextChar(void)
{
    if(text == NULL || cap == 0 || chars == NULL) return;
    int16_t idx = alphabetIndex(text[cursor]);
    uint8_t len = strlen(chars);
    if(len == 0) return;
    idx = (idx + 1) % len;
    text[cursor] = chars[idx];
}

void LCDML3_TextEditor::previousChar(void)
{
    if(text == NULL || cap == 0 || chars == NULL) return;
    int16_t idx = alphabetIndex(text[cursor]);
    uint8_t len = strlen(chars);
    if(len == 0) return;
    idx = idx <= 0 ? len - 1 : idx - 1;
    text[cursor] = chars[idx];
}

void LCDML3_TextEditor::nextPosition(void)
{
    if(cap == 0) return;
    cursor = cursor + 1 >= (cap - 1) ? 0 : cursor + 1;
}

void LCDML3_TextEditor::previousPosition(void)
{
    if(cap == 0) return;
    cursor = cursor == 0 ? cap - 2 : cursor - 1;
}

void LCDML3_TextEditor::clear(void)
{
    if(text == NULL || cap == 0) return;
    memset(text, 0, cap);
    cursor = 0;
}

const char *LCDML3_TextEditor::getText(void) const { return text == NULL ? "" : text; }
uint8_t LCDML3_TextEditor::getCursor(void) const { return cursor; }
bool LCDML3_TextEditor::isPassword(void) const { return password; }

void LCDML3_TextEditor::format(char *out, size_t size) const
{
    if(out == NULL || size == 0) return;
    if(text == NULL)
    {
        out[0] = '\0';
        return;
    }
    if(password)
    {
        size_t len = strlen(text);
        if(len >= size) len = size - 1;
        for(size_t i = 0; i < len; i++) out[i] = '*';
        out[len] = '\0';
    }
    else
    {
        lcdml3_copyText(out, size, text);
    }
}

int16_t LCDML3_TextEditor::alphabetIndex(char c) const
{
    if(chars == NULL) return 0;
    for(uint8_t i = 0; chars[i] != '\0'; i++)
    {
        if(chars[i] == c) return i;
    }
    return 0;
}

LCDML3_WiFiMenu::LCDML3_WiFiMenu()
{
    begin();
}

void LCDML3_WiFiMenu::begin(void)
{
    setCredentials("", "");
    state = LCDML3_NET_IDLE;
    selectedNetwork = 0;
}

void LCDML3_WiFiMenu::setCredentials(const char *ssid, const char *password)
{
    lcdml3_copyText(credentials.ssid, sizeof(credentials.ssid), ssid);
    lcdml3_copyText(credentials.password, sizeof(credentials.password), password);
}

LCDML3_WiFiCredentials LCDML3_WiFiMenu::getCredentials(void) const { return credentials; }
void LCDML3_WiFiMenu::setState(LCDML3_NetworkMenuState newState) { state = newState; }
LCDML3_NetworkMenuState LCDML3_WiFiMenu::getState(void) const { return state; }
void LCDML3_WiFiMenu::setSelectedNetwork(uint8_t index) { selectedNetwork = index; }
uint8_t LCDML3_WiFiMenu::getSelectedNetwork(void) const { return selectedNetwork; }

void LCDML3_WiFiMenu::formatStatus(char *buffer, size_t size) const
{
    const char *labels[] = {"Idle", "Scan", "Connect", "Connected", "Disconnect", "Error"};
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "WiFi %s #%u", labels[state], selectedNetwork);
}

LCDML3_BluetoothMenu::LCDML3_BluetoothMenu()
{
    begin();
}

void LCDML3_BluetoothMenu::begin(void)
{
    state = LCDML3_BT_IDLE;
    selectedDevice = 0;
    bleMode = false;
}

void LCDML3_BluetoothMenu::setState(LCDML3_BluetoothMenuState newState) { state = newState; }
LCDML3_BluetoothMenuState LCDML3_BluetoothMenu::getState(void) const { return state; }
void LCDML3_BluetoothMenu::nextAction(void) { state = (LCDML3_BluetoothMenuState)lcdml3_wrapIncrement((uint8_t)state, LCDML3_BT_DISCONNECT); }
void LCDML3_BluetoothMenu::previousAction(void) { state = (LCDML3_BluetoothMenuState)lcdml3_wrapDecrement((uint8_t)state, LCDML3_BT_DISCONNECT); }
void LCDML3_BluetoothMenu::setSelectedDevice(uint8_t index) { selectedDevice = index; }
uint8_t LCDML3_BluetoothMenu::getSelectedDevice(void) const { return selectedDevice; }
void LCDML3_BluetoothMenu::setBleMode(bool enabled) { bleMode = enabled; }
bool LCDML3_BluetoothMenu::isBleMode(void) const { return bleMode; }

void LCDML3_BluetoothMenu::formatStatus(char *buffer, size_t size) const
{
    const char *labels[] = {"Idle", "Discover", "Search", "BLE scan", "Pair", "Connected", "Disconnect"};
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "%s %s #%u", bleMode ? "BLE" : "BT", labels[state], selectedDevice);
}

LCDML3_MenuHeader::LCDML3_MenuHeader()
{
    begin("");
}

void LCDML3_MenuHeader::begin(const char *headerTitle, const char *headerSubtitle, uint8_t headerLevel)
{
    title = headerTitle == NULL ? "" : headerTitle;
    subtitle = headerSubtitle == NULL ? "" : headerSubtitle;
    level = headerLevel;
}

void LCDML3_MenuHeader::setTitle(const char *headerTitle) { title = headerTitle == NULL ? "" : headerTitle; }
void LCDML3_MenuHeader::setSubtitle(const char *headerSubtitle) { subtitle = headerSubtitle == NULL ? "" : headerSubtitle; }
void LCDML3_MenuHeader::setLevel(uint8_t headerLevel) { level = headerLevel; }
const char *LCDML3_MenuHeader::getTitle(void) const { return title; }
const char *LCDML3_MenuHeader::getSubtitle(void) const { return subtitle; }
uint8_t LCDML3_MenuHeader::getLevel(void) const { return level; }

void LCDML3_MenuHeader::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "%u:%s%s%s", level, title, subtitle[0] == '\0' ? "" : " - ", subtitle);
}

LCDML3_Theme::LCDML3_Theme()
{
    setColors(0xFFFF, 0x0000, 0x07E0, 0xF800);
    setSymbols(">", "[x]", "[ ]", "(o)", "( )");
}

void LCDML3_Theme::setColors(uint16_t foreground, uint16_t background, uint16_t accent, uint16_t warning)
{
    colorFg = foreground;
    colorBg = background;
    colorAccent = accent;
    colorWarning = warning;
}

void LCDML3_Theme::setSymbols(const char *cursor, const char *checked, const char *unchecked, const char *radioOn, const char *radioOff)
{
    symCursor = cursor == NULL ? ">" : cursor;
    symChecked = checked == NULL ? "[x]" : checked;
    symUnchecked = unchecked == NULL ? "[ ]" : unchecked;
    symRadioOn = radioOn == NULL ? "(o)" : radioOn;
    symRadioOff = radioOff == NULL ? "( )" : radioOff;
}

uint16_t LCDML3_Theme::fg(void) const { return colorFg; }
uint16_t LCDML3_Theme::bg(void) const { return colorBg; }
uint16_t LCDML3_Theme::accentColor(void) const { return colorAccent; }
uint16_t LCDML3_Theme::warningColor(void) const { return colorWarning; }
const char *LCDML3_Theme::cursorSymbol(void) const { return symCursor; }
const char *LCDML3_Theme::checkedSymbol(void) const { return symChecked; }
const char *LCDML3_Theme::uncheckedSymbol(void) const { return symUnchecked; }
const char *LCDML3_Theme::radioOnSymbol(void) const { return symRadioOn; }
const char *LCDML3_Theme::radioOffSymbol(void) const { return symRadioOff; }

LCDML3_DebugMenu::LCDML3_DebugMenu()
{
    begin(13);
}

void LCDML3_DebugMenu::begin(uint8_t debugPin) { pin = debugPin; }
void LCDML3_DebugMenu::setPin(uint8_t debugPin) { pin = debugPin; }
uint8_t LCDML3_DebugMenu::getPin(void) const { return pin; }
void LCDML3_DebugMenu::modeInput(bool pullup) { pinMode(pin, pullup ? INPUT_PULLUP : INPUT); }
void LCDML3_DebugMenu::modeOutput(void) { pinMode(pin, OUTPUT); }
void LCDML3_DebugMenu::write(bool high) { digitalWrite(pin, high ? HIGH : LOW); }
int LCDML3_DebugMenu::readDigital(void) const { return digitalRead(pin); }
int LCDML3_DebugMenu::readAnalog(void) const { return analogRead(pin); }
void LCDML3_DebugMenu::serialWrite(Stream &serial, const char *message) { serial.print(message == NULL ? "" : message); }

void LCDML3_DebugMenu::formatPin(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "GPIO %u D=%d A=%d", pin, readDigital(), readAnalog());
}

LCDML3_StatusBar::LCDML3_StatusBar()
{
    mask = 0;
}

void LCDML3_StatusBar::setIcon(uint8_t icon, bool enabled)
{
    if(icon >= 16) return;
    if(enabled) mask |= (uint16_t)(1U << icon);
    else mask &= (uint16_t)~(1U << icon);
}

void LCDML3_StatusBar::toggleIcon(uint8_t icon)
{
    if(icon >= 16) return;
    mask ^= (uint16_t)(1U << icon);
}

bool LCDML3_StatusBar::isIconEnabled(uint8_t icon) const
{
    if(icon >= 16) return false;
    return (mask & (uint16_t)(1U << icon)) != 0;
}

uint16_t LCDML3_StatusBar::getMask(void) const { return mask; }
void LCDML3_StatusBar::setMask(uint16_t newMask) { mask = newMask; }

void LCDML3_StatusBar::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    buffer[0] = '\0';
    const char *labels[] = {"WiFi", "BT", "BLE", "SD", "Lock", "Warn", "Busy", "User"};
    for(uint8_t i = 0; i < 8; i++)
    {
        if(isIconEnabled(i))
        {
            if(buffer[0] != '\0') strncat(buffer, " ", size - strlen(buffer) - 1);
            strncat(buffer, labels[i], size - strlen(buffer) - 1);
        }
    }
}

LCDML3_ConfirmDialog::LCDML3_ConfirmDialog()
{
    begin(false);
}

void LCDML3_ConfirmDialog::begin(bool defaultOk)
{
    okSelected = defaultOk;
    result = LCDML3_CONFIRM_NONE;
}

void LCDML3_ConfirmDialog::toggle(void) { okSelected = !okSelected; }
void LCDML3_ConfirmDialog::chooseOk(void) { okSelected = true; }
void LCDML3_ConfirmDialog::chooseCancel(void) { okSelected = false; }
void LCDML3_ConfirmDialog::confirm(void) { result = okSelected ? LCDML3_CONFIRM_OK : LCDML3_CONFIRM_CANCEL; }
bool LCDML3_ConfirmDialog::isOkSelected(void) const { return okSelected; }
LCDML3_ConfirmResult LCDML3_ConfirmDialog::getResult(void) const { return result; }
bool LCDML3_ConfirmDialog::isDone(void) const { return result != LCDML3_CONFIRM_NONE; }
void LCDML3_ConfirmDialog::reset(void) { result = LCDML3_CONFIRM_NONE; }

void LCDML3_ConfirmDialog::format(char *buffer, size_t size, const char *message) const
{
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "%s %sCancel %sOK", message == NULL ? "Confirm?" : message, okSelected ? " " : ">", okSelected ? ">" : " ");
}

LCDML3_PinEditor::LCDML3_PinEditor()
{
    begin(4, '0');
}

void LCDML3_PinEditor::begin(uint8_t pinLength, char fill)
{
    len = pinLength < 1 ? 1 : pinLength;
    if(len > 8) len = 8;
    field = 0;
    for(uint8_t i = 0; i < len; i++) digits[i] = (fill >= '0' && fill <= '9') ? fill : '0';
    digits[len] = '\0';
}

void LCDML3_PinEditor::nextField(void) { field = lcdml3_wrapIncrement(field, len - 1); }
void LCDML3_PinEditor::previousField(void) { field = lcdml3_wrapDecrement(field, len - 1); }
void LCDML3_PinEditor::increment(void) { digits[field] = digits[field] >= '9' ? '0' : digits[field] + 1; }
void LCDML3_PinEditor::decrement(void) { digits[field] = digits[field] <= '0' ? '9' : digits[field] - 1; }
void LCDML3_PinEditor::setDigit(uint8_t index, uint8_t digit) { if(index < len && digit <= 9) digits[index] = (char)('0' + digit); }
uint8_t LCDML3_PinEditor::getDigit(uint8_t index) const { return index < len ? (uint8_t)(digits[index] - '0') : 0; }
uint8_t LCDML3_PinEditor::getField(void) const { return field; }
uint8_t LCDML3_PinEditor::length(void) const { return len; }
bool LCDML3_PinEditor::equals(const char *pinText) const { return pinText != NULL && strncmp(digits, pinText, len) == 0 && pinText[len] == '\0'; }

void LCDML3_PinEditor::format(char *buffer, size_t size, bool masked) const
{
    if(buffer == NULL || size == 0) return;
    uint8_t copyLen = len;
    if(copyLen >= size) copyLen = size - 1;
    for(uint8_t i = 0; i < copyLen; i++) buffer[i] = masked ? '*' : digits[i];
    buffer[copyLen] = '\0';
}

LCDML3_ProgressScreen::LCDML3_ProgressScreen()
{
    begin(100, false);
}

void LCDML3_ProgressScreen::begin(uint32_t totalValue, bool indeterminateMode)
{
    value = 0;
    total = totalValue == 0 ? 1 : totalValue;
    indeterminate = indeterminateMode;
    animFrame = 0;
}

void LCDML3_ProgressScreen::set(uint32_t newValue) { value = newValue > total ? total : newValue; }
void LCDML3_ProgressScreen::add(uint32_t delta) { set(value + delta); }
void LCDML3_ProgressScreen::setTotal(uint32_t totalValue) { total = totalValue == 0 ? 1 : totalValue; if(value > total) value = total; }
void LCDML3_ProgressScreen::setIndeterminate(bool enabled) { indeterminate = enabled; }
bool LCDML3_ProgressScreen::isDone(void) const { return !indeterminate && value >= total; }
uint8_t LCDML3_ProgressScreen::percent(void) const { return indeterminate ? 0 : (uint8_t)((value * 100UL) / total); }
uint8_t LCDML3_ProgressScreen::frame(void) { animFrame = (animFrame + 1) & 0x03; return animFrame; }

void LCDML3_ProgressScreen::format(char *buffer, size_t size, const char *label) const
{
    if(buffer == NULL || size == 0) return;
    if(indeterminate) snprintf(buffer, size, "%s ...", label == NULL ? "Working" : label);
    else snprintf(buffer, size, "%s %u%%", label == NULL ? "Progress" : label, percent());
}

LCDML3_Wizard::LCDML3_Wizard()
{
    begin(1);
}

void LCDML3_Wizard::begin(uint8_t stepCount)
{
    count = stepCount == 0 ? 1 : stepCount;
    if(count > 32) count = 32;
    step = 0;
    completedMask = 0;
}

void LCDML3_Wizard::next(void) { if(step + 1 < count) step++; }
void LCDML3_Wizard::previous(void) { if(step > 0) step--; }
void LCDML3_Wizard::goTo(uint8_t newStep) { if(newStep < count) step = newStep; }

void LCDML3_Wizard::markComplete(uint8_t targetStep, bool complete)
{
    if(targetStep >= count) return;
    if(complete) completedMask |= (1UL << targetStep);
    else completedMask &= ~(1UL << targetStep);
}

bool LCDML3_Wizard::isComplete(uint8_t targetStep) const
{
    return targetStep < count && (completedMask & (1UL << targetStep)) != 0;
}

bool LCDML3_Wizard::isLast(void) const { return step + 1 >= count; }
uint8_t LCDML3_Wizard::getStep(void) const { return step; }
uint8_t LCDML3_Wizard::getStepCount(void) const { return count; }
uint32_t LCDML3_Wizard::getCompletedMask(void) const { return completedMask; }

LCDML3_SettingsAdapter::LCDML3_SettingsAdapter()
{
    begin(NULL, NULL, NULL);
}

void LCDML3_SettingsAdapter::begin(LCDML3_SettingsReadFn reader, LCDML3_SettingsWriteFn writer, LCDML3_SettingsCommitFn committer)
{
    readFn = reader;
    writeFn = writer;
    commitFn = committer;
}

bool LCDML3_SettingsAdapter::available(void) const
{
    return readFn != NULL && writeFn != NULL;
}

uint8_t LCDML3_SettingsAdapter::readByte(uint16_t address, uint8_t fallback) const
{
    return readFn == NULL ? fallback : readFn(address);
}

void LCDML3_SettingsAdapter::writeByte(uint16_t address, uint8_t byteValue)
{
    if(writeFn != NULL) writeFn(address, byteValue);
}

void LCDML3_SettingsAdapter::readBytes(uint16_t address, uint8_t *buffer, uint16_t length) const
{
    if(buffer == NULL) return;
    for(uint16_t i = 0; i < length; i++) buffer[i] = readByte(address + i, 0);
}

void LCDML3_SettingsAdapter::writeBytes(uint16_t address, const uint8_t *buffer, uint16_t length)
{
    if(buffer == NULL) return;
    for(uint16_t i = 0; i < length; i++) writeByte(address + i, buffer[i]);
}

int32_t LCDML3_SettingsAdapter::readInt32(uint16_t address, int32_t fallback) const
{
    if(readFn == NULL) return fallback;
    int32_t result = 0;
    readBytes(address, (uint8_t *)&result, sizeof(result));
    return result;
}

void LCDML3_SettingsAdapter::writeInt32(uint16_t address, int32_t intValue)
{
    writeBytes(address, (const uint8_t *)&intValue, sizeof(intValue));
}

float LCDML3_SettingsAdapter::readFloat(uint16_t address, float fallback) const
{
    if(readFn == NULL) return fallback;
    float result = 0.0f;
    readBytes(address, (uint8_t *)&result, sizeof(result));
    return result;
}

void LCDML3_SettingsAdapter::writeFloat(uint16_t address, float floatValue)
{
    writeBytes(address, (const uint8_t *)&floatValue, sizeof(floatValue));
}

void LCDML3_SettingsAdapter::commit(void)
{
    if(commitFn != NULL) commitFn();
}

LCDML3_RotaryEncoderHelper::LCDML3_RotaryEncoderHelper() { begin(); }

void LCDML3_RotaryEncoderHelper::begin(uint16_t slow, uint16_t fast, uint16_t threshold)
{
    slowStep = slow == 0 ? 1 : slow;
    fastStep = fast < slowStep ? slowStep : fast;
    fastThresholdMs = threshold;
    reset();
}

int16_t LCDML3_RotaryEncoderHelper::update(int8_t direction, unsigned long nowMs)
{
    if(direction == 0) return 0;
    lastStep = (lastMs != 0 && (nowMs - lastMs) <= fastThresholdMs) ? fastStep : slowStep;
    lastMs = nowMs;
    return direction > 0 ? (int16_t)lastStep : -(int16_t)lastStep;
}

void LCDML3_RotaryEncoderHelper::reset(void) { lastMs = 0; lastStep = slowStep; }
uint16_t LCDML3_RotaryEncoderHelper::getLastStep(void) const { return lastStep; }

LCDML3_TouchMenu::LCDML3_TouchMenu() { begin(NULL, 0); }

void LCDML3_TouchMenu::begin(LCDML3_Hitbox *hitboxes, uint8_t itemCount)
{
    boxes = hitboxes;
    count = itemCount > 32 ? 32 : itemCount;
    enabledMask = count >= 32 ? 0xFFFFFFFFUL : ((1UL << count) - 1UL);
}

int8_t LCDML3_TouchMenu::hit(int16_t px, int16_t py) const
{
    if(boxes == NULL) return -1;
    for(uint8_t i = 0; i < count; i++)
    {
        if(isEnabled(i) && px >= boxes[i].x && py >= boxes[i].y && px < boxes[i].x + boxes[i].w && py < boxes[i].y + boxes[i].h)
        {
            return boxes[i].id;
        }
    }
    return -1;
}

void LCDML3_TouchMenu::setEnabled(uint8_t index, bool enabled)
{
    if(index >= count) return;
    if(enabled) enabledMask |= (1UL << index);
    else enabledMask &= ~(1UL << index);
}

bool LCDML3_TouchMenu::isEnabled(uint8_t index) const
{
    return index < count && (enabledMask & (1UL << index)) != 0;
}

LCDML3_Sparkline::LCDML3_Sparkline() { begin(0, 100); }

void LCDML3_Sparkline::begin(int16_t minValue, int16_t maxValue)
{
    minVal = minValue;
    maxVal = maxValue == minValue ? minValue + 1 : maxValue;
    count = 0;
    head = 0;
}

void LCDML3_Sparkline::add(int16_t value)
{
    values[head] = value;
    head = (head + 1) % 24;
    if(count < 24) count++;
}

uint8_t LCDML3_Sparkline::size(void) const { return count; }

int16_t LCDML3_Sparkline::get(uint8_t index) const
{
    if(index >= count) return 0;
    uint8_t start = (head + 24 - count) % 24;
    return values[(start + index) % 24];
}

uint8_t LCDML3_Sparkline::normalized(uint8_t index, uint8_t height) const
{
    if(height == 0) return 0;
    int16_t value = get(index);
    if(value < minVal) value = minVal;
    if(value > maxVal) value = maxVal;
    return (uint8_t)(((long)(value - minVal) * (height - 1)) / (maxVal - minVal));
}

void LCDML3_Sparkline::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    uint8_t n = count < (size - 1) ? count : (uint8_t)(size - 1);
    for(uint8_t i = 0; i < n; i++)
    {
        uint8_t v = normalized(i, 4);
        buffer[i] = v == 0 ? '_' : (v == 1 ? '-' : (v == 2 ? '=' : '#'));
    }
    buffer[n] = '\0';
}

LCDML3_LogViewer::LCDML3_LogViewer() { clear(); filter = LCDML3_LOG_INFO; }

void LCDML3_LogViewer::clear(void) { count = 0; head = 0; }

void LCDML3_LogViewer::add(LCDML3_LogLevel level, const char *message)
{
    entries[head].level = level;
    lcdml3_copyText(entries[head].message, sizeof(entries[head].message), message);
    head = (head + 1) % 12;
    if(count < 12) count++;
}

void LCDML3_LogViewer::setFilter(LCDML3_LogLevel minLevel) { filter = minLevel; }
LCDML3_LogLevel LCDML3_LogViewer::getFilter(void) const { return filter; }

uint8_t LCDML3_LogViewer::countVisible(void) const
{
    uint8_t visible = 0;
    for(uint8_t i = 0; i < count; i++)
    {
        LCDML3_LogEntry entry;
        uint8_t start = (head + 12 - count) % 12;
        entry = entries[(start + i) % 12];
        if(entry.level >= filter) visible++;
    }
    return visible;
}

bool LCDML3_LogViewer::getVisible(uint8_t visibleIndex, LCDML3_LogEntry &out) const
{
    uint8_t visible = 0;
    uint8_t start = (head + 12 - count) % 12;
    for(uint8_t i = 0; i < count; i++)
    {
        LCDML3_LogEntry entry = entries[(start + i) % 12];
        if(entry.level >= filter)
        {
            if(visible == visibleIndex)
            {
                out = entry;
                return true;
            }
            visible++;
        }
    }
    return false;
}

LCDML3_AlarmScheduler::LCDML3_AlarmScheduler() { begin(); }

void LCDML3_AlarmScheduler::begin(void)
{
    for(uint8_t i = 0; i < 8; i++) set(i, 0, 0, 0, false);
}

void LCDML3_AlarmScheduler::set(uint8_t index, uint8_t hour, uint8_t minute, uint8_t daysMask, bool enabled)
{
    if(index >= 8) return;
    alarms[index].hour = hour > 23 ? 23 : hour;
    alarms[index].minute = minute > 59 ? 59 : minute;
    alarms[index].daysMask = daysMask;
    alarms[index].enabled = enabled;
}

LCDML3_Alarm LCDML3_AlarmScheduler::get(uint8_t index) const
{
    LCDML3_Alarm empty = {0, 0, 0, false};
    return index < 8 ? alarms[index] : empty;
}

bool LCDML3_AlarmScheduler::matches(uint8_t index, uint8_t hour, uint8_t minute, uint8_t dayBit) const
{
    if(index >= 8) return false;
    return alarms[index].enabled && alarms[index].hour == hour && alarms[index].minute == minute && (alarms[index].daysMask & dayBit) != 0;
}

uint8_t LCDML3_AlarmScheduler::count(void) const { return 8; }

LCDML3_UnitSelector::LCDML3_UnitSelector() { begin(NULL, 0, 0); }

void LCDML3_UnitSelector::begin(const char **unitLabels, uint8_t unitCount, uint8_t selectedIndex)
{
    units = unitLabels;
    count = unitCount;
    selected = (count == 0 || selectedIndex >= count) ? 0 : selectedIndex;
}

void LCDML3_UnitSelector::next(void) { if(count > 0) selected = (selected + 1) % count; }
void LCDML3_UnitSelector::previous(void) { if(count > 0) selected = selected == 0 ? count - 1 : selected - 1; }
uint8_t LCDML3_UnitSelector::getSelected(void) const { return selected; }
const char *LCDML3_UnitSelector::getLabel(void) const { return (units == NULL || count == 0) ? "" : units[selected]; }

LCDML3_OTAStatus::LCDML3_OTAStatus() { begin(); }
void LCDML3_OTAStatus::begin(void) { state = LCDML3_OTA_IDLE; progress = 0; }
void LCDML3_OTAStatus::setState(LCDML3_OTAState newState) { state = newState; }
LCDML3_OTAState LCDML3_OTAStatus::getState(void) const { return state; }
void LCDML3_OTAStatus::setProgress(uint8_t percent) { progress = percent > 100 ? 100 : percent; }
uint8_t LCDML3_OTAStatus::getProgress(void) const { return progress; }

void LCDML3_OTAStatus::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    const char *labels[] = {"Idle", "Checking", "Download", "Flashing", "Done", "Error"};
    snprintf(buffer, size, "OTA %s %u%%", labels[state], progress);
}

LCDML3_CalibrationWizard::LCDML3_CalibrationWizard() { begin(2); }

void LCDML3_CalibrationWizard::begin(uint8_t pointCount)
{
    points = pointCount < 2 ? 2 : (pointCount > 4 ? 4 : pointCount);
    reset();
}

void LCDML3_CalibrationWizard::captureRaw(uint8_t point, int32_t raw, int32_t reference)
{
    if(point >= points) return;
    rawValues[point] = raw;
    refValues[point] = reference;
    capturedMask |= (1 << point);
}

int32_t LCDML3_CalibrationWizard::apply(int32_t raw) const
{
    if(!isReady() || rawValues[1] == rawValues[0]) return raw;
    return refValues[0] + ((raw - rawValues[0]) * (refValues[1] - refValues[0])) / (rawValues[1] - rawValues[0]);
}

void LCDML3_CalibrationWizard::reset(void)
{
    capturedMask = 0;
    for(uint8_t i = 0; i < 4; i++) { rawValues[i] = 0; refValues[i] = 0; }
}

bool LCDML3_CalibrationWizard::isReady(void) const
{
    return (capturedMask & 0x03) == 0x03;
}

LCDML3_ActionMenu::LCDML3_ActionMenu() { begin(NULL); }
void LCDML3_ActionMenu::begin(LCDML3_ActionFn fn) { actionFn = fn; lastAction = 255; }
void LCDML3_ActionMenu::setAction(LCDML3_ActionFn fn) { actionFn = fn; }
void LCDML3_ActionMenu::trigger(uint8_t id) { lastAction = id; if(actionFn != NULL) actionFn(id); }
uint8_t LCDML3_ActionMenu::getLastAction(void) const { return lastAction; }

void LCDML3_applyThemePreset(LCDML3_Theme &theme, LCDML3_ThemePreset preset)
{
    switch(preset)
    {
        case LCDML3_THEME_LCD: theme.setColors(0xFFFF, 0x0000, 0x07E0, 0xF800); theme.setSymbols(">", "[x]", "[ ]", "(o)", "( )"); break;
        case LCDML3_THEME_OLED: theme.setColors(1, 0, 1, 1); theme.setSymbols(">", "*", "-", "@", "o"); break;
        case LCDML3_THEME_TFT_DARK: theme.setColors(0xFFFF, 0x0000, 0x07FF, 0xF800); theme.setSymbols(">", "[x]", "[ ]", "(o)", "( )"); break;
        case LCDML3_THEME_TFT_LIGHT: theme.setColors(0x0000, 0xFFFF, 0x001F, 0xF800); theme.setSymbols(">", "[x]", "[ ]", "(o)", "( )"); break;
        case LCDML3_THEME_HIGH_CONTRAST: theme.setColors(0xFFFF, 0x0000, 0xFFE0, 0xF800); theme.setSymbols(">>", "YES", "NO", "ON", "OFF"); break;
    }
}

LCDML3_SDFileMenu::LCDML3_SDFileMenu() { begin(4); }

void LCDML3_SDFileMenu::begin(uint8_t visibleRows)
{
    rows = visibleRows == 0 ? 1 : visibleRows;
    itemCount = 0;
    cursor = 0;
    selected = 255;
    windowStart = 0;
}

void LCDML3_SDFileMenu::setItemCount(uint8_t count) { itemCount = count; if(cursor >= itemCount) cursor = itemCount == 0 ? 0 : itemCount - 1; keepVisible(); }
void LCDML3_SDFileMenu::up(void) { if(itemCount == 0) return; cursor = cursor == 0 ? itemCount - 1 : cursor - 1; keepVisible(); }
void LCDML3_SDFileMenu::down(void) { if(itemCount == 0) return; cursor = cursor + 1 >= itemCount ? 0 : cursor + 1; keepVisible(); }
void LCDML3_SDFileMenu::select(uint8_t index) { if(index < itemCount) { selected = index; cursor = index; keepVisible(); } }
uint8_t LCDML3_SDFileMenu::getCursor(void) const { return cursor; }
uint8_t LCDML3_SDFileMenu::getSelected(void) const { return selected; }
uint8_t LCDML3_SDFileMenu::getWindowStart(void) const { return windowStart; }
uint8_t LCDML3_SDFileMenu::getVisibleRows(void) const { return rows; }

void LCDML3_SDFileMenu::keepVisible(void)
{
    if(cursor < windowStart) windowStart = cursor;
    if(cursor >= (uint8_t)(windowStart + rows)) windowStart = cursor - rows + 1;
}

LCDML3_DiagnosticMenu::LCDML3_DiagnosticMenu() { begin(); }
void LCDML3_DiagnosticMenu::begin(void) { i2cFound = 0; wifiFound = 0; heap = 0; uptimeMs = 0; }
void LCDML3_DiagnosticMenu::setI2CFound(uint8_t count) { i2cFound = count; }
void LCDML3_DiagnosticMenu::setWiFiFound(uint8_t count) { wifiFound = count; }
void LCDML3_DiagnosticMenu::setHeap(uint32_t heapBytes) { heap = heapBytes; }
void LCDML3_DiagnosticMenu::setUptime(unsigned long uptime) { uptimeMs = uptime; }

void LCDML3_DiagnosticMenu::format(char *buffer, size_t size) const
{
    if(buffer == NULL || size == 0) return;
    snprintf(buffer, size, "I2C:%u WiFi:%u Heap:%lu Up:%lus", i2cFound, wifiFound, (unsigned long)heap, uptimeMs / 1000UL);
}
