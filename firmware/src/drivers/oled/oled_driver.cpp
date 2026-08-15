/**
 * @file        oled_driver.cpp
 * @brief       OLED face driver
 * @author      Jeevan Sanchez
 * @date        2026-08-08
 *
 * PENGUIN
 */
#include <Arduino.h>
#include "oled_driver.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
static bool oledInitialized = false;

static bool oledBegin() {
  if (oledInitialized) return true;

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failure");
    return false;
  }

  randomSeed(micros());
  oledInitialized = true;
  return true;
}

bool oled() {
  if (!oledBegin()) return false;

  static uint32_t lastMove = 0;
  static int8_t eyeX = 0, eyeY = 0;
  static int8_t targetX = 0, targetY = 0;
  static uint32_t lastBlink = 0;
  static uint32_t nextBlinkAt = 3000;
  static bool blinking = false;
  static uint32_t blinkStart = 0;

  uint32_t now = millis();

  if (now - lastMove > 2000) {
    targetX = random(-6, 7);
    targetY = random(-3, 4);
    lastMove = now;
  }
  if (eyeX < targetX) eyeX++;
  if (eyeX > targetX) eyeX--;
  if (eyeY < targetY) eyeY++;
  if (eyeY > targetY) eyeY--;

  if (!blinking && now - lastBlink > nextBlinkAt) {
    blinking = true;
    blinkStart = now;
  }
  if (blinking && now - blinkStart > 120) {
    blinking = false;
    lastBlink = now;
    nextBlinkAt = 2000 + random(3000);
  }

  display.clearDisplay();
  
  display.drawFastHLine(0, 0, 34, SSD1306_WHITE);
  display.drawFastVLine(34, 0, 10, SSD1306_WHITE);
  display.drawFastHLine(34, 10, 60, SSD1306_WHITE);
  display.drawFastVLine(94, 0, 10, SSD1306_WHITE);
  display.drawFastHLine(94, 0, 34, SSD1306_WHITE);
  display.fillCircle(102, 5, 2, SSD1306_WHITE);

  int16_t eyeW = 20, eyeH = 24;
  int16_t x1 = 38 + eyeX, x2 = 70 + eyeX;
  int16_t y = 22 + eyeY;

  if (blinking) {
    display.fillRoundRect(x1, y + eyeH / 2 - 2, eyeW, 4, 2, SSD1306_WHITE);
    display.fillRoundRect(x2, y + eyeH / 2 - 2, eyeW, 4, 2, SSD1306_WHITE);
  } else {
    display.fillRoundRect(x1, y, eyeW, eyeH, 4, SSD1306_WHITE);
    display.fillRoundRect(x2, y, eyeW, eyeH, 4, SSD1306_WHITE);
  }

  display.fillTriangle(64, 50, 69, 58, 59, 58, SSD1306_WHITE);

  display.display();
  return true;
}

void oledLoadingScreen(uint8_t percent) {
  if (!oledBegin()) return;
  if (percent > 100) percent = 100;

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  int16_t x1, y1;
  uint16_t cw, ch;
  display.getTextBounds("jeevan 2026", 0, 0, &x1, &y1, &cw, &ch);
  display.setCursor(SCREEN_WIDTH - cw - 2, 2);
  display.print("jeevan 2026");

  display.setTextSize(2);
  uint16_t w, h;
  display.getTextBounds("PENGUIN", 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, 24);
  display.print("PENGUIN");

  int16_t barX = 6;
  int16_t barY = 50;
  int16_t barW = SCREEN_WIDTH - (barX * 2);
  int16_t dashW = 6;
  int16_t dashGap = 2;
  int16_t dashCount = barW / (dashW + dashGap);
  int16_t filledDashes = (dashCount * percent) / 100;

  for (int16_t i = 0; i < dashCount; i++) {
    int16_t dx = barX + i * (dashW + dashGap);
    if (i < filledDashes) {
      display.fillRect(dx, barY, dashW, 4, SSD1306_WHITE);
    } else {
      display.drawRect(dx, barY, dashW, 4, SSD1306_WHITE);
    }
  }

  display.display();
}