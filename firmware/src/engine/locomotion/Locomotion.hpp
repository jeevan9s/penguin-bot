/**
 * @file        locomotion.hpp
 * @brief       Class definition for core locomotion engine and controller orchestrator
 * @author      Jeevan Sanchez
 * @date        2026-07-27
 *
 * PENGUIN
 */

#pragma once

#include <Arduino.h>
#include "penguin_state.hpp"
#include "balance_controller.hpp"
#include "velocity_controller.hpp"
#include "motor_driver.hpp"
#include "imu_driver.hpp"
#include "penguin_commands.hpp"

// IMU -> balance controller(IMU pitch) -> velocity controller(computed vel) -> motor driver (pwm)

class Locomotion {
    public: 
        Locomotion(BalanceController &balance,  VelocityController &leftVController, VelocityController &rightVController, MotorDriver &motorL, MotorDriver &motorR); 
        void update(const PenguinState &state, const PenguinCommands &commands, float dt); 

    private:
        WheelTargets calculateWheelTargets(const PenguinCommands &commands, float balanceOutput); 

        BalanceController &_balance; 
        VelocityController &_leftVController; 
        VelocityController &_rightVController; 
        MotorDriver &_motorL; 
        MotorDriver &_motorR;


}; 