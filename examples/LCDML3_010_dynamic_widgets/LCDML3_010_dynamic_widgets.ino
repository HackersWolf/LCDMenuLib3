#include <LCDMenuLib3.h>

LCDML3_TimeEditor clockEditor;
LCDML3_TimerEditor timerEditor;
LCDML3_DateEditor dateEditor;
LCDML3_RadioList modeRadio;
LCDML3_CheckList optionChecks;
LCDML3_StateButton onOffButton;
LCDML3_StateButton manualAutoButton;
LCDML3_StateButton onAutoOffButton;

const char *radioItems[] = {"Eco", "Comfort", "Boost", "Night", "Away", "Party"};
const char *checkItems[] = {"Pump", "Light", "Fan", "Buzzer", "Relay", "Alarm"};

void setup()
{
    Serial.begin(115200);
    while(!Serial) {}

    clockEditor.begin(12, 30, 0);
    timerEditor.begin(1, 15, 0);
    dateEditor.begin(2026, 5, 15);
    modeRadio.begin(6, 3, 1);
    optionChecks.begin(6, 3, 0b000101);
    onOffButton.begin(2, 1);
    manualAutoButton.begin(2, 0);
    onAutoOffButton.begin(3, LCDML3_STATE_AUTO);

    printHelp();
    renderAll();
}

void loop()
{
    if(Serial.available() == 0)
    {
        return;
    }

    char c = Serial.read();

    if(c == 'u')
    {
        clockEditor.increment();
        timerEditor.increment();
        dateEditor.increment();
        modeRadio.up();
        optionChecks.up();
    }
    else if(c == 'd')
    {
        clockEditor.decrement();
        timerEditor.decrement();
        dateEditor.decrement();
        modeRadio.down();
        optionChecks.down();
    }
    else if(c == 'l')
    {
        clockEditor.previousField();
        timerEditor.previousField();
        dateEditor.previousField();
        onOffButton.previous();
        manualAutoButton.previous();
        onAutoOffButton.previous();
    }
    else if(c == 'r')
    {
        clockEditor.nextField();
        timerEditor.nextField();
        dateEditor.nextField();
        onOffButton.next();
        manualAutoButton.next();
        onAutoOffButton.next();
    }
    else if(c == 'e')
    {
        modeRadio.selectCursor();
        optionChecks.toggleCursor();
    }
    else if(c == 'q')
    {
        printHelp();
    }

    renderAll();
}

void printHelp()
{
    Serial.println(F("LCDMenuLib3 dynamic widgets demo"));
    Serial.println(F("u/d: increment/decrement and list cursor"));
    Serial.println(F("l/r: previous/next field or button state"));
    Serial.println(F("e: select radio item and toggle checkbox"));
    Serial.println(F("q: help"));
}

void renderAll()
{
    char text[24];

    Serial.println();
    clockEditor.format(text, sizeof(text));
    Serial.print(F("Hour editor: "));
    Serial.print(text);
    Serial.print(F(" field="));
    Serial.println(clockEditor.getField());

    timerEditor.format(text, sizeof(text));
    Serial.print(F("Timer editor: "));
    Serial.print(text);
    Serial.print(F(" totalSeconds="));
    Serial.println(timerEditor.toSeconds());

    dateEditor.format(text, sizeof(text));
    Serial.print(F("Date editor: "));
    Serial.print(text);
    Serial.print(F(" field="));
    Serial.println(dateEditor.getField());

    Serial.println(F("Radio list window:"));
    for(uint8_t i = modeRadio.getWindowStart(); i < modeRadio.getWindowStart() + modeRadio.getVisibleRows() && i < 6; i++)
    {
        Serial.print(i == modeRadio.getCursor() ? F("> ") : F("  "));
        Serial.print(modeRadio.isSelected(i) ? F("(o) ") : F("( ) "));
        Serial.println(radioItems[i]);
    }

    Serial.println(F("Checklist window:"));
    for(uint8_t i = optionChecks.getWindowStart(); i < optionChecks.getWindowStart() + optionChecks.getVisibleRows() && i < 6; i++)
    {
        Serial.print(i == optionChecks.getCursor() ? F("> ") : F("  "));
        Serial.print(optionChecks.isChecked(i) ? F("[x] ") : F("[ ] "));
        Serial.println(checkItems[i]);
    }

    onOffButton.label(text, sizeof(text));
    Serial.print(F("On/Off button: "));
    Serial.println(text);

    manualAutoButton.label(text, sizeof(text));
    Serial.print(F("Manual/Auto button: "));
    Serial.println(manualAutoButton.get() == 0 ? F("MANUAL") : F("AUTO"));

    onAutoOffButton.label(text, sizeof(text));
    Serial.print(F("On/Auto/Off button: "));
    Serial.println(text);
}
