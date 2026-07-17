/**
 * @file        batt_data_driver.hpp
 * @brief       Class definition of BATT Data driver for reading voltage from onboard 7.4V LiPo battery
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "PenguinData.hpp"
#include "config.hpp"

extern Adafruit_MCP23X17 mcp;

class BattDataDriver {
    public:
        float battVoltage(); 
        float battSOC(); 
        bool isConnected(); 
};
