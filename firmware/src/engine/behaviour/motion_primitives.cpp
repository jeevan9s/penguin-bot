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
    commands.leftHipMicroseconds = MotionConfig::STAND_HIP_MICROSECONDS;
    commands.rightHipMicroseconds = MotionConfig::STAND_HIP_MICROSECONDS;
}

void MotionPrimitives::squat(PenguinCommands &commands, int squatMicroseconds) {
    commands.targetPitch = 0.0f;
    commands.leftHipMicroseconds = squatMicroseconds;
    commands.rightHipMicroseconds = squatMicroseconds;
}

void MotionPrimitives::leanFWD(PenguinCommands &commands) {
    commands.targetPitch = MotionConfig::FWD_LEAN_PITCH; 
}

void MotionPrimitives::leanREV(PenguinCommands &commands) {
    commands.targetPitch = -MotionConfig::FWD_LEAN_PITCH; 
}

void MotionPrimitives::leanLeft(PenguinCommands &commands) {
    commands.targetPitch = 0.0f; 
    commands.leftHipMicroseconds = MotionConfig::LEFT_HIP_LEFT_LEAN_MICROSECONDS;
    commands.rightHipMicroseconds = MotionConfig::RIGHT_HIP_LEFT_LEAN_MICROSECONDS;
}

void MotionPrimitives::leanRight(PenguinCommands &commands) {
    commands.targetPitch = 0.0f; 
    commands.leftHipMicroseconds = MotionConfig::LEFT_HIP_RIGHT_LEAN_MICROSECONDS;
    commands.rightHipMicroseconds = MotionConfig::RIGHT_HIP_RIGHT_LEAN_MICROSECONDS;
}

void MotionPrimitives::stop(PenguinCommands &commands) {
    commands.forwardRPM = 0.0f; 
    commands.turnRPM = 0.0f;
}

void MotionPrimitives::pivot(PenguinCommands &commands, float rpm) {
    commands.forwardRPM = 0.0f; 
    commands.turnRPM = rpm; 
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