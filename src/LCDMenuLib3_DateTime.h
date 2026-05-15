#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>

// Forward declaration pour casser l'inclusion circulaire
class LCDMenuLib3;

namespace LCDML3 {

enum EditStep : uint8_t {
  EDIT_IDLE = 0,
  EDIT_HOURS,
  EDIT_MINUTES,
  EDIT_DAY,
  EDIT_MONTH,
  EDIT_YEAR
};

enum Align : uint8_t {
  ALIGN_LEFT = 0,
  ALIGN_CENTER,
  ALIGN_RIGHT
};

struct Context {
  EditStep step = EDIT_IDLE;
  const char* cursor = ">";

  bool blinkVisible = true;
  unsigned long blinkMs = 0;
  uint16_t blinkPeriod = 420;

  uint8_t heldMask = 0;
  unsigned long repeatStartMs = 0;
  unsigned long repeatLastMs = 0;
  uint16_t repeatDelayMs = 380;
  uint16_t repeatSlowMs = 170;
  uint16_t repeatFastMs = 55;

  bool wrap = true;
  bool changed = false;

  uint8_t animFrame = 0;
  unsigned long animMs = 0;
  uint16_t animPeriod = 120;
};

struct RenderConfig {
  int16_t x = 0;
  int16_t y = 0;
  int16_t w = 128;
  int16_t h = 8;
  int16_t valuePadding = 2;
  uint8_t charW = 6;
  uint8_t fontH = 8;
  Align labelAlign = ALIGN_LEFT;
  Align valueAlign = ALIGN_RIGHT;
  bool drawLabel = true;
  bool drawAnimation = true;
  bool clearLine = true;
};

void reset(Context& ctx, LCDMenuLib3& lcdml);
void tick(Context& ctx);
const char* cursor(const Context& ctx);

void formatHHMM(char* out, size_t outSize, uint8_t hh, uint8_t mm, bool blinkHours = false, bool blinkMinutes = false);
void formatDateDDMMYY(char* out, size_t outSize, uint8_t dd, uint8_t mm, uint16_t yy,
                      bool blinkDay = false, bool blinkMonth = false, bool blinkYear = false);
void formatDateDDMMYYYY(char* out, size_t outSize, uint8_t dd, uint8_t mm, uint16_t yy,
                        bool blinkDay = false, bool blinkMonth = false, bool blinkYear = false);

uint8_t daysInMonth(uint8_t month, uint16_t year);
void clampDate(uint8_t& dd, uint8_t& mm, uint16_t& yy, uint16_t minYear = 2000, uint16_t maxYear = 2099);

bool handleTime(Context& ctx, LCDMenuLib3& lcdml, uint8_t line, uint8_t& hh, uint8_t& mm);
bool handleDate(Context& ctx, LCDMenuLib3& lcdml, uint8_t line, uint8_t& dd, uint8_t& mm, uint16_t& yy,
                uint16_t minYear = 2000, uint16_t maxYear = 2099);

int16_t alignLeftX(int16_t x);
int16_t alignCenterX(int16_t x, int16_t w, int16_t textW);
int16_t alignRightX(int16_t x, int16_t w, int16_t textW);
int16_t alignedX(Align align, int16_t x, int16_t w, int16_t textW);
int16_t textWidth(const char* txt, uint8_t charW = 6);

void drawAligned(Adafruit_GFX& gfx, const char* txt, int16_t x, int16_t y, int16_t w, Align align, uint8_t charW = 6);
void drawTime(Adafruit_GFX& gfx, Context& ctx, const RenderConfig& cfg, const char* label, uint8_t hh, uint8_t mm);
void drawDate(Adafruit_GFX& gfx, Context& ctx, const RenderConfig& cfg, const char* label, uint8_t dd, uint8_t mm, uint16_t yy, bool useShortYear = true);

void handleAndDrawTime(Adafruit_GFX& gfx, Context& ctx, LCDMenuLib3& lcdml, uint8_t line,
                       const RenderConfig& cfg, const char* label, uint8_t& hh, uint8_t& mm);
void handleAndDrawDate(Adafruit_GFX& gfx, Context& ctx, LCDMenuLib3& lcdml, uint8_t line,
                       const RenderConfig& cfg, const char* label, uint8_t& dd, uint8_t& mm, uint16_t& yy,
                       uint16_t minYear = 2000, uint16_t maxYear = 2099, bool useShortYear = true);

} // namespace LCDML3