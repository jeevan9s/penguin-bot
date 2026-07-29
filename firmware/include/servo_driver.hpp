#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>

#pragma once 

#include <Arduino.h>
#include <ESP32Encoder.h>

class ServoDriver {
public:
    ServoDriver(uint8_t pin);
    void begin(int minAngle = 0, int maxAngle = 180);
    void setAngle(int angle);

private:
    uint8_t _pin;
    Servo _servo;
    int _targetAngle;
    int _minLimit;
    int _maxLimit;
};