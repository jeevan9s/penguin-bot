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
    pinMode(_shutdownPin, OUTPUT);
    off(); 
}

void TOFDriver::on() {
    digitalWrite(_shutdownPin, HIGH);
    delay(20); 
}

void TOFDriver::off() {
    digitalWrite(_shutdownPin, LOW);
    delay(20); 
}

bool TOFDriver::begin(uint8_t _addr) {
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

TOFData TOFDriver::read() {

    if (!_started){
        _sensor.startContinuous(); 
        _started = true;
    }

    TOFData data; 
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