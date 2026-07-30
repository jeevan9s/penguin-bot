/**
 * @file        motion_primitives.cpp
 * @brief       Implementation of motion primitives (movement actions)
 * @author      Jeevan Sanchez
 * @date        2026-07-30
 *
 * PENGUIN
 */

#include <Arduino.h>
#include "motion_primitives.hpp"

void MotionPrimitives::stand(PenguinCommands &commands) {
    commands.targetPitch = 0.0f; 
    commands.leftHipAngle = MotionConfig::STAND_HIP_ANGLE;
    commands.rightHipAngle = MotionConfig::STAND_HIP_ANGLE;
}

void MotionPrimitives::squat(PenguinCommands &commands) {
    commands.targetPitch = 0.0f;
    commands.leftHipAngle = MotionConfig::SQUAT_HIP_ANGLE; 
    commands.rightHipAngle = MotionConfig::SQUAT_HIP_ANGLE; 
}

void MotionPrimitives::leanFWD(PenguinCommands &commands) {
    commands.targetPitch = MotionConfig::FWD_LEAN_PITCH; 
}

void MotionPrimitives::leanREV(PenguinCommands &commands) {
    commands.targetPitch = -MotionConfig::FWD_LEAN_PITCH; 
}

void MotionPrimitives::leanLeft(PenguinCommands &commands) {
    commands.targetPitch = 0.0f; 
    commands.leftHipAngle = MotionConfig::LEFT_HIP_LEFT_LEAN_ANGLE; 
    commands.rightHipAngle = MotionConfig::RIGHT_HIP_LEFT_LEAN_ANGLE; 
}

void MotionPrimitives::leanRight(PenguinCommands &commands) {
    commands.targetPitch = 0.0f; 
    commands.leftHipAngle = MotionConfig::LEFT_HIP_RIGHT_LEAN_ANGLE; 
    commands.rightHipAngle = MotionConfig::RIGHT_HIP_RIGHT_LEAN_ANGLE; 
}

void MotionPrimitives::stop(PenguinCommands &commands) {
    commands.forwardRPM = 0.0f; 
    commands.turnRPM = 0.0f;
}

void MotionPrimitives::driveFWD(PenguinCommands &commands, float rpm) {
    commands.forwardRPM = rpm; 
}

void MotionPrimitives::driveREV(PenguinCommands &commands, float rpm) {
    commands.forwardRPM = -rpm; 
}

void MotionPrimitives::turnLeft(PenguinCommands &commands, float rpm) {
    commands.turnRPM = -rpm; 
}

void MotionPrimitives::turnRight(PenguinCommands &commands, float rpm) {
    commands.turnRPM = rpm; 
}