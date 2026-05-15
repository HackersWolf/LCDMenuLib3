#include <LCDMenuLib3.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
LCDML3_Sparkline graph;
LCDML3_Theme theme;
LCDML3_ProgressScreen progress;

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    graph.begin(0, 100);
    LCDML3_applyThemePreset(theme, LCDML3_THEME_OLED);
    progress.begin(100);
}

void loop()
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    graph.add((millis() / 50) % 101);
    progress.add(3);

    display.setCursor(0, 0);
    display.print(F("LCDML3 OLED"));
    display.setCursor(0, 10);
    display.print(theme.cursorSymbol());
    display.print(F(" Graph"));

    for(uint8_t i = 0; i < graph.size(); i++)
    {
        uint8_t y = 55 - graph.normalized(i, 32);
        display.drawPixel(i * 5, y, SSD1306_WHITE);
    }

    char text[24];
    progress.format(text, sizeof(text), "Task");
    display.setCursor(0, 56);
    display.print(text);

    display.display();
    delay(200);
}
