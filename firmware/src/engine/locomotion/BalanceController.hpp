/**
 * @file        BalanceController.hpp
 * @brief       Class definition of IMU-based controller for pitch correction with PID
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "PID.hpp"

class BalanceController {
    public:
        BalanceController(float kp, float ki, float kd, float maxPWM); 
        void update(float measuredPitch, float targetPitch, float dt); 
        void reset(); 

    private:
        PIDController pid; 

};