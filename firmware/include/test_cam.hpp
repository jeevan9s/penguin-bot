/**
 * @file        test_cam.hpp
 * @brief       OV2640 camera testing. 
 * @author      Jeevan Sanchez
 * @date        2026-07-01
 *
 * PENGUIN
 */

#pragma once 

#include <Adafruit_MCP23X17.h>
#include "pinouts.hpp"
#include "config.hpp"

void enable_cam();
void setup_cam();
void test_cam();
