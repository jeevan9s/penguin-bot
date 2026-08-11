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
#include <Adafruit_MCP23X17.h>
#include "penguin_data.hpp"

/// @brief hardware driver for the VL530LX time-of-flight (ToF) sensor 
/// used for proximity readings and obstacle detection
/// I2C
class TOFDriver
{
public:

    /// @brief constructor for shutdown pin setup and default state
    /// @param shutdownPin XSHUT pin for on/off toggle
    /// @param addr configurable I2C address of sensor
    /// @param detectionThreshold 
    TOFDriver(uint8_t shutdownPin, uint8_t addr, float detectionThreshold = 100.0);

    /// @brief turns sensor ON, configures parameterized I2C address and adds a 500ms timeout
    /// @return true on successful initialization
    bool begin();

    /// @brief turn the sensor ON via shutdown pin HIGH
    void on();

    /// @brief turn the sensor OFF via shutdown pin LOW
    void off();

    /// @brief confirm I2C connection
    /// @return true on acknowledgement
    bool ping();

    /// @brief gate reads based on sensor presence
    /// @return true if sensor is present
    bool present(); 

    /// @brief populate the TOFData structure with proximity data and detection flag
    /// @return the populated TOFData structure for dashboard visuals and decision-based routines
    TOFData read();
    

private:
    VL53L0X _sensor;
    uint8_t _addr;
    uint8_t _shutdownPin;
    float _detectionThreshold;
    bool _started = false; 
    bool _present = false; 
};

extern Adafruit_MCP23X17 mcp;
