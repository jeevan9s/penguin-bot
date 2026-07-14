/**
 * @file        PenguinState.hpp
 * @brief       State definition. 
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#pragma once
#include "PenguinData.hpp"

struct PenguinState {
    IMUData imu; 
    
    BattData battery; 

    TOFData sensor_L;
    
    TOFData sensor_M; 

    TOFData sensor_R;

    MotorData motor_L; 

    MotorData motor_R; 

    HealthData system; 
};

extern PenguinState penguinState; 