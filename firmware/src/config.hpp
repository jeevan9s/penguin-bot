/**
 * @file        config.hpp
 * @brief       System configuration.
 * @author      Jeevan Sanchez
 * @date        2026-06-28
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#include "pinouts.hpp"

extern Adafruit_MCP23X17 mcp;

bool init_mcp(void);
void led_startup(void);

// WIFI creds
extern const char* ssid;
extern const char* pswd;
