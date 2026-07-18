/**
 * @file        PenguinState.hpp
 * @brief       State definition. 
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#pragma once
 #include "state/PenguinData.hpp"

struct PenguinState {
    IMUData imu; 
    
    BattData battery; 

    TOFData sensL;
    
    TOFData sensM; 

    TOFData sensR;

    MotorData motorL; 

    MotorData motorR; 

    // HealthData system; 
};

extern PenguinState penguinState; 