#include <LCDMenuLib3.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LCDML3_MenuHeader header;
LCDML3_NumericEditor pwm;
LCDML3_StatusBar status;
LCDML3_ConfirmDialog confirm;

void setup()
{
    lcd.begin(20, 4);
    header.begin("LCDMenuLib3", "20x4 LCD", 1);
    pwm.begin(128, 0, 255, 5);
    status.setIcon(LCDML3_ICON_WIFI, true);
    status.setIcon(LCDML3_ICON_WARN, true);
    confirm.begin(false);
}

void loop()
{
    char line[21];
    lcd.clear();

    header.format(line, sizeof(line));
    lcd.setCursor(0, 0);
    lcd.print(line);

    pwm.increment();
    pwm.format(line, sizeof(line), " pwm");
    lcd.setCursor(0, 1);
    lcd.print(line);

    status.format(line, sizeof(line));
    lcd.setCursor(0, 2);
    lcd.print(line);

    confirm.toggle();
    confirm.format(line, sizeof(line), "Save?");
    lcd.setCursor(0, 3);
    lcd.print(line);

    delay(1000);
}
