/**
 * @file        BalanceController.hpp
 * @brief       Implementation of IMU-based controller for pitch correction with PID
 * @author      Jeevan Sanchez
 * @date        2026-07-29
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "BalanceController.hpp"

PIDController pid()

BalanceController::BalanceController(float kp, float ki, float kd, float maxV) : pid(kp, ki, kd, maxV) {} 

float BalanceController::update(const IMUData &imu, float targetPitch, float dt) {
    return pid.update(targetPitch, imu.angles.pitch, imu.gyY, dt); 
}

void BalanceController::reset() {
    pid.reset(); 
}

