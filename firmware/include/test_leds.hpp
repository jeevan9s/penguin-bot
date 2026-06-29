/**
 * @file        test_leds.hpp
 * @brief       Header for LED testing. 
 * @author      Jeevan Sanchez
 * @date        2026-06-29
 *
 * PENGUIN
 */

#pragma once

#include <Adafruit_MCP23X17.h>
#include "pinouts.hpp"

const int8_t ledPins[3] = {Pins::MCP::DBG_LED, Pins::MCP::WIFI_LED, Pins::MCP::CAM_LED};

void test_leds(void);


