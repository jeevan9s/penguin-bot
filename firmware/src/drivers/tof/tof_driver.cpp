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

namespace
{
constexpr uint16_t kMaxSingleStepMm = 300;
constexpr uint8_t kOutlierConfirmCount = 2;
constexpr uint16_t kMinReliableRangeMm = 30;
}

TOFDriver::TOFDriver(uint8_t shutdownPin, uint8_t addr, float detectionThreshold, uint16_t distanceCorrectionMm)
    : _shutdownPin(shutdownPin), _addr(addr), _detectionThreshold(detectionThreshold), _distanceCorrectionMm(distanceCorrectionMm) {}

void TOFDriver::on() {
    mcp.pinMode(_shutdownPin, OUTPUT);
    mcp.digitalWrite(_shutdownPin, HIGH);
    delay(20); 
}

void TOFDriver::off() {
    mcp.pinMode(_shutdownPin, OUTPUT);
    mcp.digitalWrite(_shutdownPin, LOW);
    delay(20); 
}

bool TOFDriver::begin() {
    _started = false;
    _present = false;
    _hasLastValidProximity = false;
    _lastValidProximity = 0.0f;
    _outlierCount = 0;

    mcp.pinMode(_shutdownPin, OUTPUT);
    off();
    delay(20);
    on(); 

    if (!_sensor.init()) {
        return false;
    }

    _sensor.setAddress(_addr); 
    _sensor.setTimeout(500); 
    delay(10);

    _present = ping();
    if (!_present) {
        return false;
    }

    // Serial.printf("[TOF 0x%02X] online\n", _addr);
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
        uint16_t correctedDist = (dist > _distanceCorrectionMm) ? (dist - _distanceCorrectionMm) : 0;

        if (correctedDist < kMinReliableRangeMm)
        {
            data.proximity = -1.0;
            data.obstacleDetected = false;
            return data;
        }

        float candidateProximity = (float)correctedDist;

        if (_hasLastValidProximity)
        {
            float delta = fabsf(candidateProximity - _lastValidProximity);
            if (delta > kMaxSingleStepMm)
            {
                if (_outlierCount < 255)
                {
                    _outlierCount++;
                }

                if (_outlierCount < kOutlierConfirmCount)
                {
                    // Drop one-off spikes but accept a sustained new level.
                    candidateProximity = _lastValidProximity;
                }
                else
                {
                    _outlierCount = 0;
                }
            }
            else
            {
                _outlierCount = 0;
            }
        }

        data.proximity = candidateProximity;
        _lastValidProximity = data.proximity;
        _hasLastValidProximity = true;
        data.obstacleDetected = (data.proximity >= 0 && data.proximity < _detectionThreshold);
    }
    return data;
}