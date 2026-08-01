/**
 * @file        penguin_state.hpp
 * @brief       State definition. 
 * @author      Jeevan Sanchez
 * @date        2026-07-14
 *
 * PENGUIN
 */

#pragma once
#include "penguin_data.hpp"


/// @brief global system object 
/// each component is mapped to a data object defined in penguin_data
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

extern PenguinState penguin_state; 
