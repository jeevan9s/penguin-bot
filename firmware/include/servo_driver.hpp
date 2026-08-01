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

    /// @brief configure servo angle bounds and attach pin
    void begin(int minAngle = 0, int maxAngle = 180);

    /// @brief constrain angle to bounds and write to Servo
    void write(int angle);

private:
    uint8_t _pin;
    Servo _servo;
    int _targetAngle;
    int _minLimit;
    int _maxLimit;
};