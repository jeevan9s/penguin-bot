/**
 * @file        VelocityController.hpp
 * @brief       Implementation for wheel velocity (N20-DRV8833) control with PID
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "VelocityController.hpp"

VelocityController::VelocityController(float kp, float ki, float kd, float maxPWM) : pid(kp, ki, kd, maxPWM) {}

VelocityController::update(const MotorData &motor, float targetPWM, float dt) {
    return pid.update(targetRPM, motor.RPM, dt); 
}

VelocityController::reset() {
    pid.reset(); 
}
