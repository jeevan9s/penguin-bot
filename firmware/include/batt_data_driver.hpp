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
 #include "state/PenguinData.hpp"
#include "config.hpp"

class BattDataDriver
{
public:
    BattData read(); 

private:
    float battVoltage();
    float battSOC();
    bool isConnected();

    const float ESP32_VREF = 3.3;
    const float VSENSE_R1 = 100.0;
    const float VSENSE_R2 = 47.0;
    const float BATT_CAPACITY = 100.0;

    const float V_MIN = 6.4f;
    const float V_MAX = 8.4f;
};
