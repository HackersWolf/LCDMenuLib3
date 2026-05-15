#include <LCDMenuLib3.h>

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

LCDML3_WiFiMenu wifiMenu;
LCDML3_BluetoothMenu btMenu;
LCDML3_OTAStatus ota;
LCDML3_DiagnosticMenu diag;

void setup()
{
    Serial.begin(115200);
    wifiMenu.setCredentials("SSID", "PASSWORD");
    wifiMenu.setState(LCDML3_NET_IDLE);
    btMenu.setBleMode(true);
    btMenu.setState(LCDML3_BT_DISCOVER);
    ota.setState(LCDML3_OTA_CHECKING);
}

void loop()
{
    char text[48];

#if defined(ESP32) || defined(ESP8266)
    int networks = WiFi.scanNetworks();
    diag.setWiFiFound(networks < 0 ? 0 : networks);
    diag.setHeap(ESP.getFreeHeap());
#endif

    wifiMenu.formatStatus(text, sizeof(text));
    Serial.println(text);
    btMenu.formatStatus(text, sizeof(text));
    Serial.println(text);
    ota.setProgress((ota.getProgress() + 10) % 101);
    ota.format(text, sizeof(text));
    Serial.println(text);
    diag.setUptime(millis());
    diag.format(text, sizeof(text));
    Serial.println(text);

    delay(5000);
}
