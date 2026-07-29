/**
 * @file        commands.hpp
 * @brief       Motion commands 
 * @author      Jeevan Sanchez
 * @date        2026-07-29
 *
 * PENGUIN
 */


#pragma once
#include <Arduino.h>

struct PenguinCommands {
    float forwardRPM; 
    float turnRPM; 

    float targetPitch; 

    float leftHipAngle; 
    float rightHipAngle; 
}