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

void MotionPrimitives::stand(PenguinCommands &commands);

void MotionPrimitives::squat(PenguinCommands &commands);

void MotionPrimitives::leanFWD(PenguinCommands &commands);

void MotionPrimitives::leanREV(PenguinCommands &commands);

void MotionPrimitives::leanLeft(PenguinCommands &commands);

void MotionPrimitives::leanRight(PenguinCommands &commands);

void MotionPrimitives::driveFWD(PenguinCommands &commands, float rpm);

void MotionPrimitives::driveREV(PenguinCommands &commands, float rpm);

void MotionPrimitives::turnLeft(PenguinCommands &commands, float rpm);

void MotionPrimitives::turnRight(PenguinCommands &commands, float rpm);

void MotionPrimitives::spinClockwise(PenguinCommands &commands, float rpm);

void MotionPrimitives::spinCounterClockwise(PenguinCommands &commands, float rpm);