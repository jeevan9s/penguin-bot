/**
 * @file        motor_driver.cpp
 * @brief       Hardware abstraction and motor data collection for DRV8833-controlled N20 MicroGear Motors.
 * @author      Jeevan Sanchez
 * @date        2026-07-17
 *
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "motor_driver.hpp"

MotorDriver::MotorDriver(uint8_t motorIn1, uint8_t motorIn2, uint8_t encP1, uint8_t encP2)
    : _in1(motorIn1), _in2(motorIn2), _encP1(encP1), _encP2(encP2), _encoder(), _lastPosition(0), _lastTime(0), _currentRPM(0.0f) {}

void MotorDriver::begin()
{
    _encoder.attachHalfQuad(_encP1, _encP2);

    _encoder.clearCount();
    _encoder.setCount(0);
    _lastTime = millis();

    ledcAttach(_in1, 20000, 8); 
    ledcAttach(_in2, 20000, 8); 

    stop(); 
}

MotorData MotorDriver::read()
{
    MotorData data;
    long currentPos = _encoder.getCount();
    unsigned long currentTime = millis();

    float dt = (currentTime - _lastTime) / 1000.0;
    if (dt > 0.01)
    { // 10ms window
        long dTicks = currentPos - _lastPosition;
        data.RPM = (dTicks / 360.0) / (dt / 60.0);

        _lastPosition = currentPos;
        _lastTime = currentTime;
        _currentRPM = data.RPM;
    }
    else
    {
        data.RPM = _currentRPM;
    }

    data.position = currentPos;
    data.running = (abs(data.RPM) > 0.1);
    return data;
}

void MotorDriver::setPWM(int pwm)
{
    pwm = constrain(pwm, -255, 255); 

    if (pwm > 0) {
        ledcWrite(_in1, pwm); 
        ledcWrite(_in2, 0); 
    }

    else if (pwm < 0) {
        ledcWrite(_in1, 0); 
        ledcWrite(_in2, abs(pwm)); 
    }
    
    else {
        stop(); 
    }
}

void MotorDriver::stop() 
{
    ledcWrite(_in1, 0); 
    ledcWrite(_in2, 0); 
    _currentRPM = 0.0f; 
}