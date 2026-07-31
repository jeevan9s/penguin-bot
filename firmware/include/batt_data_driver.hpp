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
#include "penguin_data.hpp"
#include "config.hpp"

/// @brief hardware driver class for reading voltage, capacity data from a 7.4V LiPo battery
class BattDataDriver
{
public:
    /// @brief populate the BattData structure (voltage, SOC, connected bool)
    /// @return the populated BattData object
    BattData read(); 

private:
    /// @brief read from voltage sensing circuit 
    /// @return the converted (from analog) battery voltage as a float
    float battVoltage();

    /// @brief calculate a state of charge based on the voltage-sense reading
    /// @return the state of charge as a float (50%, 75%, 100%) etc. 
    float battSOC();

    /// @brief check if the battery is plugged in based off  comparing the voltage-sense reading with a rough threshold (5.0V)
    /// @return true if the battery is connected
    bool isConnected();

    /// constants for calculations
    const float ESP32_VREF = 3.3;
    const float VSENSE_R1 = 100.0;
    const float VSENSE_R2 = 47.0;
    const float BATT_CAPACITY = 100.0;

    const float V_MIN = 6.4f;
    const float V_MAX = 7.4f;
};
