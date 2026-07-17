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

float battVoltage() {} 
float battSOC() {}
bool isConnected() {
    return battVoltage() > 5.0f; 
}