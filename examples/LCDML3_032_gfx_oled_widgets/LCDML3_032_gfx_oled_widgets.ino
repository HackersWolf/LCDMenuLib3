// ##########################################################################################################################
// ########### LCDML3 OLED 128X64 #################################################################################################
// ##########################################################################################################################
// Cannaduino-inspired LCDMenuLib3 example.
// Board/display target: Adafruit_GFX OLED
// This sketch renders a 128x64 style screen in Serial Monitor so it can compile without display hardware.

#include <Arduino.h>
#include <LCDMenuLib3.h>
#include <LCDMenuLib3_widgets.h>

#define EXAMPLE_TITLE "LCDML3 OLED 128X64"
#define EXAMPLE_BOARD "Adafruit_GFX OLED"
#define EXAMPLE_PROFILE PROFILE_OLED

#define PROFILE_SERIAL 0
#define PROFILE_DYNAMIC 1
#define PROFILE_ADVANCED 2
#define PROFILE_ALL 3
#define PROFILE_LCD20X4 4
#define PROFILE_OLED 5
#define PROFILE_ESP 6
#define PROFILE_DIAG 7

#define PAGE_TIME 0
#define PAGE_VALUES 1
#define PAGE_LISTS 2
#define PAGE_NETWORK 3
#define PAGE_SYSTEM 4
#define PAGE_DIAGNOSTIC 5
#define PAGE_STORAGE 6
#define PAGE_SECURITY 7
#define PAGE_COUNT 8

struct ExampleState {
    uint8_t page;
    char lastInput;
    bool redraw;
    unsigned long now;
    unsigned long lastClockMs;
    unsigned long lastSensorMs;
    unsigned long lastRenderMs;
    unsigned long renderIntervalMs;
    uint8_t clockHour;
    uint8_t clockMinute;
    uint8_t clockSecond;
    int16_t sensorValue;
    uint8_t lastAction;
};

ExampleState app = { EXAMPLE_PROFILE, 0, true, 0, 0, 0, 0, 500, 14, 32, 0, 256, 0 };

void controlBegin();
void controlLoop();
void controlConsumeHelp();
void logicBegin();
void logicLoop();
void menuDynamicHandleInput(char input);
void menuStaticBegin();
void menuStaticAbout();
void menuStaticDefaults();
void renderBegin();
void renderScreen();
void clockLoop();
void clockFormat(char *buffer, size_t size);
void tasksBegin();
void tasksLoop();
bool tasksShouldRender();

void printBootBanner() {
    Serial.println(F("################################################################"));
    Serial.println(F("# LCDMenuLib3 Cannaduino-style multi-file example"));
    Serial.print(F("# Example: "));
    Serial.println(F(EXAMPLE_TITLE));
    Serial.print(F("# Target : "));
    Serial.println(F(EXAMPLE_BOARD));
    Serial.println(F("################################################################"));
}

void setup() {
    Serial.begin(115200);
    while(!Serial && millis() < 2000) {}

    printBootBanner();
    controlBegin();
    logicBegin();
    menuStaticBegin();
    tasksBegin();
    renderBegin();
    menuStaticAbout();
}

void loop() {
    app.now = millis();
    controlLoop();
    clockLoop();
    logicLoop();
    tasksLoop();

    if(tasksShouldRender()) {
        renderScreen();
    }
}
