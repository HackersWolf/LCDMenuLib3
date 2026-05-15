#include "LCDMenuLib3.h"
#include "LCDMenuLib3_DateTime.h"
#include <string.h>

namespace LCDML3 {

static inline void beginEdit(Context& ctx, LCDMenuLib3& lcdml, EditStep step, const char* cursorHint) {
  lcdml.MENU_disScroll();
  ctx.step = step;
  ctx.cursor = cursorHint;
  ctx.changed = true;
}

void reset(Context& ctx, LCDMenuLib3& lcdml) {
  ctx.step = EDIT_IDLE;
  ctx.cursor = ">";
  ctx.heldMask = 0;
  ctx.changed = true;
  lcdml.MENU_enScroll();
}

const char* cursor(const Context& ctx) {
  return ctx.cursor;
}

void tick(Context& ctx) {
  const unsigned long now = millis();
  if (now - ctx.blinkMs >= ctx.blinkPeriod) {
    ctx.blinkMs = now;
    ctx.blinkVisible = !ctx.blinkVisible;
    ctx.changed = true;
  }
  if (now - ctx.animMs >= ctx.animPeriod) {
    ctx.animMs = now;
    ctx.animFrame = (ctx.animFrame + 1) & 0x03;
    ctx.changed = true;
  }
}

void formatHHMM(char* out, size_t outSize, uint8_t hh, uint8_t mm, bool blinkHours, bool blinkMinutes) {
  char hhBuf[3];
  char mmBuf[3];
  if (blinkHours) strcpy(hhBuf, "  "); else snprintf(hhBuf, sizeof(hhBuf), "%02u", hh);
  if (blinkMinutes) strcpy(mmBuf, "  "); else snprintf(mmBuf, sizeof(mmBuf), "%02u", mm);
  snprintf(out, outSize, "%s:%s", hhBuf, mmBuf);
}

void formatDateDDMMYY(char* out, size_t outSize, uint8_t dd, uint8_t mm, uint16_t yy,
                      bool blinkDay, bool blinkMonth, bool blinkYear) {
  char ddBuf[3], mmBuf[3], yyBuf[3];
  if (blinkDay) strcpy(ddBuf, "  "); else snprintf(ddBuf, sizeof(ddBuf), "%02u", dd);
  if (blinkMonth) strcpy(mmBuf, "  "); else snprintf(mmBuf, sizeof(mmBuf), "%02u", mm);
  if (blinkYear) strcpy(yyBuf, "  "); else snprintf(yyBuf, sizeof(yyBuf), "%02u", yy % 100);
  snprintf(out, outSize, "%s/%s/%s", ddBuf, mmBuf, yyBuf);
}

void formatDateDDMMYYYY(char* out, size_t outSize, uint8_t dd, uint8_t mm, uint16_t yy,
                        bool blinkDay, bool blinkMonth, bool blinkYear) {
  char ddBuf[3], mmBuf[3], yyBuf[5];
  if (blinkDay) strcpy(ddBuf, "  "); else snprintf(ddBuf, sizeof(ddBuf), "%02u", dd);
  if (blinkMonth) strcpy(mmBuf, "  "); else snprintf(mmBuf, sizeof(mmBuf), "%02u", mm);
  if (blinkYear) strcpy(yyBuf, "    "); else snprintf(yyBuf, sizeof(yyBuf), "%04u", yy);
  snprintf(out, outSize, "%s/%s/%s", ddBuf, mmBuf, yyBuf);
}

uint8_t daysInMonth(uint8_t month, uint16_t year) {
  switch (month) {
    case 1: return 31; case 2: return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
    case 3: return 31; case 4: return 30; case 5: return 31; case 6: return 30;
    case 7: return 31; case 8: return 31; case 9: return 30; case 10: return 31;
    case 11: return 30; case 12: return 31; default: return 31;
  }
}

void clampDate(uint8_t& dd, uint8_t& mm, uint16_t& yy, uint16_t minYear, uint16_t maxYear) {
  if (mm < 1) mm = 1;
  if (mm > 12) mm = 12;
  if (yy < minYear) yy = minYear;
  if (yy > maxYear) yy = maxYear;
  uint8_t maxD = daysInMonth(mm, yy);
  if (dd < 1) dd = 1;
  if (dd > maxD) dd = maxD;
}

static inline void updateRepeatState(Context& ctx, uint8_t mask, bool active) {
  const unsigned long now = millis();
  if (active) {
    if (ctx.heldMask != mask) {
      ctx.heldMask = mask;
      ctx.repeatStartMs = now;
      ctx.repeatLastMs = 0;
    }
  } else if (ctx.heldMask == mask) {
    ctx.heldMask = 0;
    ctx.repeatStartMs = 0;
    ctx.repeatLastMs = 0;
  }
}

static inline bool repeatReady(Context& ctx, uint8_t mask) {
  const unsigned long now = millis();
  if (ctx.heldMask != mask) return false;
  if (now - ctx.repeatStartMs < ctx.repeatDelayMs) return false;
  uint16_t interval = (now - ctx.repeatStartMs > 1500UL) ? ctx.repeatFastMs : ctx.repeatSlowMs;
  if (ctx.repeatLastMs == 0 || now - ctx.repeatLastMs >= interval) {
    ctx.repeatLastMs = now;
    return true;
  }
  return false;
}

static inline void adjust8(Context& ctx, LCDMenuLib3& lcdml, uint8_t& value, uint8_t minVal, uint8_t maxVal) {
  bool decNow = lcdml.BT_checkUp() || lcdml.BT_checkRight();
  bool incNow = lcdml.BT_checkDown() || lcdml.BT_checkLeft();

  if (decNow && incNow) return;

  updateRepeatState(ctx, 1, decNow);
  updateRepeatState(ctx, 2, incNow);

  if (decNow && (ctx.heldMask == 1 ? repeatReady(ctx, 1) : true)) {
    if (value > minVal) value--; else if (ctx.wrap) value = maxVal;
    lcdml.BT_resetUp(); lcdml.BT_resetRight();
    ctx.changed = true;
  }
  if (incNow && (ctx.heldMask == 2 ? repeatReady(ctx, 2) : true)) {
    if (value < maxVal) value++; else if (ctx.wrap) value = minVal;
    lcdml.BT_resetDown(); lcdml.BT_resetLeft();
    ctx.changed = true;
  }
}

static inline void adjust16(Context& ctx, LCDMenuLib3& lcdml, uint16_t& value, uint16_t minVal, uint16_t maxVal) {
  bool decNow = lcdml.BT_checkUp() || lcdml.BT_checkRight();
  bool incNow = lcdml.BT_checkDown() || lcdml.BT_checkLeft();

  if (decNow && incNow) return;

  updateRepeatState(ctx, 1, decNow);
  updateRepeatState(ctx, 2, incNow);

  if (decNow && (ctx.heldMask == 1 ? repeatReady(ctx, 1) : true)) {
    if (value > minVal) value--; else if (ctx.wrap) value = maxVal;
    lcdml.BT_resetUp(); lcdml.BT_resetRight();
    ctx.changed = true;
  }
  if (incNow && (ctx.heldMask == 2 ? repeatReady(ctx, 2) : true)) {
    if (value < maxVal) value++; else if (ctx.wrap) value = minVal;
    lcdml.BT_resetDown(); lcdml.BT_resetLeft();
    ctx.changed = true;
  }
}

bool handleTime(Context& ctx, LCDMenuLib3& lcdml, uint8_t line, uint8_t& hh, uint8_t& mm) {
  tick(ctx);
  bool wasChanged = ctx.changed;
  ctx.changed = false;

  if (line == lcdml.MENU_getCursorPos() && lcdml.BT_checkAny()) {
    if (ctx.step == EDIT_IDLE && lcdml.BT_checkEnter()) {
      beginEdit(ctx, lcdml, EDIT_HOURS, "#          [HH]");
      lcdml.BT_resetEnter();
    } else if (ctx.step == EDIT_HOURS) {
      adjust8(ctx, lcdml, hh, 0, 23);
      if (lcdml.BT_checkEnter()) {
        beginEdit(ctx, lcdml, EDIT_MINUTES, "#          [MM]");
        lcdml.BT_resetEnter();
      }
      if (lcdml.BT_checkQuit()) {
        reset(ctx, lcdml);
        lcdml.BT_resetQuit();
      }
    } else if (ctx.step == EDIT_MINUTES) {
      adjust8(ctx, lcdml, mm, 0, 59);
      if (lcdml.BT_checkEnter() || lcdml.BT_checkQuit()) {
        reset(ctx, lcdml);
        lcdml.BT_resetEnter();
        lcdml.BT_resetQuit();
      }
    }
  } else {
    updateRepeatState(ctx, 1, false);
    updateRepeatState(ctx, 2, false);
  }

  return wasChanged || ctx.changed;
}

bool handleDate(Context& ctx, LCDMenuLib3& lcdml, uint8_t line, uint8_t& dd, uint8_t& mm, uint16_t& yy,
                uint16_t minYear, uint16_t maxYear) {
  tick(ctx);
  bool wasChanged = ctx.changed;
  ctx.changed = false;

  if (line == lcdml.MENU_getCursorPos() && lcdml.BT_checkAny()) {
    if (ctx.step == EDIT_IDLE && lcdml.BT_checkEnter()) {
      beginEdit(ctx, lcdml, EDIT_DAY, "#          [DD]");
      lcdml.BT_resetEnter();
    } else if (ctx.step == EDIT_DAY) {
      clampDate(dd, mm, yy, minYear, maxYear);
      adjust8(ctx, lcdml, dd, 1, daysInMonth(mm, yy));
      if (lcdml.BT_checkEnter()) {
        beginEdit(ctx, lcdml, EDIT_MONTH, "#          [MM]");
        lcdml.BT_resetEnter();
      }
      if (lcdml.BT_checkQuit()) {
        reset(ctx, lcdml);
        lcdml.BT_resetQuit();
      }
    } else if (ctx.step == EDIT_MONTH) {
      adjust8(ctx, lcdml, mm, 1, 12);
      clampDate(dd, mm, yy, minYear, maxYear);
      if (lcdml.BT_checkEnter()) {
        beginEdit(ctx, lcdml, EDIT_YEAR, "#          [YY]");
        lcdml.BT_resetEnter();
      }
      if (lcdml.BT_checkQuit()) {
        reset(ctx, lcdml);
        lcdml.BT_resetQuit();
      }
    } else if (ctx.step == EDIT_YEAR) {
      adjust16(ctx, lcdml, yy, minYear, maxYear);
      clampDate(dd, mm, yy, minYear, maxYear);
      if (lcdml.BT_checkEnter() || lcdml.BT_checkQuit()) {
        reset(ctx, lcdml);
        lcdml.BT_resetEnter();
        lcdml.BT_resetQuit();
      }
    }
  } else {
    updateRepeatState(ctx, 1, false);
    updateRepeatState(ctx, 2, false);
  }

  return wasChanged || ctx.changed;
}

int16_t alignLeftX(int16_t x) { return x; }
int16_t alignCenterX(int16_t x, int16_t w, int16_t textW) { return x + ((w - textW) / 2); }
int16_t alignRightX(int16_t x, int16_t w, int16_t textW) { return x + w - textW; }
int16_t textWidth(const char* txt, uint8_t charW) { return (int16_t)strlen(txt) * charW; }

int16_t alignedX(Align align, int16_t x, int16_t w, int16_t textW) {
  switch (align) {
    case ALIGN_CENTER: return alignCenterX(x, w, textW);
    case ALIGN_RIGHT:  return alignRightX(x, w, textW);
    case ALIGN_LEFT:
    default:           return alignLeftX(x);
  }
}

void drawAligned(Adafruit_GFX& gfx, const char* txt, int16_t x, int16_t y, int16_t w, Align align, uint8_t charW) {
  gfx.setCursor(alignedX(align, x, w, textWidth(txt, charW)), y);
  gfx.print(txt);
}

static void drawAnim(Adafruit_GFX& gfx, Context& ctx, int16_t x, int16_t y, bool leftSide) {
  static const char* leftFrames[4]  = {">", ">", "]", ">"};
  static const char* rightFrames[4] = {"<", "<", "[", "<"};
  gfx.setCursor(x, y);
  gfx.print(leftSide ? leftFrames[ctx.animFrame] : rightFrames[ctx.animFrame]);
}

void drawTime(Adafruit_GFX& gfx, Context& ctx, const RenderConfig& cfg, const char* label, uint8_t hh, uint8_t mm) {
  tick(ctx);
  if (cfg.clearLine) gfx.fillRect(cfg.x, cfg.y - cfg.fontH + 1, cfg.w, cfg.h, 0);

  const bool blinkHours = (ctx.step == EDIT_HOURS && !ctx.blinkVisible);
  const bool blinkMinutes = (ctx.step == EDIT_MINUTES && !ctx.blinkVisible);

  char value[6];
  formatHHMM(value, sizeof(value), hh, mm, blinkHours, blinkMinutes);

  int16_t labelAreaW = cfg.drawLabel ? (cfg.w / 2) : 0;
  int16_t valueAreaX = cfg.drawLabel ? (cfg.x + labelAreaW + cfg.valuePadding) : cfg.x;
  int16_t valueAreaW = cfg.drawLabel ? (cfg.w - labelAreaW - cfg.valuePadding) : cfg.w;

  if (cfg.drawLabel) drawAligned(gfx, label, cfg.x, cfg.y, labelAreaW, cfg.labelAlign, cfg.charW);
  drawAligned(gfx, value, valueAreaX, cfg.y, valueAreaW, cfg.valueAlign, cfg.charW);

  if (cfg.drawAnimation && ctx.step != EDIT_IDLE) {
    int16_t valW = textWidth(value, cfg.charW);
    int16_t vx = alignedX(cfg.valueAlign, valueAreaX, valueAreaW, valW);
    drawAnim(gfx, ctx, vx - cfg.charW, cfg.y, true);
    drawAnim(gfx, ctx, vx + valW, cfg.y, false);
  }
}

void drawDate(Adafruit_GFX& gfx, Context& ctx, const RenderConfig& cfg, const char* label, uint8_t dd, uint8_t mm, uint16_t yy, bool useShortYear) {
  tick(ctx);
  if (cfg.clearLine) gfx.fillRect(cfg.x, cfg.y - cfg.fontH + 1, cfg.w, cfg.h, 0);

  const bool blinkDay = (ctx.step == EDIT_DAY && !ctx.blinkVisible);
  const bool blinkMonth = (ctx.step == EDIT_MONTH && !ctx.blinkVisible);
  const bool blinkYear = (ctx.step == EDIT_YEAR && !ctx.blinkVisible);

  char value[12];
  if (useShortYear) formatDateDDMMYY(value, sizeof(value), dd, mm, yy, blinkDay, blinkMonth, blinkYear);
  else formatDateDDMMYYYY(value, sizeof(value), dd, mm, yy, blinkDay, blinkMonth, blinkYear);

  int16_t labelAreaW = cfg.drawLabel ? (cfg.w / 2) : 0;
  int16_t valueAreaX = cfg.drawLabel ? (cfg.x + labelAreaW + cfg.valuePadding) : cfg.x;
  int16_t valueAreaW = cfg.drawLabel ? (cfg.w - labelAreaW - cfg.valuePadding) : cfg.w;

  if (cfg.drawLabel) drawAligned(gfx, label, cfg.x, cfg.y, labelAreaW, cfg.labelAlign, cfg.charW);
  drawAligned(gfx, value, valueAreaX, cfg.y, valueAreaW, cfg.valueAlign, cfg.charW);

  if (cfg.drawAnimation && ctx.step != EDIT_IDLE) {
    int16_t valW = textWidth(value, cfg.charW);
    int16_t vx = alignedX(cfg.valueAlign, valueAreaX, valueAreaW, valW);
    drawAnim(gfx, ctx, vx - cfg.charW, cfg.y, true);
    drawAnim(gfx, ctx, vx + valW, cfg.y, false);
  }
}

void handleAndDrawTime(Adafruit_GFX& gfx, Context& ctx, LCDMenuLib3& lcdml, uint8_t line,
                       const RenderConfig& cfg, const char* label, uint8_t& hh, uint8_t& mm) {
  handleTime(ctx, lcdml, line, hh, mm);
  drawTime(gfx, ctx, cfg, label, hh, mm);
}

void handleAndDrawDate(Adafruit_GFX& gfx, Context& ctx, LCDMenuLib3& lcdml, uint8_t line,
                       const RenderConfig& cfg, const char* label, uint8_t& dd, uint8_t& mm, uint16_t& yy,
                       uint16_t minYear, uint16_t maxYear, bool useShortYear) {
  handleDate(ctx, lcdml, line, dd, mm, yy, minYear, maxYear);
  drawDate(gfx, ctx, cfg, label, dd, mm, yy, useShortYear);
}

} // namespace LCDML3
