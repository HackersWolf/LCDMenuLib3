LCDMenuLib3 recovered manual functions
=====================================

Recovered from:
C:\Users\User\Documents\Arduino\libraries\LCDMenuLib3

Added back:
- src/LCDMenuLib3_DateTime.h
- src/LCDMenuLib3_DateTime.cpp

These expose the LCDML3 namespace helpers:
- LCDML3::Context
- LCDML3::RenderConfig
- LCDML3::handleTime()
- LCDML3::handleDate()
- LCDML3::drawTime()
- LCDML3::drawDate()
- LCDML3::handleAndDrawTime()
- LCDML3::handleAndDrawDate()
- LCDML3::formatHHMM()
- LCDML3::formatDateDDMMYY()
- LCDML3::formatDateDDMMYYYY()
- LCDML3::daysInMonth()
- LCDML3::clampDate()

Dependency:
- Adafruit GFX Library

Quick use:

  #include <LCDMenuLib3.h>
  static LCDML3::Context ctx;

  LCDML3::RenderConfig cfg;
  cfg.x = 0;
  cfg.y = 16;
  cfg.w = 128;
  cfg.h = 8;
  cfg.labelAlign = LCDML3::ALIGN_LEFT;
  cfg.valueAlign = LCDML3::ALIGN_RIGHT;

  LCDML3::handleAndDrawTime(display, ctx, LCDML, line, cfg, "LIGHT ON", hourValue, minuteValue);
  _LCDML_DISP_cursor_char = (char*)LCDML3::cursor(ctx);
