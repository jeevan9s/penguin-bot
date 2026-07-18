/**
 * @file        batt_data_driver.cpp
 * @brief       Implementation of BATT Data driver for reading voltage from onboard 7.4V LiPo battery
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "batt_data_driver.hpp"

float BattDataDriver::battVoltage()
{
    int raw = analogRead(Pins::MCU::VBATT_SENSE);

    float voltage = (raw / 4095.0) * ESP32_VREF * ((VSENSE_R1 + VSENSE_R2) / VSENSE_R2); // 12-bit (0-4095)
    return voltage;
}

float BattDataDriver::battSOC()
{
    float voltage = battVoltage();

    if (voltage <= V_MIN)
        return 0.0f;
    if (voltage >= V_MAX)
        return 100.0f;

    // linear mapping between 6.4V and 8.4V
    return ((voltage - V_MIN) / (V_MAX - V_MIN)) * 100.0f;
}

// rough 5.0V for now
bool BattDataDriver::isConnected()
{
    return battVoltage() > 5.0f;
}

BattData BattDataDriver::read() {
    BattData _batt; 

    _batt.voltage = battVoltage(); 
    _batt.SOC = battSOC(); 
    _batt.connected = isConnected(); 

    return _batt; 
}