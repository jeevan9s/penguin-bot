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

/// @brief constants for system configuration
// stance-based hip-servo angles 
// motor speeds based on levels and actions
// offsets for scan-pivots
// pitch depth (angles) for stance 
namespace MotionConfig {
    // tune
    constexpr float DEFAULT_HIP_ANGLE = 270.0f; 
    constexpr float SQUAT_HIP_ANGLE = 225.0f; 
    constexpr float STAND_HIP_ANGLE = 200.0f; 
    constexpr float LEFT_HIP_LEFT_LEAN_ANGLE = 0.0f; 
    constexpr float RIGHT_HIP_LEFT_LEAN_ANGLE = 0.0f; 
    constexpr float LEFT_HIP_RIGHT_LEAN_ANGLE = 0.0f; 
    constexpr float RIGHT_HIP_RIGHT_LEAN_ANGLE = 0.0f; 

    constexpr float CRAWL_SPEED = 50.0F;
    constexpr float CRUISE_SPEED = 150.0f; 
    constexpr float TURBO_SPEED = 250.0f; 

    constexpr float SPIN_STARTUP_SPEED = 50.0f;  

    constexpr float PIVOT_OFFST = 30.0f;
    constexpr float FWD_LEAN_PITCH = 5.0f; 

}; 

/// @brief cascade speed structure 
enum class SpeedLevel {
    CRAWL,
    CRUISE, 
    TURBO
};

/// @brief getter for speed values (RPM) based on typed speed levels
/// used to update commands
/// @param level one of the three speed levels
/// @return the corresponding float RPM value
inline float getRPM(SpeedLevel level) {
    switch(level) {
        case SpeedLevel::CRAWL: return MotionConfig::CRAWL_SPEED; 
        case SpeedLevel::CRUISE: return MotionConfig::CRUISE_SPEED; 
        case SpeedLevel::TURBO: return MotionConfig::TURBO_SPEED;
        default: return 0.0f; 
    }
}

