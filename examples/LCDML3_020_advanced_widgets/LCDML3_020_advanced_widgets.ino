#include <LCDMenuLib3.h>

LCDML3_NumericEditor temperature;
LCDML3_FloatEditor pidKp;
LCDML3_IPAddressEditor ip;
LCDML3_WiFiMenu wifiMenu;
LCDML3_BluetoothMenu btMenu;
LCDML3_MenuHeader header;
LCDML3_Theme theme;
LCDML3_DebugMenu debugMenu;
LCDML3_StatusBar statusBar;
LCDML3_ConfirmDialog confirmDialog;
LCDML3_PinEditor pinEditor;
LCDML3_ProgressScreen progress;
LCDML3_Wizard wizard;

uint8_t settingsBytes[32];

uint8_t settingsRead(uint16_t address)
{
    return address < sizeof(settingsBytes) ? settingsBytes[address] : 0;
}

void settingsWrite(uint16_t address, uint8_t value)
{
    if(address < sizeof(settingsBytes)) settingsBytes[address] = value;
}

void settingsCommit()
{
    Serial.println(F("Settings committed"));
}

LCDML3_SettingsAdapter settings;

void setup()
{
    Serial.begin(115200);
    while(!Serial) {}

    temperature.begin(21, -20, 80, 1);
    pidKp.begin(1.25f, 0.0f, 10.0f, 0.05f, 2);
    ip.begin(192, 168, 4, 1);
    wifiMenu.setCredentials("MyWiFi", "secret");
    wifiMenu.setState(LCDML3_NET_SCAN);
    btMenu.setState(LCDML3_BT_DISCOVER);
    btMenu.setBleMode(true);
    header.begin("Settings", "Advanced", 1);
    theme.setSymbols(">", "[x]", "[ ]", "(o)", "( )");
    debugMenu.begin(13);
    statusBar.setIcon(LCDML3_ICON_WIFI, true);
    statusBar.setIcon(LCDML3_ICON_BT, true);
    confirmDialog.begin(false);
    pinEditor.begin(4);
    progress.begin(100);
    wizard.begin(4);
    settings.begin(settingsRead, settingsWrite, settingsCommit);

    settings.writeInt32(0, temperature.getValue());
    settings.writeFloat(4, pidKp.getValue());
    settings.commit();
}

void loop()
{
    char line[48];

    temperature.increment();
    pidKp.increment();
    ip.nextField();
    ip.increment();
    btMenu.nextAction();
    progress.add(5);
    wizard.markComplete(wizard.getStep(), true);
    wizard.next();

    header.format(line, sizeof(line));
    Serial.println(line);

    temperature.format(line, sizeof(line), " C");
    Serial.print(F("Temperature: "));
    Serial.println(line);

    pidKp.format(line, sizeof(line));
    Serial.print(F("PID Kp: "));
    Serial.println(line);

    ip.format(line, sizeof(line));
    Serial.print(F("IP: "));
    Serial.println(line);

    wifiMenu.formatStatus(line, sizeof(line));
    Serial.println(line);

    btMenu.formatStatus(line, sizeof(line));
    Serial.println(line);

    statusBar.format(line, sizeof(line));
    Serial.print(F("Status: "));
    Serial.println(line);

    progress.format(line, sizeof(line), "OTA");
    Serial.println(line);

    Serial.print(F("Wizard step: "));
    Serial.println(wizard.getStep());

    delay(1000);
}
