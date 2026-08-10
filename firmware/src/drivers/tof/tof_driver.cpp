/**
 * @file        tof_driver.cpp
 * @brief       Implementation of ToF Sensor driver for reading proximity and obstacle detection. 
 * @author      Jeevan Sanchez
 * @date        2026-07-17
 * 
 * Uses the Adafruit VL530LX Library
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "tof_driver.hpp"

TOFDriver::TOFDriver(uint8_t shutdownPin, uint8_t addr, float detectionThreshold) : _shutdownPin(shutdownPin), _addr(addr), _detectionThreshold(detectionThreshold) {
    mcp.pinMode(_shutdownPin, OUTPUT);
    off(); 
}

void TOFDriver::on() {
    mcp.digitalWrite(_shutdownPin, HIGH);
    delay(20); 
}

void TOFDriver::off() {
    mcp.digitalWrite(_shutdownPin, LOW);
    delay(20); 
}

bool TOFDriver::begin() {
    on(); 

    if (!_sensor.init()) return false; 

    _sensor.setAddress(_addr); 
    _sensor.setTimeout(500); 
    return true;
}

bool TOFDriver::ping() {
    Wire.beginTransmission(_addr);
    return (Wire.endTransmission() == 0); // true on ACK
}

bool TOFDriver::present() {
    return _present; 
}

TOFData TOFDriver::read() {

    TOFData data;

    if (!_present) {
        data.proximity = -1.0;
        data.obstacleDetected = false;
        return data;
    }

    if (!_started){
        _sensor.startContinuous(); 
        _started = true;
    }

    uint16_t dist = _sensor.readRangeContinuousMillimeters(); 

    if (_sensor.timeoutOccurred() || dist >= 65535) {
        data.proximity = -1.0; 
        data.obstacleDetected = false; 
    } else {
        data.proximity = (float)dist; 
        data.obstacleDetected = (data.proximity < _detectionThreshold && data.proximity > 0);
    }
    return data;
}