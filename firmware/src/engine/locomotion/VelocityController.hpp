/**
 * @file        VelocityController.hpp
 * @brief       Class definition for wheel velocity (N20-DRV8833) control with PID
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "PID.hpp"

class VelocityController {
    public:
        VelocityController(float kp, float ki, float kd, float maxPWM); 
        void update(float measuredVelocity, float targetVelocity, float dt); 
        void reset(); 

    private:
        PIDController pid; 

};