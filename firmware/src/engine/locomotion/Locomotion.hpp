/**
 * @file        locomotion.hpp
 * @brief       Core locomotion engine and controller orchestrator
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "balance_controller.hpp"
#include "velocity_controller.hpp"
#include "motor_driver.hpp"
#include "imu_driver.hpp"
#include "commands.hpp"

// IMU -> balance controller(IMU pitch) -> velocity controller(computed vel) -> motor driver (pwm)

class Locomotion {
    public: 
        

}; 