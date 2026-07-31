/**
 * @file        penguin_commands.hpp
 * @brief       Motion commands 
 * @author      Jeevan Sanchez
 * @date        2026-07-29
 *
 * PENGUIN
 */


#pragma once
#include <Arduino.h>

/// @brief structure for motor commands 
/// updated by primitives and observed by controllers
struct PenguinCommands {
    float forwardRPM; // along with turnRPM, converted into differential-drive inputs in locomotion engine
    float turnRPM; 

    float targetPitch; // deg

    float leftHipAngle; // deg
    float rightHipAngle; 
};

// light structure for updating left/right wheel target speeds
struct WheelTargets {
    float leftRPM; 
    float rightRPM; 
};

extern PenguinCommands penguin_commands; 