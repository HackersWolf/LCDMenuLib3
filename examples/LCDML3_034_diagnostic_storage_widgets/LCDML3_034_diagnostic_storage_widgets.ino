#include <LCDMenuLib3.h>
#include <EEPROM.h>

LCDML3_SettingsAdapter settings;
LCDML3_SDFileMenu fileMenu;
LCDML3_DiagnosticMenu diag;

uint8_t readSetting(uint16_t address)
{
    return EEPROM.read(address);
}

void writeSetting(uint16_t address, uint8_t value)
{
    EEPROM.write(address, value);
}

void commitSettings()
{
#if defined(ESP32) || defined(ESP8266)
    EEPROM.commit();
#endif
}

void setup()
{
    Serial.begin(115200);
#if defined(ESP32) || defined(ESP8266)
    EEPROM.begin(64);
#endif
    settings.begin(readSetting, writeSetting, commitSettings);
    fileMenu.begin(4);
    fileMenu.setItemCount(12);
    settings.writeInt32(0, 123456);
    settings.commit();
}

void loop()
{
    char text[48];
    fileMenu.down();
    diag.setI2CFound(2);
    diag.setHeap(1024);
    diag.setUptime(millis());

    Serial.print(F("Selected file index: "));
    Serial.println(fileMenu.getCursor());

    Serial.print(F("Stored int32: "));
    Serial.println(settings.readInt32(0));

    diag.format(text, sizeof(text));
    Serial.println(text);
    delay(1000);
}
