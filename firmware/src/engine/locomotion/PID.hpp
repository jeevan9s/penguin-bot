/**
 * @file        PID.hpp
 * @brief       Definitions for utility PID class
 * @author      Jeevan Sanchez
 * @date        2026-07-23
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>

class PIDController {
    public:
        PIDController(float kp, float ki, float kd, float outMin, float outMax);

        float update(float target, float measurement, float dt); 
        float update(float target, float measurement, float derivative, float dt); // for balance controller : use gyro pitch rate as derivative term

        void reset(); 
        void setGains(float P, float I, float D); 
    
    private:

        float _kp; 
        float _ki; 
        float _kd; 

        float _outMin; 
        float _outMax; 

        float integral; 
        float prevErr;

        bool ran; 
}; 