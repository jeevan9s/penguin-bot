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

void oled() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); 
  }
  
  display.clearDisplay();
  
  display.drawRect(36, 4, 56, 56, SSD1306_WHITE);
  
  display.fillRect(51, 21, 6, 6, SSD1306_WHITE);
  display.fillRect(71, 21, 6, 6, SSD1306_WHITE);
  
  display.drawFastHLine(57, 45, 14, SSD1306_WHITE);
  display.drawPixel(56, 44, SSD1306_WHITE);
  display.drawPixel(71, 44, SSD1306_WHITE);
  
  display.display();
}
