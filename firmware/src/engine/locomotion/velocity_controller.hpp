/**
 * @file        velocity_controller.hpp
 * @brief       Class definition for wheel velocity (N20-DRV8833) control with PID
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "PID.hpp"
#include "penguin_data.hpp"

/// @brief PID controller wrapper for speed control 
// controller produces an optimal PWM for motor driver given the RPM from the globally-tracked motor data struct
class VelocityController {
    public:
        VelocityController(float kp, float ki, float kd, float maxPWM); 
        float update(const MotorData &motor, float targetPWM, float dt); 
        void reset(); 

    private:
        PIDController pid; 

};