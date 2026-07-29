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

ServoDriver::ServoDriver(uint8_t pin) : _pin(pin), _targetAngle(90), _minLimit(0), _maxLimit(180) {}

void ServoDriver::begin(int minAngle, int maxAngle) {
    _minLimit = minAngle; 
    _maxLimit = maxAngle; 
    _servo.attach(_pin);
}

void ServoDriver::setAngle(int angle) {
    _targetAngle = constrain(angle, _minLimit, _maxLimit); 
    _servo.write(_targetAngle); 
}

