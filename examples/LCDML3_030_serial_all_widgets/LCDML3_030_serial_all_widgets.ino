#include <LCDMenuLib3.h>

LCDML3_RotaryEncoderHelper encoder;
LCDML3_Sparkline graph;
LCDML3_LogViewer logs;
LCDML3_AlarmScheduler alarms;
LCDML3_UnitSelector units;
LCDML3_OTAStatus ota;
LCDML3_CalibrationWizard calibration;
LCDML3_ActionMenu actions;
LCDML3_SDFileMenu files;
LCDML3_DiagnosticMenu diag;
LCDML3_Theme theme;

const char *unitLabels[] = {"C", "F", "%", "rpm"};

void actionCallback(uint8_t id)
{
    Serial.print(F("Action triggered: "));
    Serial.println(id);
}

void setup()
{
    Serial.begin(115200);
    while(!Serial) {}

    encoder.begin(1, 10, 100);
    graph.begin(0, 1023);
    logs.add(LCDML3_LOG_INFO, "Boot");
    logs.add(LCDML3_LOG_WARN, "Low battery");
    alarms.set(0, 7, 30, 0b0111110, true);
    units.begin(unitLabels, 4, 0);
    ota.setState(LCDML3_OTA_CHECKING);
    calibration.captureRaw(0, 100, 0);
    calibration.captureRaw(1, 900, 1000);
    actions.begin(actionCallback);
    files.begin(3);
    files.setItemCount(8);
    diag.setI2CFound(3);
    diag.setWiFiFound(5);
    diag.setHeap(20480);
    LCDML3_applyThemePreset(theme, LCDML3_THEME_HIGH_CONTRAST);
}

void loop()
{
    char text[64];

    int16_t delta = encoder.update(1, millis());
    graph.add((millis() / 10) % 1024);
    ota.setProgress((ota.getProgress() + 5) % 101);
    units.next();
    files.down();
    actions.trigger(files.getCursor());
    diag.setUptime(millis());

    Serial.print(F("Encoder delta: "));
    Serial.println(delta);

    graph.format(text, sizeof(text));
    Serial.print(F("Sparkline: "));
    Serial.println(text);

    LCDML3_LogEntry entry;
    if(logs.getVisible(0, entry))
    {
        Serial.print(F("Log: "));
        Serial.println(entry.message);
    }

    ota.format(text, sizeof(text));
    Serial.println(text);

    diag.format(text, sizeof(text));
    Serial.println(text);

    Serial.print(F("Unit: "));
    Serial.println(units.getLabel());

    Serial.print(F("Theme cursor: "));
    Serial.println(theme.cursorSymbol());

    delay(1000);
}
