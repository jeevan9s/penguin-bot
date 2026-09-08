/**
 * @file        servor_driver.cpp
 * @brief       Hardware abstraction for Servo motors.
 * @author      Jeevan Sanchez
 * @date        2026-07-21
 *
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "servo_driver.hpp"

ServoDriver::ServoDriver(uint8_t pin) : _pin(pin), _targetMicroseconds(1500), _minLimit(500), _maxLimit(2500) {}

void ServoDriver::begin(int minMicroseconds, int maxMicroseconds) {
    _minLimit = min(minMicroseconds, maxMicroseconds);
    _maxLimit = max(minMicroseconds, maxMicroseconds);
    _servo.attach(_pin, _minLimit, _maxLimit);
}

void ServoDriver::write(int microseconds) {
    _targetMicroseconds = constrain(microseconds, _minLimit, _maxLimit);
    _servo.writeMicroseconds(_targetMicroseconds);
}

