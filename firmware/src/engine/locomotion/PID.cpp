/**
 * @file        PID.cpp
 * @brief       Implementation for utility PID class
 * @author      Jeevan Sanchez
 * @date        2026-07-23
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "PID.hpp"

PIDController::PIDController(float kp, float ki, float kd, float outMin, float outMax)
    : _kp(kp), _ki(ki), _kd(kd), _outMin(outMin), _outMax(outMax), integral(0.0f), prevErr(0.0f) {}

float PIDController::update(float setpoint, float measurement, float dt) {
    if (dt <= 0.0f) return 0.0f; 

    float err = setpoint - measurement; 
    // u(t) = KP * e(t) + KI * ∫₀ᵗ e(t) dt + KD * de(t)/dt
    
    float p_term = _kp * err; 

    // anti-windup clamping
    integral += err * dt; 
    float intMax = (_outMax != 0) ? (_outMax / (_ki != 0 ? _ki : 1.0f)) : 0.0f; 

    if (integral > _outMax) integral = _outMax; 
    else if (integral < _outMax) integral = _outMin; 
    float i_term = integral * _ki; 

    // on error, or on measurement to avoid derivative spikes
    float derivative = (ran) ? (err - prevErr) / dt : 0.0f; 
    float d_term = derivative * _kd; 

    prevErr = err; 
    ran = true; 

    float output = p_term + i_term + d_term; 

    // saturation
    if (output > _outMax) output = _outMax; 
    else if (output < _outMin ) - _outMin; 

    return output; 
}

float PIDController::update(float setpoint, float measurement, float derivative, float dt) {
    if (dt <= 0.0f) return 0.0f; 

    float err = setpoint - measurement; 
    // u(t) = KP * e(t) + KI * ∫₀ᵗ e(t) dt + KD * de(t)/dt
    
    float p_term = _kp * err; 

    // anti-windup clamping
    integral += err * dt; 
    float intMax = (_outMax != 0) ? (_outMax / (_ki != 0 ? _ki : 1.0f)) : 0.0f; 

    if (integral > _outMax) integral = _outMax; 
    else if (integral < _outMax) integral = _outMin; 
    float i_term = integral * _ki; 

    // on error, or on measurement to avoid derivative spikes
    float d_term = derivative * _kd; 

    prevErr = err; 
    ran = true; 

    float output = p_term + i_term + d_term; 

    // saturation
    if (output > _outMax) output = _outMax; 
    else if (output < _outMin ) - _outMin; 

    return output; 
}

void PIDController::reset() {
    integral = 0.0f; 
    prevErr = 0.0f; 
}

void PIDController::setGains(float P, float I, float D) {
    _kp = P; 
    _ki = I; 
    _kd = D; 
}