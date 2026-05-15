#include <LCDMenuLib3.h>

#define _LCDML_DISP_cols 20
#define _LCDML_DISP_rows 4

LCDMenuLib3_menu LCDML_0(255, 0, 0, NULL, NULL);

void lcdml_menu_display();
void lcdml_menu_clear();
void lcdml_menu_control();
void mFunc_information(uint8_t param);
void mFunc_settings(uint8_t param);
void mFunc_screensaver(uint8_t param);

LCDMenuLib3 LCDML(
    LCDML_0,
    _LCDML_DISP_rows,
    _LCDML_DISP_cols,
    lcdml_menu_display,
    lcdml_menu_clear,
    lcdml_menu_control
);

LCDML_add(0, LCDML_0, 1, "Information", mFunc_information);
LCDML_add(1, LCDML_0, 2, "Settings", mFunc_settings);
LCDML_createMenu(1);

void setup()
{
    Serial.begin(115200);
    while(!Serial) {}

    LCDML_setup(1);
    LCDML.SCREEN_enable(mFunc_screensaver, 10000);

    Serial.println(F("LCDMenuLib3 serial helper demo"));
    Serial.print(F("Version: "));
    Serial.println(LCDML.VERSION_get());
    Serial.println(F("Use u/d/e/q in Serial Monitor."));
}

void loop()
{
    LCDML.loop();
}

void lcdml_menu_clear()
{
    Serial.println();
}

void lcdml_menu_display()
{
    if(LCDML.DISP_checkMenuUpdate())
    {
        char content_text[21];
        Serial.println(F("--- menu ---"));

        for(uint8_t n = 0; n < LCDML.MENU_getWindowRows(); n++)
        {
            uint8_t content_id = LCDML.DISP_getMenuContentId(n);

            if(content_id < _LCDML_NO_FUNC)
            {
                LCDML_getContent(content_text, content_id);
                Serial.print(n == LCDML.MENU_getCursorPos() ? F("> ") : F("  "));
                Serial.println(content_text);
            }
        }

        Serial.print(F("Displayed id: "));
        Serial.println(LCDML.MENU_getDisplayedElementID());
    }
}

void lcdml_menu_control()
{
    if(Serial.available() == 0)
    {
        return;
    }

    char c = Serial.read();

    if(c == 'u') LCDML.BT_press(_LCDML_REG_button_up);
    if(c == 'd') LCDML.BT_press(_LCDML_REG_button_down);
    if(c == 'e') LCDML.BT_press(_LCDML_REG_button_enter);
    if(c == 'q') LCDML.BT_press(_LCDML_REG_button_quit);
}

void mFunc_information(uint8_t param)
{
    if(LCDML.FUNC_setup())
    {
        Serial.println(F("Information page"));
        Serial.print(F("Param: "));
        Serial.println(param);
        LCDML.FUNC_setLoopInterval(500);
    }

    if(LCDML.FUNC_loop())
    {
        Serial.print(F("Active id: "));
        Serial.println(LCDML.FUNC_getID());
    }

    if(LCDML.FUNC_close())
    {
        Serial.println(F("Leaving information page"));
    }
}

void mFunc_settings(uint8_t param)
{
    if(LCDML.FUNC_setup())
    {
        Serial.println(F("Settings page"));
        Serial.print(F("Screensaver enabled: "));
        Serial.println(LCDML.SCREEN_isEnabled() ? F("yes") : F("no"));
        Serial.print(F("Screensaver timeout: "));
        Serial.println(LCDML.SCREEN_getTimeout());
        LCDML.FUNC_setLoopInterval(500);
    }

    if(LCDML.FUNC_loop())
    {
        Serial.print(F("Menu has children: "));
        Serial.println(LCDML.MENU_hasChildren() ? F("yes") : F("no"));
    }

    if(LCDML.FUNC_close())
    {
        Serial.println(F("Leaving settings page"));
    }
}

void mFunc_screensaver(uint8_t param)
{
    LCDML_UNUSED(param);

    if(LCDML.FUNC_setup())
    {
        Serial.println(F("Screensaver started. Press q to return."));
        LCDML.FUNC_setLoopInterval(1000);
    }

    if(LCDML.FUNC_loop())
    {
        Serial.println(F("Screensaver tick"));
    }
}
