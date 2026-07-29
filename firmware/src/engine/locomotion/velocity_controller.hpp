/**
 * @file        velocity_controller.hpp
 * @brief       Class definition for wheel velocity (N20-DRV8833) control with PID
 * outputs a float motor effort (PWM)
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "PID.hpp"
#include "penguin_data.hpp"

class VelocityController {
    public:
        VelocityController(float kp, float ki, float kd, float maxPWM); 
        float update(const MotorData &motor, float targetPWM, float dt); 
        void reset(); 

    private:
        PIDController pid; 

};