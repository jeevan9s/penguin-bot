/**
 * @file        balance_controller.hpp
 * @brief       Class definition of IMU-based controller for pitch correction with PID
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "PID.hpp"
#include "penguin_data.hpp"

/// @brief PID controller wrapper for IMU-driven balance control
// produces a target RPM for wheel-motors based on the current pitchRate and a target pitch
// uses the IMU pitch rate as the derivative term for PID control
class BalanceController {
    public:
        BalanceController(float kp, float ki, float kd, float maxV); 
        float update(const IMUData &imu, float targetPitch, float dt); 
        void reset(); 

    private:
        PIDController pid; 
};