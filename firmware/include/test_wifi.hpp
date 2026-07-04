/**
 * @file        test_wifi.hpp
 * @brief       Header for WiFi testing. 
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#pragma once

#include <Wifi.h>
#include <Adafruit_MCP23X17.h>
#include "pinouts.hpp"

void test_wifi(const char* ssid, const char* pswd);

