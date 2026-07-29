/**
 * @file        tof_driver.hpp
 * @brief       Class definition of ToF Sensor driver for reading proximity and obstacle detection.
 * @author      Jeevan Sanchez
 * @date        2026-07-17
 *
 * Uses the Pololu VL530LX Library
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include <VL53L0X.h>
#include "state/penguin_data.hpp"

class TOFDriver
{
public:
    TOFDriver(uint8_t shutdownPin, uint8_t addr, float detectionThreshold = 100.0);

    bool begin(uint8_t addr);
    void on();
    void off();
    bool ping();
    TOFData read();

private:
    VL53L0X _sensor;
    uint8_t _addr;
    uint8_t _shutdownPin;
    float _detectionThreshold;
    bool _started = false; 
};