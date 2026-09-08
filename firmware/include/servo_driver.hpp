/**
 * @file        servo_driver.hpp
 * @brief       ESP32Servo wrapper for Servo motor (hips) control
 * @author      Jeevan Sanchez
 * @date        2026-07-17
 *
 *
 * PENGUIN
 */

#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>

/// @brief lightweight ESP32Servo wrapper for hip-control
class ServoDriver {
public:
    /// @brief construct with the Servo input
    /// @param pin Servo motor input pin
    ServoDriver(uint8_t pin);

    /// @brief configure servo pulse bounds and attach pin
    void begin(int minMicroseconds = 500, int maxMicroseconds = 2500);

    /// @brief constrain pulse width to bounds and write to Servo
    void write(int microseconds);

private:
    uint8_t _pin;
    Servo _servo;
    int _targetMicroseconds;
    int _minLimit;
    int _maxLimit;
};