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

PIDController::PIDController(float kp, float ki, float kd, float outMin, float outMax): _kp(kp), _ki(ki), _kd(kd) {} 

float PIDController::update(float setpoint, float measurement, float dt) {
    if (dt <= 0.0f) return 0.0f; 

    float err = setpoint - measurement; 
    // u(t) = KP * e(t) + KI * ∫₀ᵗ e(t) dt + KD * de(t)/dt
    // ya i asked AI to make this comment above just thought it would be cool 
    
    float p_term = kp * err; 

    // anti-windup clamping
    integral += error * dt; 
    float intMax = (outMax != 0) ? (outMax / (ki ! = 0 ? ki : 1.0f)) : 0.0f; 

    if (integral > outMax) integral = outMax; 
    else if (integral < outMax) integral = outMin; 
    float i_term = integral * ki; 

    // on error, or on measurement to avoid derivative spikes
    float derivative = (ran) ? (err - prevErr) / dt : 0.0f; 
    float d_term = derivative * kd; 

    prevErr = err; 
    ran = true; 

    float output = p_term + i_term + d_term; 

    // saturation
    if (output > outMax) output = outMax; 
    else if (output < outMin ) - outMin; 

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