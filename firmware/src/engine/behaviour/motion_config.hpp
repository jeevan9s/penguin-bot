/**
 * @file        motion_config.hpp
 * @brief       Motion constants & controller tuning 
 * @author      Jeevan Sanchez
 * @date        2026-07-30
 *
 * PENGUIN
 */

#pragma once 

#include <Arduino.h>

namespace MotionConfig {
    // tune
    constexpr float DEFAULT_HIP_ANGLE = 270.0f; 
    constexpr float SQUAT_HIP_ANGLE = 225.0f; 
    constexpr float STAND_HIP_ANGLE = 180.0f; 
    constexpr float LEFT_HIP_LEFT_LEAN_ANGLE = 0.0f; 
    constexpr float RIGHT_HIP_LEFT_LEAN_ANGLE = 0.0f; 
    constexpr float LEFT_HIP_RIGHT_LEAN_ANGLE = 0.0f; 
    constexpr float RIGHT_HIP_RIGHT_LEAN_ANGLE = 0.0f; 

    constexpr float FWD_LEAN_PITCH = 5.0f; 
}; 