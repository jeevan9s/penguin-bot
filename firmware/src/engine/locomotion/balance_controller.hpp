/**
 * @file        balance_controller.hpp
 * @brief       Class definition of IMU-based controller for pitch correction with PID
 * only commands wheel motion, hips only driven by stances
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "PID.hpp"
#include "penguin_data.hpp"

class BalanceController {
    public:
        BalanceController(float kp, float ki, float kd, float maxV); 
        float update(const IMUData &imu, float targetPitch, float dt); 
        void reset(); 

    private:
        PIDController pid; 
};